/**
 * @file _leds.h
 *
 * Все, что связано с работой гирлянды
 *
 */
#pragma once

#include "../setting.h"
#include "_eeprom.h"
#include <FastLED.h>

// ===================================================

// подмена цветов согласно сохраненного порядка следования перед выводом их на гирлянду
CRGB set_new_eorder(CRGB _col);
// инициализация FastLED
void fastled_init();
// вывод цветности гирлянды в Сериал
void print_eorder();
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

// ===================================================

CRGB set_new_eorder(CRGB _col)
{
#if !defined(EORDER)
  switch (eorder_index)
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

void fastled_init()
{
  LEDS.setBrightness(maxBright);
  LEDS.setMaxPowerInVoltsAndMilliamps(5, 500);

#if defined(EORDER)

#if defined(LED_CLK_PIN)
  LEDS.addLeds<CHIPSET, LED_DATA_PIN, LED_CLK_PIN, EORDER>(leds, MAX_LEDS);
#else
  LEDS.addLeds<CHIPSET, LED_DATA_PIN, EORDER>(leds, MAX_LEDS);
#endif

#else

#if defined(LED_CLK_PIN)
  LEDS.addLeds<CHIPSET, LED_DATA_PIN, LED_CLK_PIN, RGB>(leds, MAX_LEDS);
#else
  LEDS.addLeds<CHIPSET, LED_DATA_PIN, RGB>(leds, MAX_LEDS);
#endif

#if BUTTONS_NUM > 0
  // настройка следования цветов при зажатой кнопке 1
  if (!digitalRead(BTN1_PIN))
  {
    set_eorder();
  }

#endif

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
}

void print_eorder()
{
  CTG_PRINT(F("LEDS EORDER: "));
#if !defined(EORDER)
  switch (eorder_index)
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

#if BUTTONS_NUM && (TOP_LENGTH || CAN_CHANGE_NUMLEDS || !defined(EORDER))
void _start_mode()
{
  // отработка первого клика, чтобы не мешался в настройках
  btn1.getButtonState();
  delay(100);
  btn1.getButtonState();
}
#endif

#if BUTTONS_NUM > 1 && CAN_CHANGE_NUMLEDS
static void fill_solid_garland()
{
  fill_solid(leds, MAX_LEDS, CRGB::Black);
  fill_solid(leds, numLeds, set_new_eorder(CRGB::Red));
  LEDS.show();

  CTG_PRINT(F("Length garland: "));
  CTG_PRINTLN(numLeds);
}
void setLengthOfGarland()
{
  CTG_PRINTLN(F("Mode for changing the length of the garland"));

  fill_solid_garland();

  _start_mode();

  // запускаем бесконечный цикл для опроса кнопок
  while (true)
  {
    switch (btn1.getButtonState())
    {
    case BTN_DOWN:
      if (numLeds < MAX_LEDS)
      {
        numLeds++;
        fill_solid_garland();
      }
      break;
    case BTN_LONGCLICK:
      if (numLeds < MAX_LEDS - 10)
      {
        numLeds += 10;
        fill_solid_garland();
      }
      break;
    }

#if BUTTONS_NUM == 2
    shButton *btn_down = &btn2;
#elif BUTTONS_NUM == 3
    shButton *btn_down = &btn3;
#elif BUTTONS_NUM == 4
    shButton *btn_down = &btn4;
#endif
    switch (btn_down->getButtonState())
    {
    case BTN_DOWN:
      if (numLeds > 1)
      {
        numLeds--;
        fill_solid_garland();
      }
      break;
    case BTN_LONGCLICK:
      if (numLeds > 10)
      {
        numLeds -= 10;
        fill_solid_garland();
      }
      break;
    }

    // при отпускании кнопки сохранить длину в EEPROM
    if (btn1.getLastState() == BTN_UP ||
        btn_down->getLastState() == BTN_UP)
    {
#if MAX_LEDS < 255
      write_eeprom_8(EEPROM_INDEX_FOR_STRANDLEN, numLeds);
      write_eeprom_8(EEPROM_INDEX_FOR_STRANDLEN + 1, 0);
#else
      write_eeprom_8(EEPROM_INDEX_FOR_STRANDLEN, (uint16_t)(numLeds) & 0x00ff);
      write_eeprom_8(EEPROM_INDEX_FOR_STRANDLEN + 1, (uint16_t)(numLeds) >> 8);
#endif
    }
  }
}
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

  _start_mode();

  eorder_index = 0;
  write_eeprom_8(EEPROM_INDEX_FOR_EORDER, eorder_index);
  fill_solid(leds, MAX_LEDS, CRGB::Black);
  show_rgb();

  // запускаем бесконечный цикл для опроса кнопки
  while (true)
  {
    if (btn1.getButtonState() == BTN_DOWN)
    {
      if (++eorder_index > 5)
      {
        eorder_index = 0;
      }
      write_eeprom_8(EEPROM_INDEX_FOR_EORDER, eorder_index);
      print_eorder();
      show_rgb();
    }
  }
}
#endif

#if BUTTONS_NUM > 2 && TOP_LENGTH
void set_top_setting()
{
  CTG_PRINTLN(F("Mode for changing the setting for top of the garland"));

  fill_solid(leds, MAX_LEDS, CRGB::Black);
  top();
  LEDS.show();

  _start_mode();

  while (true)
  {
    if (btn1.getButtonState() == BTN_DOWN)
    {
      if (topLength < TOP_LENGTH)
      {
        topLength++;
#if TOP_LENGTH < 255
        write_eeprom_8(EEPROM_INDEX_FOR_TOPLENGTH, topLength);
#else
        write_eeprom_16(EEPROM_INDEX_FOR_TOPLENGTH, topLength);
#endif
        fill_solid(leds, MAX_LEDS, CRGB::Black);

        CTG_PRINT(F("Top length: "));
        CTG_PRINTLN(topLength);
      }
    }

#if BUTTONS_NUM == 3
    shButton *btn_down = &btn3;
#elif BUTTONS_NUM == 4
    shButton *btn_down = &btn4;
#endif
    if (btn_down->getButtonState() == BTN_DOWN)
    {
      if (topLength > 0)
      {
        topLength--;
#if TOP_LENGTH < 255
        write_eeprom_8(EEPROM_INDEX_FOR_TOPLENGTH, topLength);
#else
        write_eeprom_16(EEPROM_INDEX_FOR_TOPLENGTH, topLength);
#endif
        fill_solid(leds, MAX_LEDS, CRGB::Black);

        CTG_PRINT(F("Top length: "));
        CTG_PRINTLN(topLength);
      }
    }

    if (btn2.getButtonState() == BTN_DOWN)
    {
      if (++topEffect > 3)
      {
        topEffect = 0;
      }
      write_eeprom_8(EEPROM_INDEX_FOR_TOPEFFECT, topEffect);
      fill_solid(leds, MAX_LEDS, CRGB::Black);

      CTG_PRINT(F("Top effect: "));
      CTG_PRINTLN(topEffect);
    }

#if BUTTON_NUM > 3
TODO: сделать выбор цвета вершины третьей кнопкой, если модуль использует все 4 кнопки
#endif

    top();
    LEDS.show();
  }
}
#endif
