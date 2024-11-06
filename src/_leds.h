/**
 * @file _leds.h
 *
 * Все, что связано с работой гирлянды
 *
 */
#pragma once

#include "../setting.h"
#include <FastLED.h>

#if MAX_LEDS < 255
uint8_t numLeds; // Количество светодиодов, которые мы на самом деле используем, и мы можем изменить его только на длину нити - не более MAX_LEDS
uint8_t kolLeds;
#else
uint16_t numLeds; // Количество светодиодов, которые мы на самом деле используем, и мы можем изменить его только на длину нити - не более MAX_LEDS
uint16_t kolLeds;
#endif

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
uint8_t eorder_index = 2; // сохраненная очередность цветов, если она не задана жестко макросом EORDER
#endif

// ===================================================

// подмена цветов согласно сохраненного порядка следования перед выводом их на гирлянду
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
  default:
    return (_col);
  }
#else
  // если порядок задан жестко, вывести, не меняя
  return (_col);
#endif
}

// инициализация FastLED
void fastled_init()
{
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

#endif
  LEDS.setBrightness(maxBright);
  LEDS.setMaxPowerInVoltsAndMilliamps(5, 500);
}

// вывод цветности гирлянды в Сериал
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