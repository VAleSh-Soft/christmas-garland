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
void led2_blink();
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
#if BUTTONS_NUM > 3 && POWER_I && POWER_V
void setMaxPowerConsumption();
#endif
#endif

// ===================================================

void fastled_init()
{
  LEDS.setBrightness(maxBright);
#if (defined(POWER_I) && defined(POWER_V))
  if (powerI > 0)
  {
    LEDS.setMaxPowerInVoltsAndMilliamps(powerV, powerI * 100ul);
  }
#endif

  int num_leds = numLeds;
#if BUTTONS_NUM > 1 && CAN_CHANGE_NUMLEDS
  if (!digitalRead(BTN2_PIN))
  {
    /* на максимально возможное количество светодиодов гирлянду инициализируем
     * только если сейчас будем настраивать ее длину; иначе инициализируем на
     * сохраненное количество - экономим память, меньше шансов зависнуть )) */
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
#if BUTTONS_NUM > 0 && !defined(EORDER)
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
  // если кнопок больше двух, доступна настройка вершины гирлянды
  if (!digitalRead(BTN3_PIN))
  {
    set_top_setting();
  }
#endif

#if BUTTONS_NUM > 3 && POWER_I && POWER_V
  // если кнопок четыре, доступна настройка потребляемой мощности
  if (!digitalRead(BTN4_PIN))
  {
    setMaxPowerConsumption();
  }
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

void led2_blink()
{
#if LED_ON > 1
  digitalWrite(LED2_PIN, HIGH);
  delay(5);
  digitalWrite(LED2_PIN, LOW);
#endif
}

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

void _set_num_leds(bool to_up, uint8_t step = 1)
{
  numLeds += (to_up) ? step : -step;
  led2_blink();
  fill_solid_garland();
  print_length_of_garland();
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
    btn1.getButtonState();
#if BUTTONS_NUM == 2
    shButton *btn_down = &btn2;
#elif BUTTONS_NUM == 3
    btn2.getButtonState();
    shButton *btn_down = &btn3;
#elif BUTTONS_NUM > 3
    btn2.getButtonState();
    btn3.getButtonState();
    shButton *btn_down = &btn4;
#endif
    btn_down->getButtonState();

    switch (btn1.getLastState())
    {
    case BTN_DOWN:
    case BTN_DBLCLICK:
      if (numLeds < MAX_LEDS)
      {
        _set_num_leds(true);
      }
      break;
    case BTN_LONGCLICK:
      if (numLeds < MAX_LEDS - 10)
      {
        _set_num_leds(true, 10);
      }
      break;
    }

    switch (btn_down->getLastState())
    {
    case BTN_DOWN:
    case BTN_DBLCLICK:
      if (numLeds > 1)
      {
        _set_num_leds(false);
      }
      break;
    case BTN_LONGCLICK:
      if (numLeds > 10)
      {
        _set_num_leds(false, 10);
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
    switch (btn2.getLastState())
    {
    case BTN_DOWN:
    case BTN_DBLCLICK:
      // смена цвета заливки фона
      if (++bgrColorIndex > 2)
      {
        bgrColorIndex = 0;
      }
      led2_blink();
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
    switch (btn1.getButtonState())
    {
    case BTN_DOWN:
    case BTN_DBLCLICK:
      if (++eorderIndex > 5)
      {
        eorderIndex = 0;
      }
      led2_blink();
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

void fill_solid_for_top()
{
  fill_solid_garland(false);
  uint8_t x = topEffectIndex;
  topEffectIndex = 0;
  top();
  topEffectIndex = x;
}

void _set_top_length(bool to_up)
{
  (to_up) ? topLength++ : topLength--;
  led2_blink();
  save_top_length();
  fill_solid_for_top();
}

void _set_top_delay(bool to_up)
{
  topDelay += (to_up) ? 5 : -5;
  led2_blink();
  write_eeprom_8(EEPROM_INDEX_FOR_TOPDELAY, topDelay);
  print_top_delay();
}

void set_top_setting()
{
  LEDS.setBrightness(10);
  CTG_PRINTLN(F("Mode for changing the setting for top of the garland"));
  print_top_length();
  print_top_color();
  print_top_delay();
  print_top_fading();
  CTG_PRINTLN();

  fill_solid_for_top();
  LEDS.show();

#if BUTTONS_NUM > 3
  btn1.setIntervalOfSerial(500);
  btn3.setLongClickMode(LCM_CLICKSERIES);
  btn3.setIntervalOfSerial(500);
  btn4.setIntervalOfSerial(500);
#endif

  _start_mode(btn3);

  // опрос кнопок
  while (true)
  {
    btn1.getButtonState();
    btn2.getButtonState();
#if BUTTONS_NUM == 3
    shButton *btn_down = &btn3;
#elif BUTTONS_NUM > 3
    btn3.getButtonState();
    shButton *btn_down = &btn4;
#endif
    btn_down->getButtonState();

#if BUTTONS_NUM == 3
    static bool td_start = false;
#endif
    static bool td_btn_up = false;
    static bool td_btn_down = false;

    switch (btn1.getLastState())
    {
    case BTN_UP:
      // размер вершины - увеличение
      if (!td_btn_up)
      {
        if (topLength < TOP_LENGTH)
        {
          _set_top_length(true);
        }
      }
      td_btn_up = false;
      break;
#if BUTTONS_NUM > 3
    case BTN_LONGCLICK:
      // задержка вершины - ускорение
      if (topEffectIndex > 0)
      {
        if (topDelay > 20)
        {
          _set_top_delay(false);
        }
      }
      td_btn_up = true;
      break;
#endif
    }

    switch (btn_down->getLastState())
    {
    case BTN_UP:
#if BUTTONS_NUM == 3
      if (td_start)
      {
#endif
        // размер вершины - уменьшение
        if (!td_btn_down)
        {
          if (topLength > 0)
          {
            _set_top_length(false);
          }
        }
        td_btn_down = false;
#if BUTTONS_NUM == 3
      }
      else
      {
        td_start = true;
      }
#endif
      break;
#if BUTTONS_NUM > 3
    case BTN_LONGCLICK:
      // задержка вершины - замедление
      if (topEffectIndex > 0)
      {
        if (topDelay < 250)
        {
          _set_top_delay(true);
        }
      }
      td_btn_down = true;
      break;
#endif
    }

    switch (btn2.getLastState())
    {
    case BTN_ONECLICK:
      // тип заливки вершины - сплошной, сверху вниз, снизу вверх или случайное мерцание
      if (++topEffectIndex > 3)
      {
        topEffectIndex = 0;
      }
      led2_blink();
      write_eeprom_8(EEPROM_INDEX_FOR_TOPEFFECT, topEffectIndex);

      CTG_PRINT(F("Top effect: "));
      CTG_PRINTLN(topEffectIndex);
      break;
    case BTN_LONGCLICK:
      // цвет заливки вершины
      if (++topColorIndex > 7)
      {
        topColorIndex = 0;
      }
      led2_blink();
      write_eeprom_8(EEPROM_INDEX_FOR_TOPCOLOR, topColorIndex);

      print_top_color();
      break;
    }

#if BUTTONS_NUM > 3
    // изменение величины затухания вершины (topFading); работает только если не задана сплошная заливка вершины
    if (topEffectIndex > 0)
    {
      static bool tf_flag = false;
      static bool tf_to_up = false;
      static bool tf_start = false;

      switch (btn3.getLastState())
      {
      case BTN_LONGCLICK:
        if (tf_start)
        {
          tf_flag = true;
          if (tf_to_up)
          {
            if (topFading <= 50)
            {
              led2_blink();
              topFading += 5;
              print_top_fading();
            }
          }
          else
          {
            if (topFading >= 10)
            {
              led2_blink();
              topFading -= 5;
              print_top_fading();
            }
          }
        }
        break;
      case BTN_UP:
        // устанавливаем флаг начала изменений
        tf_start = true;
        // при отпускании кнопки меняем флаг направления изменения только при условии, что было удержание кнопки, а не просто клик
        if (tf_flag)
        {
          tf_flag = false;
          tf_to_up = !tf_to_up;
        }
        // и сохраняем изменения
        write_eeprom_8(EEPROM_INDEX_FOR_TOPFADING, topFading);
        break;
      }
    }
#endif

    top();
    LEDS.show();
  }
}
#endif

#if BUTTONS_NUM > 3 && POWER_I && POWER_V

void print_voltage()
{
  CTG_PRINT(F("Garland supply voltage: "));
  CTG_PRINT(powerV);
  CTG_PRINTLN(F("V"));
}

void print_current()
{
  CTG_PRINT(F("Maximum current consumption: "));
  CTG_PRINT(powerI * 100ul);
  CTG_PRINTLN(F("mA"));
}

void fill_power_data(uint8_t mode)
{
  fill_solid(leds, MAX_LEDS, CRGB::Black);
  if (mode)
  {
    fill_solid(leds, powerV, set_new_eorder(CRGB::Red));
  }
  else
  {
    fill_solid(leds, powerI, set_new_eorder(CRGB::Blue));
  }
}

void _set_power_data(uint8_t mode, bool to_up, uint8_t step = 1)
{
  if (mode)
  {
    powerV += (to_up) ? step : -step;
    print_voltage();
  }
  else
  {
    powerI += (to_up) ? step : -step;
    print_current();
  }
  led2_blink();
}

void setMaxPowerConsumption()
{
  btn1.setIntervalOfSerial(500);
  btn4.setIntervalOfSerial(500);

  LEDS.setBrightness(10);
  CTG_PRINTLN(F("Maximum power consumption setting mode"));
  print_voltage();
  print_current();
  CTG_PRINTLN();

  _start_mode(btn4);

  fill_power_data(0);
  LEDS.show();

  uint8_t cur_mode = 0;

  // опрос кнопок
  while (true)
  {

    btn1.getButtonState();
    btn2.getButtonState();
    btn3.getButtonState();
    btn4.getButtonState();

    if (btn2.getLastState() == BTN_DOWN || btn2.getLastState() == BTN_DBLCLICK)
    {
      cur_mode = 0;
      led2_blink();
    }
    if (btn3.getLastState() == BTN_DOWN || btn3.getLastState() == BTN_DBLCLICK)
    {
      cur_mode = 1;
      led2_blink();
    }

    switch (btn1.getLastState())
    {
    case BTN_DOWN:
    case BTN_DBLCLICK:
      if ((cur_mode && powerV < 15) || (!cur_mode && powerI < 1000))
      {
        _set_power_data(cur_mode, true);
      }
      break;
    case BTN_LONGCLICK:
      if ((cur_mode && powerV < 10) || (!cur_mode && powerI < 995))
      {
        _set_power_data(cur_mode, true, 5);
      }
      break;
    case BTN_UP:
      (cur_mode) ? write_eeprom_8(EEPROM_INDEX_FOR_POWER_V, powerV)
                 : write_eeprom_16(EEPROM_INDEX_FOR_POWER_I, powerI);
      break;
    }

    static bool start = false;

    switch (btn4.getLastState())
    {
    case BTN_DOWN:
    case BTN_DBLCLICK:
      if ((cur_mode && powerV > 3) || (!cur_mode && powerI > 0))
      {
        _set_power_data(cur_mode, false);
      }
      break;
    case BTN_LONGCLICK:
      if (start)
      {
        if ((cur_mode && powerV > 8) || (!cur_mode && powerI > 5))
        {
          _set_power_data(cur_mode, false, 5);
        }
      }
      break;
    case BTN_UP:
      start = true;
      (cur_mode) ? write_eeprom_8(EEPROM_INDEX_FOR_POWER_V, powerV)
                 : write_eeprom_16(EEPROM_INDEX_FOR_POWER_I, powerI);
      break;
    }

    fill_power_data(cur_mode);
    LEDS.show();
  }
}
#endif

#endif