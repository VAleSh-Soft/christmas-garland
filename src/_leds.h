/**
 * @file _leds.h
 *
 * Все, что связано с работой гирлянды
 *
 */
#pragma once

#include "../setting.h"
#include "function.h"
#include "_eeprom.h"
#include <FastLED.h>

// ===================================================

// инициализация FastLED
void fastled_init();
// вывод цветности гирлянды в Сериал
void print_eorder();
#if SAVE_EEPROM
#if BUTTONS_NUM > 1 && CAN_CHANGE_NUMLEDS
// установка количества светодиодов в гирлянде
void setLengthOfGarland();
#endif
#if !defined(EORDER) && BUTTONS_NUM > 0
// настройка порядка следования цветов в чипе
void set_eorder();
#endif
#if BUTTONS_NUM > 2 && TOP_LENGTH
void set_top_setting();
#endif
#endif

// ===================================================

void fastled_init()
{
  LEDS.setBrightness(maxBright);
#if (defined(POWER_I) && defined(POWER_V))
  if (POWER_I > 0)
  {
    LEDS.setMaxPowerInVoltsAndMilliamps(POWER_V, POWER_I);
  }
#endif

  int num_leds = numLeds;
#if BUTTONS_NUM > 1 && CAN_CHANGE_NUMLEDS
  if (!digitalRead(BTN2_PIN))
  {
    /* на максимально возможное количество светодиодов гирлянду инициализируем
     * только если сейчас будем настраивать ее длину; иначе инициализируем на
     * сохраненное количество - экономим память, на всякий случай )) */
    num_leds = MAX_LEDS;
  }
#endif

#if defined(EORDER)

#if defined(LED_CLK_PIN)
  LEDS.addLeds<CHIPSET, LED_DATA_PIN, LED_CLK_PIN, EORDER>(leds, num_leds);
#else
  LEDS.addLeds<CHIPSET, LED_DATA_PIN, EORDER>(leds, num_leds);
#endif

#else

#if defined(LED_CLK_PIN)
  LEDS.addLeds<CHIPSET, LED_DATA_PIN, LED_CLK_PIN, RGB>(leds, num_leds);
#else
  LEDS.addLeds<CHIPSET, LED_DATA_PIN, RGB>(leds, num_leds);
#endif

#endif

#if SAVE_EEPROM
#if BUTTONS_NUM > 0
  // настройка следования цветов при зажатой кнопке 1
  if (!digitalRead(BTN1_PIN))
  {
    set_eorder();
  }

#endif

#if BUTTONS_NUM > 1 && CAN_CHANGE_NUMLEDS
  // если кнопок больше одной, доступна настройка длины гирлянды
  if (!digitalRead(BTN2_PIN))
  {
    setLengthOfGarland();
  }
#endif

#if BUTTONS_NUM > 2 && TOP_LENGTH
  if (!digitalRead(BTN3_PIN))
  {
    set_top_setting();
  }
#endif

#if BUTTONS_NUM > 3

#endif
#endif
}

void print_eorder()
{
  CTG_PRINT(F("LEDS EORDER: "));
#if !defined(EORDER)
  switch (eorderIndex)
  {
  case 0:
    CTG_PRINTLN(F("RGB"));
    break;
  case 1:
    CTG_PRINTLN(F("RBG"));
    break;
  case 2:
    CTG_PRINTLN(F("GRB"));
    break;
  case 3:
    CTG_PRINTLN(F("GBR"));
    break;
  case 4:
    CTG_PRINTLN(F("BRG"));
    break;
  case 5:
    CTG_PRINTLN(F("BGR"));
    break;
  default:
    CTG_PRINTLN(F("Unknown"));
    break;
  }
#else
  switch (EORDER)
  {
  case 0012:
    CTG_PRINTLN(F("RGB"));
    break;
  case 0121:
    CTG_PRINTLN(F("RBG"));
    break;
  case 0102:
    CTG_PRINTLN(F("GRB"));
    break;
  case 0120:
    CTG_PRINTLN(F("GBR"));
    break;
  case 0201:
    CTG_PRINTLN(F("BRG"));
    break;
  case 0210:
    CTG_PRINTLN(F("BGR"));
    break;
  }
#endif
}

#if SAVE_EEPROM

#if BUTTONS_NUM && (TOP_LENGTH || CAN_CHANGE_NUMLEDS || !defined(EORDER))
void _start_mode(shButton &btn)
{
  /* отработка первого клика, чтобы не мешался в настройках; если этого не
   * сделать, то в момент входа в режим настройки (напомню - кнопка в этот
   * момент удерживается нажатой, но ее отслеживание пока не началось, т.к.
   * мы по сути еще не вышли из функции setup()) будет зафиксировано состяние
   * BTN_DOWN, что может привести к несанкционированному изменению параметра;
   * вот это событие мы здесь и ждем перед тем, как запустить код собственно
   * настройки параметра
   */
  while (btn.getButtonState() != BTN_DOWN)
    ;
}
#endif

#if BUTTONS_NUM > 2
void print_bgr_color()
{
  CTG_PRINT(F("Background Fill Color: "));
  switch (bgrColorIndex)
  {
  case 0:
    CTG_PRINTLN(F("Blue"));
    break;
  case 1:
    CTG_PRINTLN(F("Green"));
    break;
  case 2:
    CTG_PRINTLN(F("Red"));
    break;
  default:
    CTG_PRINTLN(F("Unknown"));
    break;
  }
}
#endif

#if BUTTONS_NUM > 1
static void fill_solid_garland(bool can_print = true)
{
  LEDS.setBrightness(10);
  fill_solid(leds, MAX_LEDS, CRGB::Black);

#if BUTTONS_NUM > 2
  switch (bgrColorIndex)
  {
  case 0:
    fill_solid(leds, numLeds, set_new_eorder(CRGB::Blue));
    break;
  case 1:
    fill_solid(leds, numLeds, set_new_eorder(CRGB::Green));
    break;
  case 2:
    fill_solid(leds, numLeds, set_new_eorder(CRGB::Red));
    break;
  }
#else
  fill_solid(leds, numLeds, set_new_eorder(CRGB::Blue));
#endif

  if (can_print)
  {
    CTG_PRINT(F("Length garland: "));
    CTG_PRINTLN(numLeds);
  }

  LEDS.show();
}

#if CAN_CHANGE_NUMLEDS
static void print_length_of_garland()
{
  CTG_PRINT(F("Length garland: "));
  CTG_PRINTLN(numLeds);
}

void setLengthOfGarland()
{
  CTG_PRINTLN(F("Mode for changing the length of the garland"));
  print_length_of_garland();
#if BUTTONS_NUM > 2
  void print_bgr_color();
#endif
  CTG_PRINTLN();

  fill_solid_garland();

  _start_mode(btn2);

  // опрос кнопок
  while (true)
  {
    switch (btn1.getButtonState())
    {
    case BTN_DOWN:
      if (numLeds < MAX_LEDS)
      {
        numLeds++;
        fill_solid_garland();
        print_length_of_garland();
      }
      break;
    case BTN_LONGCLICK:
      if (numLeds < MAX_LEDS - 10)
      {
        numLeds += 10;
        fill_solid_garland();
        print_length_of_garland();
      }
      break;
    }

#if BUTTONS_NUM == 2
    shButton *btn_down = &btn2;
#elif BUTTONS_NUM == 3
    shButton *btn_down = &btn3;
#elif BUTTONS_NUM > 3
    shButton *btn_down = &btn4;
#endif
    switch (btn_down->getButtonState())
    {
    case BTN_DOWN:
      if (numLeds > 1)
      {
        numLeds--;
        fill_solid_garland();
        print_length_of_garland();
      }
      break;
    case BTN_LONGCLICK:
      if (numLeds > 10)
      {
        numLeds -= 10;
        fill_solid_garland();
        print_length_of_garland();
      }
      break;
    }

    // при отпускании кнопки сохранить длину в EEPROM
    if (btn1.getLastState() == BTN_UP ||
        btn_down->getLastState() == BTN_UP)
    {
      writeStrandLen();
    }

#if BUTTONS_NUM > 2
    if (btn2.getButtonState() == BTN_DOWN)
    {
      // смена цвета заливки фона
      if (++bgrColorIndex > 2)
      {
        bgrColorIndex = 0;
      }
      write_eeprom_8(EEPROM_INDEX_FOR_BGRCOLOR, bgrColorIndex);
      fill_solid_garland(false);

      print_bgr_color();
    }

#endif
  }
}
#endif
#endif

#if !defined(EORDER) && BUTTONS_NUM > 0
static void show_rgb()
{
  CRGB exmpl[] = {CRGB::Red, CRGB::Green, CRGB::Blue};
  for (uint8_t i = 0; i < 3; i++)
  {
    leds[i] = set_new_eorder(exmpl[i]);
  }
  LEDS.show();
}

void set_eorder()
{
  CTG_PRINTLN(F("EORDER change mode for LEDs"));

  _start_mode(btn1);

  eorderIndex = 0;
  write_eeprom_8(EEPROM_INDEX_FOR_EORDER, eorderIndex);
  fill_solid(leds, MAX_LEDS, CRGB::Black);
  show_rgb();

  // опрос кнопок
  while (true)
  {
    if (btn1.getButtonState() == BTN_DOWN)
    {
      if (++eorderIndex > 5)
      {
        eorderIndex = 0;
      }
      write_eeprom_8(EEPROM_INDEX_FOR_EORDER, eorderIndex);
      print_eorder();
      show_rgb();
    }
  }
}
#endif

#if BUTTONS_NUM > 2 && TOP_LENGTH
static void print_top_length()
{
  CTG_PRINT(F("Top length: "));
  CTG_PRINTLN(topLength);
}

static void save_top_length()
{
#if TOP_LENGTH < 255
  write_eeprom_8(EEPROM_INDEX_FOR_TOPLENGTH, topLength);
#else
  write_eeprom_16(EEPROM_INDEX_FOR_TOPLENGTH, topLength);
#endif

  print_top_length();
}

static void print_top_delay()
{
  CTG_PRINT(F("Top delay: "));
  CTG_PRINTLN(topDelay);
}

static void print_top_fading()
{
  CTG_PRINT(F("Top fading: "));
  CTG_PRINTLN(topFading);
}

static void print_top_color()
{
  CTG_PRINT(F("Top color: "));
  switch (topColorIndex)
  {
  case 0:
    CTG_PRINTLN(F("Red"));
    break;
  case 1:
    CTG_PRINTLN(F("Orange"));
    break;
  case 2:
    CTG_PRINTLN(F("Yellow"));
    break;
  case 3:
    CTG_PRINTLN(F("Green"));
    break;
  case 4:
    CTG_PRINTLN(F("Blue"));
    break;
  case 5:
    CTG_PRINTLN(F("Indigo"));
    break;
  case 6:
    CTG_PRINTLN(F("Violet"));
    break;
  case 7:
    CTG_PRINTLN(F("White"));
    break;
  default:
    CTG_PRINTLN(F("Unknown"));
    break;
  }
}

void set_top_setting()
{
  CTG_PRINTLN(F("Mode for changing the setting for top of the garland"));
  print_top_length();
  print_top_color();
  print_top_delay();
  print_top_fading();
  CTG_PRINTLN();

  fill_solid_garland(false);
  top();
  LEDS.show();

  _start_mode(btn3);

  // опрос кнопок
  while (true)
  {
#if BUTTONS_NUM == 3
    shButton *btn_down = &btn3;
#elif BUTTONS_NUM > 3
    shButton *btn_down = &btn4;
#endif

    btn1.getButtonState();
    btn_down->getButtonState();

    // размер вершины
    if (btn1.getLastState() == BTN_DOWN || btn_down->getLastState() == BTN_DOWN)
    {
      if (btn1.getLastState() == BTN_DOWN)
      {
        if (topLength < TOP_LENGTH)
        {
          topLength++;
          save_top_length();
        }
      }
      else if (topLength > 0)
      {
        topLength--;
        save_top_length();
      }

      // сразу заполним вершину текущим цветом для наглядности
      fill_solid_garland(false);
      uint8_t x = topEffectIndex;
      topEffectIndex = 0;
      top();
      topEffectIndex = x;
    }

    switch (btn2.getButtonState())
    {
    // тип заливки вершины - сплошной, сверху вниз, снизу вверх или случайное мерцание
    case BTN_ONECLICK:
      if (++topEffectIndex > 3)
      {
        topEffectIndex = 0;
      }
      write_eeprom_8(EEPROM_INDEX_FOR_TOPEFFECT, topEffectIndex);

      CTG_PRINT(F("Top effect: "));
      CTG_PRINTLN(topEffectIndex);
      break;
    // цвет заливки вершины
    case BTN_LONGCLICK:
      if (++topColorIndex > 7)
      {
        topColorIndex = 0;
      }
      write_eeprom_8(EEPROM_INDEX_FOR_TOPCOLOR, topColorIndex);

      print_top_color();
      break;
    }

#if BUTTONS_NUM > 3
    // изменение величины затухания вершины (topFading)
    static bool flag = false;
    static bool to_up = false;
    static bool start = false;

    btn3.setLongClickMode(LCM_CLICKSERIES);
    btn3.setTimeoutOfLongClick(500);

    switch (btn3.getButtonState())
    {
    case BTN_LONGCLICK:
      if (start)
      {
        flag = true;
        if (to_up)
        {
          if (topFading <= 40)
          {
            topFading++;
            write_eeprom_8(EEPROM_INDEX_FOR_TOPFADING, topFading);
            print_top_fading();
          }
        }
        else
        {
          if (topFading > 1)
          {
            topFading--;
            write_eeprom_8(EEPROM_INDEX_FOR_TOPFADING, topFading);
            print_top_fading();
          }
        }
      }
      break;
    case BTN_UP:
      // устанавливаем флаг начала изменений
      start = true;
      // при отпускании кнопки меняем флаг направления изменения только при условии, что было удержание кнопки, а не просто клик
      if (flag)
      {
        flag = false;
        to_up = !to_up;
      }
      break;
    }
#endif

    top();
    LEDS.show();
  }
}
#endif
#endif