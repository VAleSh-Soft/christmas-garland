#include <FastLED.h> // https://github.com/FastLED/FastLED

#if FASTLED_VERSION < 3001000
#error "Requires FastLED 3.1 or later; check github for latest code."
#endif

#include "setting.h"
#include "src/_leds.h"

// ===================================================

// Функции поддержки
#include "src/addings.h"

#if SAVE_EEPROM
#include "src/_eeprom.h"
#endif

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

#if BUTTONS_NUM
// Работа с кнопками
#include "src/getirl.h"
#endif

#if RUNNING_FIRE
#include "src/running_fire.h"
#endif

// ===================================================

void strobe_mode(uint8_t newMode, bool mc);
void demo_check();

#if LED_ON > 0
void ledsFlash(uint8_t led_idx, uint8_t &count);
#endif

// ===================================================

void setup()
{
#if BUTTONS_NUM > 0
  btn1.setVirtualClickOn(true);
  btn1.setLongClickMode(LCM_CLICKSERIES);
#if BUTTONS_NUM > 1
  btn2.setVirtualClickOn(true);
#endif
#if BUTTONS_NUM > 2
  btn3.setVirtualClickOn(true);
#endif
#if BUTTONS_NUM > 3
  btn4.setVirtualClickOn(true);
#endif
#if BUTTONS_NUM == 2
  btn2.setLongClickMode(LCM_CLICKSERIES);
#elif BUTTONS_NUM == 3
  btn3.setLongClickMode(LCM_CLICKSERIES);
  btn2.setLongClickMode(LCM_ONLYONCE);
#elif BUTTONS_NUM > 3
  btn4.setLongClickMode(LCM_CLICKSERIES);
  btn2.setLongClickMode(LCM_ONLYONCE);
  btn3.setLongClickMode(LCM_ONLYONCE);
#endif
#endif

#if LED_ON > 0
  pinMode(LED1_PIN, OUTPUT); // пин первого светодиода
#if LED_ON > 1
  pinMode(LED2_PIN, OUTPUT); // пин второго светодиода
#endif
  LED1_On; // Включим светодиод
#endif

#if LOG_ON
  Serial.begin(SERIAL_BAUDRATE); // Setup serial baud rate
#endif

  CTG_PRINTLN(F(" "));
  CTG_PRINTLN(F("---SETTING UP---"));

#if SAVE_EEPROM
  // если задано сохранение настроек в EEPROM
  eeprom_init();
#else
  // если настройки в EEPROM не сохраняются

  extFlag.Glitter = GLITER_ON;    // Флаг включения блеска
  extFlag.Background = BACKGR_ON; // Флаг включения заполнения фона
  extFlag.Candle = CANDLE_ON;     // Флаг включения свечей

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
  numLeds = MAX_LEDS;
  meshdelay = INITDEL;
#endif

  if (numLeds < (TOP_LENGTH + 1))
  {
    numLeds = (TOP_LENGTH + 1); // Проверка
  }

  fastled_init();

  random16_set_seed(4832); // Рандомайзер
  random16_add_entropy(analogRead(2));

  CTG_PRINT(F("Initial delay: "));
  CTG_PRINT(meshdelay * 100);
  CTG_PRINTLN(F("ms delay."));
  CTG_PRINT(F("Initial strand length: "));
  CTG_PRINT(numLeds);
  CTG_PRINTLN(F(" LEDs"));
  print_eorder();
  CTG_PRINTLN(F("EXTEND Setup"));
  if (extFlag.Glitter)
    CTG_PRINTLN(F("Glitter On"));
  else
    CTG_PRINTLN(F("Glitter Off"));
  if (extFlag.Background)
    CTG_PRINTLN(F("Background On"));
  else
    CTG_PRINTLN(F("Background Off"));
  if (extFlag.Candle)
    CTG_PRINTLN(F("Candle On"));
  else
    CTG_PRINTLN(F("Candle Off"));

#if BLACKSTART == 1
  solid = CRGB::Black; // Запуск с пустого поля
#if CHANGE_ON == 1
  newMode = ledMode;
  stepMode = 1;
#endif
  ledMode = 255;
#endif

  gCurrentPalette = gGradientPalettes[0];
  gTargetPalette = gGradientPalettes[0];
  strobe_mode(ledMode, 1); // инициализация первой последовательности

  if (DEMO_MODE)
  {
    CTG_PRINT(F("DEMO MODE "));
    CTG_PRINTLN(DEMO_MODE);
  }
  CTG_PRINTLN(F("---SETUP COMPLETE---"));

#if LED_ON
  LED1_Off; // Выключим светодиод
#endif
}

void loop()
{

#if BUTTONS_NUM
  getirl(); // Обработка кнопок
#endif

  demo_check(); // Работа если включен демонстрационный режим

  EVERY_N_MILLISECONDS(50)
  { // Плавный переход от одной палитры в другую
#if CHANGE_ON == 1
    if (stepMode == MAX_LEDS)
#endif
      nblendPaletteTowardPalette(gCurrentPalette, gTargetPalette, PALETTE_SPEED);

#if LED_ON > 0 // мигаем светодиодом 1
    if (led1Flesh > 0)
    {
      ledsFlash(1, led1Flesh);
    }
#if LED_ON > 1 // мигаем светодиодом 2
    if (led2Flesh > 0)
    {
      ledsFlash(2, led2Flesh);
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

        CTG_PRINT(F("New Palette: "));
        CTG_PRINTLN(gCurrentPaletteNumber);
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
    kolLeds = numLeds - TOP_LENGTH; // Выводим Эффект на все светодиоды
    strobe_mode(ledMode, 0);        // отобразить эффект;
#if CHANGE_ON == 1
    if ((stepMode < (numLeds - TOP_LENGTH)) && ((ledMode < 220) || (ledMode >= 230)))
    {                     // требуется наложить новый эффект
      kolLeds = stepMode; // Выводим Эффект на все светодиоды
      if (stepMode > 10)
        strobe_mode(newMode, 0); // отобразить эффект;
#if CHANGE_SPARK == 4
      sparkler(randSpark);
#else
      sparkler(CHANGE_SPARK); // бенгальский огонь
#endif
    }
#endif
  }

#if CHANGE_ON == 1 // Включена плавная смена эффектов
  if (stepMode < (numLeds - TOP_LENGTH))
  {                                                                        // есть шаги, исполняем
    uint16_t change_time = (1000L * CHANGE_TIME) / (numLeds - TOP_LENGTH); // время в мСек на каждый светодиод
    if (change_time < 20)
    {
      change_time = 20;
    }
    //        static uint8_t change_increment = (uint32_t)change_time * (numLeds-TOP_LENGTH) / (1000L *CHANGE_TIME)+1;
    EVERY_N_MILLISECONDS(change_time)
    { // Движение плавной смены эффектов
      //            if (stepMode > 10) stepMode += change_increment;
      //            else
      stepMode++;
      if (stepMode == 10)
      {
        strobe_mode(newMode, 1);
      }
      if (stepMode >= (numLeds - TOP_LENGTH))
      {
        ledMode = newMode;
        stepMode = MAX_LEDS - TOP_LENGTH;

        CTG_PRINTLN(F("End setMode"));
      }
      nblendPaletteTowardPalette(gCurrentPalette, gTargetPalette, PALETTE_SPEED);
    }
  }
#endif

#if TOP_LENGTH > 0
  top(); // Обработка конца гирлянды
#endif
  if (extFlag.Glitter)
  {
    addglitter(10); // блеск, если включен
  }
#if CANDLE_KOL > 0
  if (extFlag.Candle)
  {
    addcandle();
  }
#endif

  if (extFlag.Background)
  {
    addbackground(); // Включить заполнение черного цвета фоном
  }

  BtnHandler(); // Обработчик нажатий кнопок

  LEDS.show();
}

void strobe_mode(uint8_t mode, bool mc)
{ // mc == 0 - работа, mc == 1 - смена режима

  if (mc)
  {
    fill_solid(leds, numLeds - TOP_LENGTH, CRGB(0, 0, 0)); // очистить гирлянду при смене режима

    CTG_PRINT(F("Mode: "));
    CTG_PRINTLN(mode);
    CTG_PRINTLN(millis());

#if PALETTE_TIME > 0
    if (palchg == 0)
      palchg = 3;
#else
    if (palchg == 0)
      palchg = 1;
#endif
  }

  switch (mode)
  { // При старте нового режима инициализируются его переменные
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
  case 201:
    fill_solid(leds, MAX_LEDS, CRGB::Black);
    fill_solid(leds, meshdelay, CRGB(255, 255, 255));
    break; // Зажечь гирлянду длиной meshdelay
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
      CTG_PRINTLN(F("Change palette off"));
    else if (palchg == 1)
      CTG_PRINTLN(F("Change palette Stop"));
    else if (palchg == 3)
      CTG_PRINTLN(F("Change palette ON"));
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
        newMode = random8(0, MAX_MODE); // демо 2
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
        if (newMode >= MAX_MODE)
          newMode = 0; // демо 1
        else
          newMode++;
        break;
      }
      stepMode = 1;
#if CHANGE_SPARK == 4
      randSpark = random8(3) + 1;
#endif

      CTG_PRINTLN(F("Start setMode"));

#else
      gTargetPalette = gGradientPalettes[gCurrentPaletteNumber]; // Применим палитру

      CTG_PRINT(F("New Palette: "));
      CTG_PRINTLN(gCurrentPaletteNumber);

      switch (demorun)
      {
      case 2:
        ledMode = random8(0, MAX_MODE); // демо 2
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
        if (ledMode >= MAX_MODE)
          ledMode = 0; // демо 1
        else
          ledMode++;
        break;
      }
      strobe_mode(ledMode, 1); // Does NOT reset to 0.
#if CANDLE_KOL > 0
      polCandle = random8(CANDLE_KOL);
#endif
#endif
    }
  }
}

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
