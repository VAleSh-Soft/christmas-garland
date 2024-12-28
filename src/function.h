#pragma once

#include <FastLED.h>
#include "../setting.h"
#if BUTTONS_NUM
#include <shButton.h> // https://github.com/VAleSh-Soft/shButton
#endif

// ===================================================

#if BUTTONS_NUM
class cgButton : public shButton
{
private:
  /* data */
public:
  cgButton(int8_t pin) : shButton(pin)
  {
    shButton::setVirtualClickOn(true);
    shButton::setLongClickMode(LCM_CLICKSERIES);
  }
};

#endif

// ===================================================

#if BUTTONS_NUM
cgButton btn1(BTN1_PIN);
#if BUTTONS_NUM > 1
cgButton btn2(BTN2_PIN);
#endif
#if BUTTONS_NUM > 2
cgButton btn3(BTN3_PIN);
#endif
#if BUTTONS_NUM > 3
cgButton btn4(BTN4_PIN);
#endif
#endif

// ===================================================

#if LED_ON
// ==== Команды связанные со светодиодами ============
#define LED1_On digitalWrite(LED1_PIN, HIGH)      // Включить светодиод 1
#define LED1_Off digitalWrite(LED1_PIN, LOW)      // Выключить светодиод 1
#define LED1_FleshH(x) led1Flesh = 4 * x          // Мигнуть быстро x раз 1 светодиодом    (1-15)
#define LED1_Flesh(x) led1Flesh = 64 + (8 * x)    // Мигнуть x раз 1 светодиодом           (1-7)
#define LED1_FleshL(x) led1Flesh = 128 + (16 * x) // Мигнуть медленно x раз 1 светодиодом  (1-7)
#else
#define LED1_On
#define LED1_Off
#define LED1_FleshH(x)
#define LED1_Flesh(x)
#define LED1_FleshL(x)
#endif

#if LED_ON > 1
#define LED2_On digitalWrite(LED2_PIN, HIGH)    // Включить светодиод 2
#define LED2_Off digitalWrite(LED2_PIN, LOW)    // Выключить светодиод 2
#define LED2_FleshH(x) led2Flesh = 4 * x        // Мигнуть быстро x раз 2 светодиодом    (1-15)
#define LED2_Flesh(x) led2Flesh = 64 + 8 * x    // Мигнуть x раз 2 светодиодом           (1-7)
#define LED2_FleshL(x) led2Flesh = 128 + 16 * x // Мигнуть медленно x раз 2 светодиодом  (1-7)
#else
#define LED2_On
#define LED2_Off
#define LED2_FleshH(x)
#define LED2_Flesh(x)
#define LED2_FleshL(x)
#endif

#if LOG_ON
// ==== макросы вывода в Serial ======================
#define CTG_PRINT(x) Serial.print(x)
#define CTG_PRINTLN(x) Serial.println(x)
#define CTG_PRINTLN_2(x, y) Serial.println(x, y)
#else
#define CTG_PRINT(x)
#define CTG_PRINTLN(x)
#define CTG_PRINTLN_2(x, y)
#endif

// ==== Переменные ===================================

// Установить флаг OFF
void setOff(uint8_t &x);
// Установить флаг ON
void setOn(uint8_t &x);

int qsubd(size_t x, size_t b);
int qsuba(size_t x, size_t b);
#if SAVE_EEPROM
// инициализация параметров, сохраненных в EEPROM
void eeprom_init();
#endif
#if TOP_LENGTH > 0
// обработка конца гирлянды
void top();
#endif
// подмена цветов согласно сохраненного порядка следования перед выводом их на гирлянду
CRGB set_new_eorder(CRGB _col);
//  добавление свечей
void addCandle();
// заливка фона
void addBackground();
// блестки
void addGlitter(fract8 chanceOfGlitter);
// бенгальский огонь
void sparkler(uint8_t n);
// обработчик нажатий кнопок
void btnHandler();
#if LED_ON > 0
void ledsFlash(uint8_t led_idx, uint8_t &count);
#endif
#if SAVE_EEPROM
// чтение длины нити из EEPROM
void readStrandLen();
// сохранение длины нити в EEPROM
void writeStrandLen();
#endif

// ===================================================

#if LED_ON > 0
uint8_t led1Flesh = 0; // Управление мигания светодиодом 1
#if LED_ON > 1
uint8_t led2Flesh = 0; // Управление мигания светодиодом 2
#endif
#endif

uint8_t protocol = 0;
uint32_t command = 0;

// ==== Общие переменные =============================

#if MAX_LEDS < 255
uint8_t numLeds; // Количество светодиодов, которые мы на самом деле используем, и мы можем изменить его только на длину нити - не более MAX_LEDS
uint8_t kolLeds;
#else
uint16_t numLeds; // Количество светодиодов, которые мы на самом деле используем, и мы можем изменить его только на длину нити - не более MAX_LEDS
uint16_t kolLeds;
#endif

#if TOP_LENGTH
#if TOP_LENGTH < 255
uint8_t topLength = TOP_LENGTH;
#else
uint16_t topLength = TOP_LENGTH;
#endif
uint8_t topEffectIndex = TOP_EFFECT;
uint8_t topDelay = TOP_DELAY;
uint8_t topFading = TOP_FADING;
#endif

#if BUTTONS_NUM > 2
uint8_t topColorIndex = 0;
uint8_t bgrColorIndex = 0;
#endif

uint8_t polCandle = 1; // Положение свечи

uint8_t maxBright = 255; // Определение общей яркости; возможно изменение на лету

struct CRGB leds[MAX_LEDS]; // инициализация массива светодиодов

CRGBPalette16 gCurrentPalette; // Использование палитры вместо прямых назначений CHSV или CRGB.
CRGBPalette16 gTargetPalette;  // Поддержка плавной смены палитры
CRGB solid = CRGB::Black;      // Цвет заливки

extern const TProgmemRGBGradientPalettePtr gGradientPalettes[]; // для фиксированных палитр в gradient_palettes.h.

extern const uint8_t gGradientPaletteCount; // Общее количество фиксированных палитр
uint8_t gCurrentPaletteNumber = 0;          // Текущий номер палитры из списка палитр.
uint8_t currentPatternIndex = 0;            // Порядковый номер текущего шаблона
uint32_t demo_time = 0;                     // время демо режима

TBlendType currentBlending = LINEARBLEND; // NOBLEND или LINEARBLEND

#define INITVAL 0x55     // Это значение проверяем в бите корректности EEPROM
#define INITMODE 0       // с этого режима будет старт, по умолчанию 0 (старт с - с черного цвета)
#define INITLEN MAX_LEDS // Размер гирлянды при старте
#define INITDEL 0        // размер задержки при старте в миллисекундах

uint16_t meshdelay; // Timer for the notamesh. Works with INITDEL.

uint8_t ledMode = 0; // номер текущего режима
#if CHANGE_ON == 1
uint8_t newMode = 0; // номер нового режима
#if MAX_LEDS < 255
uint8_t stepMode = MAX_LEDS; // Текущий шаг перехода от нового режима к старому
#else
uint16_t stepMode = MAX_LEDS; // Текущий шаг перехода от нового режима к старому
#endif
#endif

uint8_t demorun = DEMO_MODE;
#if RUNNING_FIRE > 0
#define MAX_MODE 122 // Maximum number of modes.
#else
#define MAX_MODE 42 // Maximum number of modes.
#endif

#ifndef EORDER
uint8_t eorderIndex = 2; // сохраненная очередность цветов, если она не задана жестко макросом EORDER
#endif

uint8_t allfreq = 32; // Меняет частоту. Переменная для эффектов one_sin_pal и two_sin.
uint8_t bgclr = 0;    // Общий цвет фона. Переменная для эффектов matrix_pal и one_sin_pal.
uint8_t bgbri = 0;    // Общая фоновая яркость. Переменная для эффектов matrix_pal и one_sin_pal.

// Структура хранения расширенных настроек
#pragma pack(push, 1)
typedef union
{
  struct
  {
    bool Glitter : 1;    // Флаг включения блеска
    bool Background : 1; // Флаг включения заполнения фона
    bool Candle : 1;     // Флаг включения свечей
    bool rezerv0 : 1;    // Зарезервировано
    bool rezerv1 : 1;    // Зарезервировано
    bool rezerv2 : 1;    // Зарезервировано
    bool rezerv3 : 1;    // Зарезервировано
    bool rezerv4 : 1;    // Зарезервировано
  };
  unsigned char Byte;
} ExtendedFlags;
#pragma pack(pop)

ExtendedFlags extFlag; // Флаги расширенных настроек

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
uint8_t randSpark = 0;
#endif

long summ = 0;

// ===================================================

void setOff(uint8_t &x)
{
  if (x < 100)
    x += 100;
}

void setOn(uint8_t &x)
{
  if (x >= 100)
    x -= 100;
}

int qsubd(size_t x, size_t b)
{
  return ((x > b) ? wavebright : 0);
}

int qsuba(size_t x, size_t b)
{
  return ((x > b) ? x - b : 0);
}

// ===================================================

#if SAVE_EEPROM
void eeprom_init()
{
  readStrandLen();
  ledMode = read_eeprom_8(EEPROM_INDEX_FOR_STARTMODE);

  // проверка правильности в EEPROM байта корректности записи
  if ((read_eeprom_8(EEPROM_INDEX_FOR_ISINIT) != INITVAL) ||
      (numLeds > MAX_LEDS) ||
      ((ledMode > MAX_MODE) && (ledMode != 100)))
  { // Не корректен
    write_eeprom_8(EEPROM_INDEX_FOR_STARTMODE, INITMODE);
    writeStrandLen();
    write_eeprom_8(EEPROM_INDEX_FOR_STRANDEL, INITDEL);

    extFlag.Glitter = GLITER_ON;
    extFlag.Background = BACKGR_ON;
    extFlag.Candle = CANDLE_ON;
    write_eeprom_8(EEPROM_INDEX_FOR_EXTFLAG, extFlag.Byte);
#if !defined(EORDER)
    write_eeprom_8(EEPROM_INDEX_FOR_EORDER, eorderIndex);
#endif
    write_eeprom_8(EEPROM_INDEX_FOR_ISINIT, INITVAL);

    ledMode = INITMODE;
    numLeds = INITLEN;
    meshdelay = INITDEL;
#if TOP_LENGTH
    write_eeprom_8(EEPROM_INDEX_FOR_TOPEFFECT, topEffectIndex);
#if TOP_LENGTH < 255
    write_eeprom_8(EEPROM_INDEX_FOR_TOPLENGTH, topLength);
#else
    write_eeprom_16(EEPROM_INDEX_FOR_TOPLENGTH, topLength);
#endif
#if BUTTONS_NUM > 2
    write_eeprom_8(EEPROM_INDEX_FOR_TOPCOLOR, topColorIndex);
    write_eeprom_8(EEPROM_INDEX_FOR_BGRCOLOR, bgrColorIndex);
#endif
#if BUTTONS_NUM > 3
    write_eeprom_8(EEPROM_INDEX_FOR_TOPDELAY, topDelay);
    write_eeprom_8(EEPROM_INDEX_FOR_TOPFADING, topFading);
#endif
#endif
  }
  else
  {
    extFlag.Byte = read_eeprom_8(EEPROM_INDEX_FOR_EXTFLAG); // Прочитаем расширенные настройки

    maxBright = read_eeprom_8(EEPROM_INDEX_FOR_BRIGHT);
#if !defined(EORDER)
    eorderIndex = read_eeprom_8(EEPROM_INDEX_FOR_EORDER);
    if (eorderIndex > 5)
    {
      eorderIndex = 0;
      write_eeprom_8(EEPROM_INDEX_FOR_EORDER, eorderIndex);
    }
#endif
    ledMode = read_eeprom_8(EEPROM_INDEX_FOR_STARTMODE);
    readStrandLen();

    meshdelay = read_eeprom_8(EEPROM_INDEX_FOR_STRANDEL);
#if TOP_LENGTH
    topEffectIndex = read_eeprom_8(EEPROM_INDEX_FOR_TOPEFFECT);
    if (topEffectIndex > 3)
    {
      topEffectIndex = TOP_EFFECT;
      write_eeprom_8(EEPROM_INDEX_FOR_TOPEFFECT, topEffectIndex);
    }
#if TOP_LENGTH < 255
    topLength = read_eeprom_8(EEPROM_INDEX_FOR_TOPLENGTH);
#else
    write_eeprom_16(EEPROM_INDEX_FOR_TOPLENGTH, topLength);
#endif
    if (topLength > TOP_LENGTH)
    {
      topLength = TOP_LENGTH;
#if TOP_LENGTH < 255
      write_eeprom_8(EEPROM_INDEX_FOR_TOPLENGTH, topLength);
#else
      write_eeprom_16(EEPROM_INDEX_FOR_TOPLENGTH, topLength);
#endif
    }
#if BUTTONS_NUM > 2
    topColorIndex = read_eeprom_8(EEPROM_INDEX_FOR_TOPCOLOR);
    if (topColorIndex > 7)
    {
      topColorIndex = TOP_COLOR;
      write_eeprom_8(EEPROM_INDEX_FOR_TOPCOLOR, topColorIndex);
    }
    bgrColorIndex = read_eeprom_8(EEPROM_INDEX_FOR_BGRCOLOR);
    if (bgrColorIndex > 2)
    {
      bgrColorIndex = 0;
      write_eeprom_8(EEPROM_INDEX_FOR_BGRCOLOR, bgrColorIndex);
    }
#endif
#if BUTTONS_NUM > 3
    topDelay = read_eeprom_8(EEPROM_INDEX_FOR_TOPDELAY);
    if (topDelay > 250 || topDelay < 5)
    {
      topDelay = TOP_DELAY;
      write_eeprom_8(EEPROM_INDEX_FOR_TOPDELAY, topDelay);
    }
    topFading = read_eeprom_8(EEPROM_INDEX_FOR_TOPFADING);
    if (topFading == 0 || topFading > 50)
    {
      topFading = TOP_FADING;
      write_eeprom_8(EEPROM_INDEX_FOR_TOPFADING, topFading);
    }
#endif
#endif
  }
}
#endif

#if TOP_LENGTH > 0
void top()
{
  if (topLength == 0)
  {
    return;
  }

  CRGB top_color;

#if BUTTONS_NUM > 2
  static const uint32_t PROGMEM color_of_number[] = {
      0xFF0000, // красный (Red)
      0xFF4500, // оранжевый (Orange)
      0xFFCC00, // желтый (Yellow)
      0x00FF00, // зеленый (Green)
      0x00FFFF, // голубой (Blue)
      0x0000FF, // синий (Indigo)
      0x9600D7, // фиолетовый (Violet)
      0xFFFFFF, // белый (White)
  };

  top_color = pgm_read_dword(&color_of_number[topColorIndex]);
#else
  top_color = TOP_COLOR;
#endif

  if (topEffectIndex == 0)
  {
    fill_solid(&leds[numLeds - topLength], topLength, set_new_eorder(top_color));
  }
  else
  {
#if MAX_LEDS < 255
    static uint8_t x;
#else
    static uint16_t x;
#endif

    fadeToBlackBy(&leds[numLeds - topLength], topLength, topFading); // Затухание к черному
    EVERY_N_MILLIS_I(toptimer, topDelay)
    { // Sets the original delay time.

      switch (topEffectIndex)
      {
      case 1:
#if TOP_LENGTH < 255
        leds[numLeds - topLength + random8(0, topLength)] = set_new_eorder(top_color);
#else
        leds[numLeds - topLength + random16(0, topLength)] = set_new_eorder(top_color);
#endif
        break;
      case 2:
        if ((x <= numLeds - topLength) || (x >= numLeds))
        {
          x = numLeds - 1;
        }
        else
        {
          x--;
        }
        leds[x] = set_new_eorder(top_color);
        break;
      default:
        if ((x < numLeds - topLength) || (x >= numLeds - 1))
        {
          x = numLeds - topLength;
        }
        else
        {
          x++;
        }
        leds[x] = set_new_eorder(top_color);
        break;
      }
    }
  }
} // top()
#endif

CRGB set_new_eorder(CRGB _col)
{
#if !defined(EORDER)
  switch (eorderIndex)
  {
  case 1: // RBG
    return CRGB(_col.r, _col.b, _col.g);
  case 2: // GRB
    return CRGB(_col.g, _col.r, _col.b);
  case 3: // GBR
    return CRGB(_col.g, _col.b, _col.r);
  case 4: // BRG
    return CRGB(_col.b, _col.r, _col.g);
  case 5: // BGR
    return CRGB(_col.b, _col.g, _col.r);
  default: // по умолчанию выводить RGB
    return (_col);
  }
#else
  // если порядок задан жестко, вывести, не меняя
  return (_col);
#endif
}

#if CANDLE_KOL > 0
DEFINE_GRADIENT_PALETTE(candle_Pal){
    0, 255, 0, 0,        // red
    90, 255, 255, 255,   // full white
    180, 255, 255, 0,    // bright yellow
    255, 255, 255, 255}; // full white

void addCandle()
{
  uint16_t poz = polCandle;
  CRGBPalette16 myPal = candle_Pal;

  if ((numLeds - topLength) > CANDLE_KOL)
  {
    uint16_t kol = (numLeds - topLength) / CANDLE_KOL; // Количество свечей

    for (uint16_t x = 0; x < kol; x++)
    {
      if (poz < (numLeds - topLength))
      {
        leds[poz] = set_new_eorder(ColorFromPalette(myPal, random8(255)));
      }
      poz += CANDLE_KOL;
    }
  }
}
#endif

void addBackground()
{
  const uint8_t thrsh = 5; // пороговое значение для заливки

#if MAX_LEDS < 255
  uint8_t i;
#else
  uint16_t i;
#endif

#if BUTTONS_NUM > 2
  uint8_t bgr_color = bgrColorIndex;
#else
  uint8_t bgr_color = 0;
#endif

  for (i = 0; i < numLeds - topLength; i++)
  {
    if ((leds[i].r < thrsh) && (leds[i].g < thrsh) && (leds[i].b < thrsh))
    {
#if !defined(EORDER)
      switch (bgr_color)
      {
      case 0: // заливка фона голубым
        switch (eorderIndex)
        {
        case 0:
        case 2:
          leds[i].b += thrsh;
          break;
        case 1:
        case 3:
          leds[i].g += thrsh;
          break;
        case 4:
        case 5:
          leds[i].r += thrsh;
          break;
        }
        break;
      case 1: // заливка фона зеленым
        switch (eorderIndex)
        {
        case 0:
        case 5:
          leds[i].g += thrsh;
          break;
        case 1:
        case 4:
          leds[i].b += thrsh;
          break;
        case 2:
        case 3:
          leds[i].r += thrsh;
          break;
        }
        break;
      case 2: // заливка фона красным
        switch (eorderIndex)
        {
        case 0:
        case 1:
          leds[i].r += thrsh;
          break;
        case 2:
        case 4:
          leds[i].g += thrsh;
          break;
        case 3:
        case 5:
          leds[i].b += thrsh;
          break;
        }
        break;
        break;
      }
#else
      switch (bgr_color)
      {
      case 0: // заливка фона голубым
        leds[i].b += thrsh;
        break;
      case 1: // заливка фона зеленым
        leds[i].g += thrsh;
        break;
      case 2: // заливка фона красным
        leds[i].r += thrsh;
        break;
      }
#endif
    }
  }
}

void addGlitter(fract8 chanceOfGlitter)
{
  if (random8() < chanceOfGlitter)
  {
#if MAX_LEDS < 255
    leds[random8(numLeds - topLength)] += CRGB::White;
#else
    leds[random16(numLeds - topLength)] += CRGB::White;
#endif
  }
}

void sparkler(uint8_t n) // Бенгальский огонь
// 0 - нет эффектов
// 1 - Бенгальский огонь
// 2 - 1 яркий светодиод
// 3 - метеорит
// 4 - случайный эффект
{
  uint8_t kol = 3;

  if (kolLeds < 10)
    kol = kolLeds / 3;
  if (kol >= 2)
  {
    uint8_t nn = n;
    switch (nn)
    {
    case 1:
      for (uint8_t x = 0; x < kol; x++)
        leds[kolLeds - random8(kol * 2)] = CRGB::White;
      break; // Бенгальский
    case 2:
      leds[kolLeds - 1] = CRGB::White;
      break; // 1 яркий
    case 3:
      leds[kolLeds] = CRGB::White;
      leds[kolLeds - 1] = set_new_eorder(CRGB::Red);
      leds[kolLeds - 2] = set_new_eorder(CRGB::Violet);
      break; // Метеорит
    }
  }
}

#if BUTTONS_NUM
void btnHandler()
{
  {
    switch (btn1.getButtonState())
    {
    case BTN_ONECLICK:
      protocol = 1;
      command = BTN1_1;

      CTG_PRINTLN(F("BTN1 Click"));

      LED1_FleshH(1); // мигнуть светодиодом 1

      break;
    case BTN_DBLCLICK:
      protocol = 1;
      command = BTN1_2;

      CTG_PRINTLN(F("BTN1 DblClick"));

      LED1_FleshH(2); // мигнуть 2 раза светодиодом 1

      break;
    case BTN_LONGCLICK:
      protocol = 1;
      command = BTN1_PRESS;

      CTG_PRINTLN(F("BTN1 Step"));

      LED1_FleshL(1); // мигнуть  светодиодом 1

      break;
    }
  }
#if BUTTONS_NUM > 1
  {
    switch (btn2.getButtonState())
    {
    case BTN_ONECLICK:
      protocol = 1;
      command = BTN2_1;

      CTG_PRINTLN(F("BTN2 Click"));

      LED1_FleshH(1); // мигнуть светодиодом 1

      break;
    case BTN_DBLCLICK:
      protocol = 1;
      command = BTN2_2;

      CTG_PRINTLN(F("BTN2 DblClick"));

      LED1_FleshH(2); // мигнуть 2 раза светодиодом 1

      break;
    case BTN_LONGCLICK:
      protocol = 1;
      command = BTN2_PRESS;

      CTG_PRINTLN(F("BTN2 Step"));

      LED1_FleshL(1); // мигнуть  светодиодом 1

      break;
    }
  }
#if BUTTONS_NUM > 2
  {
    switch (btn3.getButtonState())
    {
    case BTN_ONECLICK:
      protocol = 1;
      command = BTN3_1;

      CTG_PRINTLN(F("BTN3 Click"));

      LED1_FleshH(1); // мигнуть светодиодом 1

      break;
    case BTN_DBLCLICK:
      protocol = 1;
      command = BTN3_2;

      CTG_PRINTLN(F("BTN3 DblClick"));

      LED1_FleshH(2); // мигнуть 2 раза светодиодом 1

      break;
    case BTN_LONGCLICK:
      protocol = 1;
      command = BTN3_PRESS;

      CTG_PRINTLN(F("BTN3 Step"));

      LED1_FleshL(1); // мигнуть  светодиодом 1

      break;
    }
  }
#if BUTTONS_NUM > 3
  {
    switch (btn4.getButtonState())
    {
    case BTN_ONECLICK:
      protocol = 1;
      command = BTN4_1;

      CTG_PRINTLN(F("BTN4 Click"));

      LED1_FleshH(1); // мигнуть светодиодом 1

      break;
    case BTN_DBLCLICK:
      protocol = 1;
      command = BTN4_2;

      CTG_PRINTLN(F("BTN4 DblClick"));

      LED1_FleshH(2); // мигнуть 2 раза светодиодом 1

      break;
    case BTN_LONGCLICK:
      protocol = 1;
      command = BTN4_PRESS;

      CTG_PRINTLN(F("BTN4 Step"));

      LED1_FleshL(1); // мигнуть  светодиодом 1

      break;
    }
  }
#endif
#endif
#endif
}
#endif

#if LED_ON > 0
// мигание индикаторным светодиодом
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

#if SAVE_EEPROM
void readStrandLen()
{
  numLeds = read_eeprom_8(EEPROM_INDEX_FOR_STRANDLEN);
#if MAX_LEDS < 255
  if (read_eeprom_8(EEPROM_INDEX_FOR_STRANDLEN + 1))
  { // Если почему-то светодиодов больше чем размер переменной
    numLeds = MAX_LEDS;
    writeStrandLen();
  }
#else
  numLeds += (uint16_t)read_eeprom_8(EEPROM_INDEX_FOR_STRANDLEN + 1) << 8;
#endif
  if (numLeds > MAX_LEDS)
  {
    numLeds = MAX_LEDS;
    writeStrandLen();
  }
}

void writeStrandLen()
{
#if MAX_LEDS < 255
  write_eeprom_8(EEPROM_INDEX_FOR_STRANDLEN, numLeds);
  write_eeprom_8(EEPROM_INDEX_FOR_STRANDLEN + 1, 0);
#else
  write_eeprom_8(EEPROM_INDEX_FOR_STRANDLEN, (uint16_t)(numLeds) & 0x00ff);
  write_eeprom_8(EEPROM_INDEX_FOR_STRANDLEN + 1, (uint16_t)(numLeds) >> 8);
#endif
}
#endif
