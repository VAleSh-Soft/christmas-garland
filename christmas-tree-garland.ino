#include <FastLED.h> // https://github.com/FastLED/FastLED

#if FASTLED_VERSION < 3001000
#error "Requires FastLED 3.1 or later; check github for latest code."
#endif

#include "setting.h"

#if SAVE_EEPROM > 0
#include <EEPROM.h> // This is included with base install
#endif

// ===================================================

void strobe_mode(uint8_t newMode, bool mc);
void demo_check();

#if LED_ON > 0
void ledsFlash(uint8_t led_idx, uint8_t &count);
#endif

// ===================================================

#if LED_ON > 0
uint8_t Led1_flesh = 0x0; // Управление мигания светодиодом 1
#if LED_ON > 1
uint8_t Led2_flesh = 0; // Управление мигания светодиодом 2
#endif
#endif

#if defined(KEY_ON)
uint8_t IR_New_Mode = 0;   // Выбор эффекта
uint32_t IR_Time_Mode = 0; // время последнего нажатия
#endif

#if MAX_LEDS < 255
uint8_t NUM_LEDS; // Количество светодиодов, которые мы на самом деле используем, и мы можем изменить его только на длину нити
uint8_t KolLed;
#else
uint16_t NUM_LEDS; // Количество светодиодов, которые мы на самом деле используем, и мы можем изменить его только на длину нити
uint16_t KolLed;
#endif

uint8_t max_bright = 255; // Определение общей яркости; возможно изменение на лету

struct CRGB leds[MAX_LEDS]; // инициализация массива светодиодов

CRGBPalette16 gCurrentPalette; // Использование палитры вместо прямых назначений CHSV или CRGB.
CRGBPalette16 gTargetPalette;  // Поддержка плавной смены палитры
CRGB solid = CRGB::Black;      // Цвет закраски

extern const TProgmemRGBGradientPalettePtr gGradientPalettes[]; // для фиксированных палитр в gradient_palettes.h.

extern const uint8_t gGradientPaletteCount; // Общее количество фиксированных палитр
uint8_t gCurrentPaletteNumber = 0;          // Текущий номер палитры из списка палитр.
uint8_t currentPatternIndex = 0;            // Порядковый номер текущего шаблона
uint32_t demo_time = 0;                     // время демо режима

TBlendType currentBlending = LINEARBLEND; // NOBLEND или LINEARBLEND

// Индексы настроек в EEPROM
#define STARTMODE 0 // Расположение в EEPROM номера режима с которого будет старт (байт)
#define STRANDLEN 1 // Расположение в EEPROM длины гирлянды (2 байта)
#define STRANDEL 3  // Расположение в EEPROM задержки (байт)
#define EXTFLAG 4   // Расположение в EEPROM расширенных флагов
#define ISINIT 5    // Расположение в EEPROM байта корректности записи

#define INITVAL 0x55     // Это значение проверяем в бите корректности EEPROM
#define INITMODE 0       // с этого режима будет старт, по умолчанию 0 (старт с - с черного цвета)
#define INITLEN MAX_LEDS // Размер гирлянды при старте
#define INITDEL 0        // размер задержки при старте в миллисекундах

uint16_t meshdelay; // Timer for the notamesh. Works with INITDEL.

uint8_t ledMode = 0; // номер текущего режима
#if CHANGE_ON == 1
uint8_t newMode = 0; // номер нового режима
#if MAX_LEDS < 255
uint8_t StepMode = MAX_LEDS; // Текущий шаг перехода от нового режима к старому
#else
uint16_t StepMode = MAX_LEDS; // Текущий шаг перехода от нового режима к старому
#endif
#endif

uint8_t demorun = DEMO_MODE;
#if RUNNING_FIRE > 0
#define maxMode 122 // Maximum number of modes.
#else
#define maxMode 42 // Maximum number of modes.
#endif

uint8_t Protocol = 0; // Temporary variables to save latest IR input
uint32_t Command = 0;

// ==== Общие переменные =============================
uint8_t allfreq = 32; // Меняет частоту. Переменная для эффектов one_sin_pal и two_sin.
uint8_t bgclr = 0;    // Общий цвет фона. Переменная для эффектов matrix_pal и one_sin_pal.
uint8_t bgbri = 0;    // Общая фоновая яркость. Переменная для эффектов matrix_pal и one_sin_pal.

// Структура хранения расширенных настроек
#pragma pack(push, 1)
typedef union
{
  struct
  {
    bool RedGreen : 1;   // Очередность  Цветов  RGB
    bool Glitter : 1;    // Флаг включения блеска
    bool Background : 1; // Флаг включения заполнения фона
    bool Candle : 1;     // Флаг включения свечей
    bool DemoRand : 1;   // Флаг случайный перебор эффектов
    bool rezerv0 : 1;    // Зарезервировано
    bool rezerv1 : 1;    // Зарезервировано
    bool rezerv2 : 1;    // Зарезервировано
  };
  unsigned char Byte;
} ExtendedFlags;
#pragma pack(pop)

ExtendedFlags ExtFlag; // Флаги расширенных настроек

#define GLITTER ExtFlag.Glitter
#define BACKGROUND ExtFlag.Background
#define CANDLE ExtFlag.Candle

uint8_t palchg = 3;       // Управление палитрой  3 - менять палитру автоматически иначе нет
uint8_t startindex = 0;   // С какого цвета начинать. Переменная для эффектов one_sin_pal.
uint8_t thisbeat;         // Переменная для эффектов juggle_pal.
uint8_t thiscutoff = 192; // Если яркость ниже этой, то яркость = 0. Переменная для эффектов one_sin_pal и two_sin.
uint16_t thisdelay = 0;   // Задержка delay
uint8_t thisdiff = 1;     // Шаг изменения палитры. Переменная для эффектов confetti_pal, juggle_pal и rainbow_march.
int8_t thisdir = 1;       // Направление движения эффекта. принимает значение -1 или 1.
uint8_t thisfade = 224;   // Скорость затухания. Переменная для эффектов confetti_pal и juggle_pal.
uint8_t thishue = 0;      // Оттенок Переменная для эффектов two_sin.
uint8_t thisindex = 0;    // Указатель ан элемент палитры
uint8_t thisinc = 1;      // Изменение начального цвета после каждого прохода. Переменная для эффектов confetti_pal и one_sin_pal.
int thisphase = 0;        // Изменение фазы. Переменная для эффектов one_sin_pal, plasma и two_sin.
uint8_t thisrot = 1;      // Измение скорости вращения волны. В настоящее время 0.
int8_t thisspeed = 4;     // Изменение стандартной скорости
uint8_t wavebright = 255; // Вы можете изменить яркость волн / полос, катящихся по экрану.

#ifdef MY_MODE
const PROGMEM uint8_t my_mode[] = {MY_MODE};   // массив выбранных режимов
const uint8_t my_mode_count = sizeof(my_mode); // колличество выбрано режимов
uint8_t cur_my_mode = 0;                       // Указатель на текущий режим
#endif

#if CHANGE_SPARK == 4
uint8_t rand_spark = 0;
#endif

long summ = 0;

// ==== Функции отображения ==========================

// Функции поддержки
#include "src/addings.h"

// Эффекты
#include "src/confetti_pal.h"
#include "src/gradient_palettes.h"
#include "src/juggle_pal.h"
#include "src/matrix_pal.h"
#include "src/noise16_pal.h"
#include "src/noise8_pal.h"
#include "src/one_sin_pal.h"
#include "src/plasma.h"
#include "src/rainbow_march.h"
#include "src/rainbow_beat.h"
#include "src/serendipitous_pal.h"
#include "src/three_sin_pal.h"
#include "src/two_sin.h"
#include "src/blendwave.h"
#include "src/fire.h"
#include "src/candles.h"
#include "src/colorwave.h"

#if defined(KEY_ON)
#include "src/getirl.h"
#endif

#if defined(RUNNING_FIRE)
#include "src/running_fire.h"
#endif

// ===================================================

void setup()
{
  pinMode(COLOR_ORDER_PIN, INPUT_PULLUP);

#if defined(KEY_ON)
  btn1.setVirtualClickOn(true);
  btn1.setLongClickMode(LCM_CLICKSERIES);
#if KEY_ON > 1
  btn2.setVirtualClickOn(true);
  btn2.setLongClickMode(LCM_CLICKSERIES);
#endif
#if KEY_ON > 2
  btn3.setVirtualClickOn(true);
  btn3.setLongClickMode(LCM_CLICKSERIES);
#endif
#if KEY_ON > 3
  btn4.setVirtualClickOn(true);
  btn4.setLongClickMode(LCM_CLICKSERIES);
#endif
#endif

#if LED_ON > 0
  pinMode(LED1_PIN, OUTPUT); // пин первого светодиода
#if LED_ON > 1
  pinMode(LED2_PIN, OUTPUT); // пин второго светодиода
#endif
  LED1_On; // Включим светодиод
#endif

#if LOG_ON == 1
  Serial.begin(SERIAL_BAUDRATE); // Setup serial baud rate

  Serial.println(F(" "));
  Serial.println(F("---SETTING UP---"));

#endif

#if SAVE_EEPROM > 0

#if !defined(__AVR__)
  EEPROM.begin(ISINIT + 1);
#endif
  ledMode = EEPROM.read(STARTMODE);  // Расположение в EEPROM номера режима с которого будет старт (байт)
  NUM_LEDS = EEPROM.read(STRANDLEN); // Расположение в EEPROM длины гирлянды (2 байта)
#if MAX_LEDS < 255
  if (EEPROM.read(STRANDLEN + 1)) // Почемуто светодиодов болше чем размер переменной
    NUM_LEDS = MAX_LEDS;          // Need to ensure NUM_LEDS < MAX_LEDS elsewhere.
#else
  NUM_LEDS += (uint16_t)EEPROM.read(STRANDLEN + 1) << 8; // Need to ensure NUM_LEDS < MAX_LEDS elsewhere.
#endif
  meshdelay = EEPROM.read(STRANDEL); // Расположение в EEPROM задержки (байт)

#if SAVE_EEPROM == 1
  ExtFlag.Byte = EEPROM.read(EXTFLAG); // Прочитаем расширенные настройки
#else
  ExtFlag.RedGreen = digitalRead(COLOR_ORDER_PIN) ? 1 : 0;
  // if (COLOR_ORDER == RGB)
  //   ExtFlag.RedGreen = 1;
  // else
  //   ExtFlag.RedGreen = 0;
  ExtFlag.Glitter = GLITER_ON;    // Флаг включения блеска
  ExtFlag.Background = BACKGR_ON; // Флаг включения заполнения фона
  ExtFlag.Candle = CANDLE_ON;     // Флаг включения свечей
#endif

  if ((EEPROM.read(ISINIT) != INITVAL) || // проверка правильности в EEPROM байта корректности записи
      (NUM_LEDS > MAX_LEDS) ||
      ((ledMode > maxMode) && (ledMode != 100)))
  {                                    // Не корректен
    EEPROM.write(STARTMODE, INITMODE); // сохраним в EEPROM номера режима с которого будет старт (байт)
#if MAX_LEDS < 255
    EEPROM.write(STRANDLEN, INITLEN); // сохраним в EEPROM длины гирлянды (2 байта)
#else
    EEPROM.write(STRANDLEN, (uint16_t)(INITLEN) & 0x00ff);
    EEPROM.write(STRANDLEN + 1, (uint16_t)(INITLEN) >> 8);
#endif
    EEPROM.write(STRANDEL, INITDEL); // сохраним в EPROM задержку (байт)

    ExtFlag.RedGreen = digitalRead(COLOR_ORDER_PIN) ? 1 : 0;
    // if (COLOR_ORDER == RGB)
    //   ExtFlag.RedGreen = 1;
    // else
    //   ExtFlag.RedGreen = 0;
    ExtFlag.Glitter = GLITER_ON;         // Флаг включения блеска
    ExtFlag.Background = BACKGR_ON;      // Флаг включения заполнения фона
    ExtFlag.Candle = CANDLE_ON;          // Флаг включения свечей
    EEPROM.write(EXTFLAG, ExtFlag.Byte); // сохраним в EPROM расширенные настройки

    EEPROM.write(ISINIT, INITVAL); // сохраним в EEPROM байта корректности записи
#if !defined(__AVR__)
    EEPROM.commit();
#endif

    ledMode = INITMODE;
    NUM_LEDS = INITLEN;
    meshdelay = INITDEL;
  }
#else
  // ExtFlag.RedGreen = digitalRead(COLOR_ORDER_PIN) ? 1 : 0;
  ExtFlag.RedGreen = 0;
  // if (COLOR_ORDER == RGB)
  //   ExtFlag.RedGreen = 1;
  // else
  //   ExtFlag.RedGreen = 0;
  ExtFlag.Glitter = GLITER_ON;    // Флаг включения блеска
  ExtFlag.Background = BACKGR_ON; // Флаг включения заполнения фона
  ExtFlag.Candle = CANDLE_ON;     // Флаг включения свечей

#ifdef MY_MODE
  switch (demorun)
  {
  case 3:
    ledMode = pgm_read_byte(my_mode + cur_my_mode);
    break; // демо 3
  case 4:
    ledMode = pgm_read_byte(my_mode + random8(my_mode_count));
    break; // демо 4
  case 1:
  case 2:
    ledMode = INITMODE;
    break;
  }
#else
  ledMode = INITMODE;
#endif
  NUM_LEDS = MAX_LEDS;
  meshdelay = INITDEL;
#endif

  if (NUM_LEDS < (TOP_LENGTH + 1))
  {
    NUM_LEDS = (TOP_LENGTH + 1); // Проверка
  }

  LEDS.setBrightness(max_bright);

  if (ExtFlag.RedGreen)
  {
#if LED_CLK_PIN
    LEDS.addLeds<CHIPSET, LED_DATA_PIN, LED_CLK_PIN, RGB>(leds, MAX_LEDS);
#else
    LEDS.addLeds<CHIPSET, LED_DATA_PIN, RGB>(leds, MAX_LEDS); // Для светодиодов WS2812B
#endif
  }
  else
  {
#if LED_CLK_PIN
    LEDS.addLeds<CHIPSET, LED_DATA_PIN, LED_CLK_PIN, GRB>(leds, MAX_LEDS);
#else
    LEDS.addLeds<CHIPSET, LED_DATA_PIN, GRB>(leds, MAX_LEDS); // Для светодиодов WS2812B
#endif
  }

  LEDS.setMaxPowerInVoltsAndMilliamps(POWER_V, POWER_I); // Настройка блока питания

  random16_set_seed(4832); // Рандомайзер
  random16_add_entropy(analogRead(2));

#if LOG_ON == 1
  Serial.print(F("Initial delay: "));
  Serial.print(meshdelay * 100);
  Serial.println(F("ms delay."));
  Serial.print(F("Initial strand length: "));
  Serial.print(NUM_LEDS);
  Serial.println(F(" LEDs"));
  Serial.println(F("EXTEND Setup"));
  if (ExtFlag.RedGreen)
    Serial.println(F("RGB LEDS"));
  else
    Serial.println(F("GRB LEDS"));
  if (ExtFlag.Glitter)
    Serial.println(F("Glitter On"));
  else
    Serial.println(F("Glitter Off"));
  if (ExtFlag.Background)
    Serial.println(F("Background On"));
  else
    Serial.println(F("Background Off"));
  if (ExtFlag.Candle)
    Serial.println(F("Candle On"));
  else
    Serial.println(F("Candle Off"));
#endif

#if BLACKSTART == 1
  solid = CRGB::Black; // Запуск с пустого поля
#if CHANGE_ON == 1
  newMode = ledMode;
  StepMode = 1;
#endif
  ledMode = 255;
#endif

  gCurrentPalette = gGradientPalettes[0];
  gTargetPalette = gGradientPalettes[0];
  strobe_mode(ledMode, 1); // инициализация первой последовательности
#if LOG_ON == 1
  if (DEMO_MODE)
  {
    Serial.print(F("DEMO MODE "));
    Serial.println(DEMO_MODE);
  }
  Serial.println(F("---SETUP COMPLETE---"));
#endif

  LED1_Off; // Выключим светодиод
}

void loop()
{

#if defined(KEY_ON)
  getirl(); // Обработка кнопок
#endif

  demo_check(); // Работа если включен демонстрационный режим

  EVERY_N_MILLISECONDS(50)
  { // Плавный переход от одной палитры в другую
#if CHANGE_ON == 1
    if (StepMode == MAX_LEDS)
#endif
      nblendPaletteTowardPalette(gCurrentPalette, gTargetPalette, PALETTE_SPEED);

#if LED_ON > 0 // мигаем светодиодом 1
    if (Led1_flesh > 0)
    {
      ledsFlash(1, Led1_flesh);
    }
#if LED_ON > 1 // мигаем светодиодом 2
    if (Led2_flesh > 0)
    {
      ledsFlash(2, Led2_flesh);
    }
#endif
#endif
  }

#if PALETTE_TIME > 0
  if ((palchg) && (demorun <= 100))
  {
    EVERY_N_SECONDS(PALETTE_TIME)
    { // Смена палитры
      if (palchg == 3)
      {
        if (gCurrentPaletteNumber < (gGradientPaletteCount - 1))
          gCurrentPaletteNumber++;
        else
          gCurrentPaletteNumber = 0;
#if LOG_ON == 1
        Serial.print(F("New Palette: "));
        Serial.println(gCurrentPaletteNumber);
#endif
      }
      gTargetPalette = gGradientPalettes[gCurrentPaletteNumber]; // We're just ensuring that the gTargetPalette WILL be assigned.
    }
  }
#endif

#if DIRECT_TIME > 0
  EVERY_N_SECONDS(DIRECT_TIME)
  { // Меняем направление
    thisdir = thisdir * -1;
  }
#endif

  EVERY_N_MILLIS_I(thistimer, thisdelay)
  {                                 // Sets the original delay time.
    thistimer.setPeriod(thisdelay); // This is how you update the delay value on the fly.
    KolLed = NUM_LEDS - TOP_LENGTH; // Выводим Эффект на все светодиоды
    strobe_mode(ledMode, 0);        // отобразить эффект;
#if CHANGE_ON == 1
    if ((StepMode < (NUM_LEDS - TOP_LENGTH)) && ((ledMode < 220) || (ledMode >= 230)))
    {                    // требуется наложить новый эффект
      KolLed = StepMode; // Выводим Эффект на все светодиоды
      if (StepMode > 10)
        strobe_mode(newMode, 0); // отобразить эффект;
#if CHANGE_SPARK == 4
      sparkler(rand_spark);
#else
      sparkler(CHANGE_SPARK); // бенгальский огонь
#endif
    }
#endif
  }

#if CHANGE_ON == 1 // Включена плавная смена эффектов
  if (StepMode < (NUM_LEDS - TOP_LENGTH))
  {                                                                         // есть шаги, исполняем
    uint16_t change_time = (1000L * CHANGE_TIME) / (NUM_LEDS - TOP_LENGTH); // время в мСек на каждый светодиод
    if (change_time < 20)
    {
      change_time = 20;
    }
    //        static uint8_t change_increment = (uint32_t)change_time * (NUM_LEDS-TOP_LENGTH) / (1000L *CHANGE_TIME)+1;
    EVERY_N_MILLISECONDS(change_time)
    { // Движение плавной смены эффектов
      //            if (StepMode > 10) StepMode += change_increment;
      //            else
      StepMode++;
      if (StepMode == 10)
      {
        strobe_mode(newMode, 1);
      }
      if (StepMode >= (NUM_LEDS - TOP_LENGTH))
      {
        ledMode = newMode;
        StepMode = MAX_LEDS - TOP_LENGTH;

#if LOG_ON == 1
        Serial.println(F("End SetMode"));
#endif
      }
      nblendPaletteTowardPalette(gCurrentPalette, gTargetPalette, PALETTE_SPEED);
    }
  }
#endif

#if TOP_LENGTH > 0
  top(); // Обработка конца гирлянды
#endif
  if (GLITTER)
  {
    addglitter(10); // блеск, если включен
  }
#if CANDLE_KOL > 0
  if (CANDLE)
  {
    addcandle();
  }
#endif

  if (BACKGROUND)
  {
    addbackground(); // Включить заполнение черного цвета фоном
  }

  BtnHandler(); // Обработчик нажатий кнопок

#if defined(KEY_ON)
  if ((IR_Time_Mode > 0) && // Идет отчет времени
      ((millis() - IR_Time_Mode) >= 2000))
  { // И прошло больше 2 секунд
    IR_Time_Mode = 0;
    if (IR_New_Mode <= maxMode)
      SetMode(IR_New_Mode);
    IR_New_Mode = 0;
  }
#endif

  FastLED.show(); // Power managed display of LED's.
}

void strobe_mode(uint8_t mode, bool mc)
{ // mc stands for 'Mode Change', where mc = 0 is strobe the routine, while mc = 1 is change the routine

  if (mc)
  {
    fill_solid(leds, NUM_LEDS - TOP_LENGTH, CRGB(0, 0, 0)); // Clean up the array for the first time through. Don't show display though, so you may have a smooth transition.

#if LOG_ON == 1
    Serial.print(F("Mode: "));
    Serial.println(mode);
    Serial.println(millis());
#endif
#if PALETTE_TIME > 0
    if (palchg == 0)
      palchg = 3;
#else
    if (palchg == 0)
      palchg = 1;
#endif
  }

  switch (mode)
  { // First time through a new mode, so let's initialize the variables for a given display.
  case 0:
    if (mc)
    {
      thisdelay = 10;
      palchg = 0;
    }
    blendwave();
    break;
  case 1:
    if (mc)
    {
      thisdelay = 10;
      palchg = 0;
    }
    rainbow_beat();
    break;
  case 2:
    if (mc)
    {
      thisdelay = 10;
      allfreq = 2;
      thisspeed = 1;
      thatspeed = 2;
      thishue = 0;
      thathue = 128;
      thisdir = 1;
      thisrot = 1;
      thatrot = 1;
      thiscutoff = 128;
      thatcutoff = 192;
    }
    two_sin();
    break;
  case 3:
    if (mc)
    {
      thisdelay = 20;
      allfreq = 4;
      bgclr = 0;
      bgbri = 0;
      startindex = 64;
      thisinc = 2;
      thiscutoff = 224;
      thisphase = 0;
      thiscutoff = 224;
      thisrot = 0;
      thisspeed = 4;
      wavebright = 255;
    }
    one_sin_pal();
    break;
  case 4:
    if (mc)
    {
      thisdelay = 10;
    }
    noise8_pal();
    break;
  case 5:
    if (mc)
    {
      thisdelay = 10;
      allfreq = 4;
      thisspeed = -1;
      thatspeed = 0;
      thishue = 64;
      thathue = 192;
      thisdir = 1;
      thisrot = 0;
      thatrot = 0;
      thiscutoff = 64;
      thatcutoff = 192;
    }
    two_sin();
    break;
  case 6:
    if (mc)
    {
      thisdelay = 20;
      allfreq = 10;
      bgclr = 64;
      bgbri = 4;
      startindex = 64;
      thisinc = 2;
      thiscutoff = 224;
      thisphase = 0;
      thiscutoff = 224;
      thisrot = 0;
      thisspeed = 4;
      wavebright = 255;
    }
    one_sin_pal();
    break;
  case 7:
    if (mc)
    {
      thisdelay = 10;
      numdots = 2;
      thisfade = 16;
      thisbeat = 8;
      thisdiff = 64;
    }
    juggle_pal();
    break;
  case 8:
    if (mc)
    {
      thisdelay = 40;
      thisindex = 128;
      thisdir = 1;
      thisrot = 0;
      bgclr = 200;
      bgbri = 6;
    }
    matrix_pal();
    break;
  case 9:
    if (mc)
    {
      thisdelay = 10;
      allfreq = 6;
      thisspeed = 2;
      thatspeed = 3;
      thishue = 96;
      thathue = 224;
      thisdir = 1;
      thisrot = 0;
      thatrot = 0;
      thiscutoff = 64;
      thatcutoff = 64;
    }
    two_sin();
    break;
  case 10:
    if (mc)
    {
      thisdelay = 20;
      allfreq = 16;
      bgclr = 0;
      bgbri = 0;
      startindex = 64;
      thisinc = 2;
      thiscutoff = 224;
      thisphase = 0;
      thiscutoff = 224;
      thisrot = 0;
      thisspeed = 4;
      wavebright = 255;
    }
    one_sin_pal();
    break;
  case 11:
    if (mc)
    {
      thisdelay = 50;
      mul1 = 5;
      mul2 = 8;
      mul3 = 7;
    }
    three_sin_pal();
    break;
  case 12:
    if (mc)
    {
      thisdelay = 10;
    }
    serendipitous_pal();
    break;
  case 13:
    if (mc)
    {
      thisdelay = 20;
      allfreq = 8;
      bgclr = 0;
      bgbri = 4;
      startindex = 64;
      thisinc = 2;
      thiscutoff = 224;
      thisphase = 0;
      thiscutoff = 224;
      thisrot = 0;
      thisspeed = 4;
      wavebright = 255;
    }
    one_sin_pal();
    break;
  case 14:
    if (mc)
    {
      thisdelay = 10;
      allfreq = 20;
      thisspeed = 2;
      thatspeed = -1;
      thishue = 24;
      thathue = 180;
      thisdir = 1;
      thisrot = 0;
      thatrot = 1;
      thiscutoff = 64;
      thatcutoff = 128;
    }
    two_sin();
    break;
  case 15:
    if (mc)
    {
      thisdelay = 50;
      thisindex = 64;
      thisdir = -1;
      thisrot = 1;
      bgclr = 100;
      bgbri = 10;
    }
    matrix_pal();
    break;
  case 16:
    if (mc)
    {
      thisdelay = 10;
    }
    noise8_pal();
    break; // By: Andrew Tuline
  case 17:
    if (mc)
    {
      thisdelay = 10;
    }
    plasma(11, 23, 4, 18);
    break;
  case 18:
    if (mc)
    {
      thisdelay = 20;
      allfreq = 10;
      thisspeed = 1;
      thatspeed = -2;
      thishue = 48;
      thathue = 160;
      thisdir = -1;
      thisrot = 1;
      thatrot = -1;
      thiscutoff = 128;
      thatcutoff = 192;
    }
    two_sin();
    break;
  case 19:
    if (mc)
    {
      thisdelay = 50;
      palchg = 0;
      thisdir = 1;
      thisrot = 1;
      thisdiff = 1;
    }
    rainbow_march();
    break;
  case 20:
    if (mc)
    {
      thisdelay = 10;
      mul1 = 6;
      mul2 = 9;
      mul3 = 11;
    }
    three_sin_pal();
    break;
  case 21:
    if (mc)
    {
      thisdelay = 10;
      palchg = 0;
      thisdir = 1;
      thisrot = 2;
      thisdiff = 10;
    }
    rainbow_march();
    break;
  case 22:
    if (mc)
    {
      thisdelay = 20;
      palchg = 0;
      hxyinc = random16(1, 15);
      octaves = random16(1, 3);
      hue_octaves = random16(1, 5);
      hue_scale = random16(10, 50);
      x = random16();
      xscale = random16();
      hxy = random16();
      hue_time = random16();
      hue_speed = random16(1, 3);
      x_speed = random16(1, 30);
    }
    noise16_pal();
    break;
  case 23:
    if (mc)
    {
      thisdelay = 20;
      allfreq = 6;
      bgclr = 0;
      bgbri = 0;
      startindex = 64;
      thisinc = 2;
      thiscutoff = 224;
      thisphase = 0;
      thiscutoff = 224;
      thisrot = 0;
      thisspeed = 4;
      wavebright = 255;
    }
    one_sin_pal();
    break;
  case 24:
    if (mc)
    {
      thisdelay = 10;
    }
    plasma(23, 15, 6, 7);
    break;
  case 25:
    if (mc)
    {
      thisdelay = 20;
      thisinc = 1;
      thisfade = 2;
      thisdiff = 32;
    }
    confetti_pal();
    break;
  case 26:
    if (mc)
    {
      thisdelay = 10;
      thisspeed = 2;
      thatspeed = 3;
      thishue = 96;
      thathue = 224;
      thisdir = 1;
      thisrot = 1;
      thatrot = 2;
      thiscutoff = 128;
      thatcutoff = 64;
    }
    two_sin();
    break;
  case 27:
    if (mc)
    {
      thisdelay = 30;
      thisindex = 192;
      thisdir = -1;
      thisrot = 0;
      bgclr = 50;
      bgbri = 0;
    }
    matrix_pal();
    break;
  case 28:
    if (mc)
    {
      thisdelay = 20;
      allfreq = 20;
      bgclr = 0;
      bgbri = 0;
      startindex = 64;
      thisinc = 2;
      thiscutoff = 224;
      thisphase = 0;
      thiscutoff = 224;
      thisrot = 0;
      thisspeed = 4;
      wavebright = 255;
    }
    one_sin_pal();
    break;
  case 29:
    if (mc)
    {
      thisdelay = 20;
      thisinc = 2;
      thisfade = 8;
      thisdiff = 64;
    }
    confetti_pal();
    break;
  case 30:
    if (mc)
    {
      thisdelay = 10;
    }
    plasma(8, 7, 9, 13);
    break;
  case 31:
    if (mc)
    {
      thisdelay = 10;
      numdots = 4;
      thisfade = 32;
      thisbeat = 12;
      thisdiff = 20;
    }
    juggle_pal();
    break;
  case 32:
    if (mc)
    {
      thisdelay = 30;
      allfreq = 4;
      bgclr = 64;
      bgbri = 4;
      startindex = 64;
      thisinc = 2;
      thiscutoff = 224;
      thisphase = 0;
      thiscutoff = 128;
      thisrot = 1;
      thisspeed = 8;
      wavebright = 255;
    }
    one_sin_pal();
    break;
  case 33:
    if (mc)
    {
      thisdelay = 50;
      mul1 = 3;
      mul2 = 4;
      mul3 = 5;
    }
    three_sin_pal();
    break;
  case 34:
    if (mc)
    {
      thisdelay = 10;
      palchg = 0;
      thisdir = -1;
      thisrot = 1;
      thisdiff = 5;
    }
    rainbow_march();
    break;
  case 35:
    if (mc)
    {
      thisdelay = 10;
    }
    plasma(11, 17, 20, 23);
    break;
  case 36:
    if (mc)
    {
      thisdelay = 20;
      thisinc = 1;
      thisfade = 1;
    }
    confetti_pal();
    break;
  case 37:
    if (mc)
    {
      thisdelay = 20;
      palchg = 0;
      octaves = 1;
      hue_octaves = 2;
      hxy = 6000;
      x = 5000;
      xscale = 3000;
      hue_scale = 50;
      hue_speed = 15;
      x_speed = 100;
    }
    noise16_pal();
    break;
  case 38:
    if (mc)
    {
      thisdelay = 10;
    }
    noise8_pal();
    break;
  case 39:
    if (mc)
    {
      thisdelay = 10;
      palchg = 0;
    }
    fire();
    break;
  case 40:
    if (mc)
    {
      thisdelay = 10;
      palchg = 0;
    }
    candles();
    break;
  case 41:
    if (mc)
    {
      thisdelay = 10;
    }
    colorwaves();
    break;
    //  case 42 .. 121: if(mc) {thisdelay=10; } running_fire(9,3,1); break;
  case 200:
    fill_solid(leds, MAX_LEDS, CRGB::Black);
    fill_solid(leds, NUM_LEDS, CRGB(255, 255, 255));
    break; // Зажечь гирлянду длиной NUM_LEDS (регулировка длины гирлянды)
  case 201:
    fill_solid(leds, MAX_LEDS, CRGB::Black);
    fill_solid(leds, meshdelay, CRGB(255, 255, 255));
    break; // Зажечь гирлянду длиной meshdelay
  case 220:
    fill_solid(leds, MAX_LEDS, CRGB::Black);
    fill_solid(leds, NUM_LEDS, CRGB(255, 255, 255));
    leds[0] = CRGB::Red;
    break; // Зажечь гирлянду длиной NUM_LEDS (регулировка длины гирлянды)
  case 221:
    fill_solid(leds, MAX_LEDS, CRGB::Black);
    fill_solid(leds, NUM_LEDS, CRGB(255, 255, 255));
    leds[0] = CRGB::Green;
    break; // Зажечь гирлянду длиной NUM_LEDS (регулировка длины гирлянды)
  case 255:
    if (mc)
    {
      palchg = 0;
    }
    fill_solid(leds, NUM_LEDS - TOP_LENGTH, solid);
    break; // Установить цвет
  default:
#if RUNNING_FIRE == 1
    if (mode >= 42 && mode < 122)
    {
      uint8_t mode_x = mode - 42;
      if (mc)
      {
        thisdelay = 10;
      }
      running_fire(mode_x >> 3, (mode_x >> 1) % 3, mode_x % 1);
    }
    else
#endif
      ledMode = 0;
    break; // нет такого режима принудительно ставим нулевой
  }

#if LOG_ON == 1
  if (mc)
  {
    if (palchg == 0)
      Serial.println(F("Change palette off"));
    else if (palchg == 1)
      Serial.println(F("Change palette Stop"));
    else if (palchg == 3)
      Serial.println(F("Change palette ON"));
  }
#endif
}

void demo_check()
{

  if ((demorun > 0) && (demorun <= 100))
  {
    if ((millis() - demo_time) >= (DEMO_TIME * 1000L))
    {                                                            // Наступило время смены эффекта
      demo_time = millis();                                      // Запомним время
      gCurrentPaletteNumber = random8(0, gGradientPaletteCount); // Случайно поменяем палитру
#if CHANGE_ON == 1
      switch (demorun)
      {
      case 2:
        newMode = random8(0, maxMode); // демо 2
        break;
#ifdef MY_MODE
      case 3:
        if (cur_my_mode >= (my_mode_count - 1))
          cur_my_mode = 0; // демо 3
        else
          cur_my_mode++;
        newMode = pgm_read_byte(my_mode + cur_my_mode);
        break;
      case 4:
        newMode = pgm_read_byte(my_mode + random8(my_mode_count)); // демо 4
        break;
#endif
      case 1:
        if (newMode >= maxMode)
          newMode = 0; // демо 1
        else
          newMode++;
        break;
      }
      StepMode = 1;
#if CHANGE_SPARK == 4
      rand_spark = random8(3) + 1;
#endif

#if LOG_ON == 1
      Serial.println(F("Start SetMode"));
#endif
#else
      gTargetPalette = gGradientPalettes[gCurrentPaletteNumber]; // Применим палитру
#if LOG_ON == 1
      Serial.print(F("New Palette: "));
      Serial.println(gCurrentPaletteNumber);
#endif
      switch (demorun)
      {
      case 2:
        ledMode = random8(0, maxMode); // демо 2
        break;
#ifdef MY_MODE
      case 3:
        if (cur_my_mode >= (my_mode_count - 1))
          cur_my_mode = 0; // демо 3
        else
          cur_my_mode++;
        ledMode = pgm_read_byte(my_mode + cur_my_mode);
        break;
      case 4:
        ledMode = pgm_read_byte(my_mode + random8(my_mode_count)); // демо 4
        break;
#endif
      case 1:
        if (ledMode >= maxMode)
          ledMode = 0; // демо 1
        else
          ledMode++;
        break;
      }
      strobe_mode(ledMode, 1); // Does NOT reset to 0.
#if CANDLE_KOL > 0
      PolCandle = random8(CANDLE_KOL);
#endif
#endif
    }
  }
}

#if LED_ON > 0
// мигание светодиодом
void ledsFlash(uint8_t led_idx, uint8_t &count)
{
#if LED_ON == 1
  if (led_idx > 1)
  {
    return;
  }
#endif
  if (led_idx > 2 || led_idx == 0)
  {
    return;
  }

  uint8_t _pin = (led_idx == 1) ? LED1_PIN : LED2_PIN;

  if (count > 0)
  {
    count--;
    if (count >= 128)
    {
      if (count & 8)
      {
        digitalWrite(_pin, HIGH);
      }
      else
      {
        digitalWrite(_pin, LOW);
      }
      if (count == 128)
        count = 0;
    }
    else if (count >= 64)
    {
      if (count & 4)
      {
        digitalWrite(_pin, HIGH);
      }
      else
      {
        digitalWrite(_pin, LOW);
      }
      if (count == 64)
        count = 0;
    }
    else
    {
      if (count & 2)
      {
        digitalWrite(_pin, HIGH);
      }
      else
      {
        digitalWrite(_pin, LOW);
      }
    }
  }
}
#endif
