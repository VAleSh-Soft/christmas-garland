#ifndef FIRE_H
#define FIRE_H

#include "function.h"

void fire()
{ // The fill_rainbow call doesn't support brightness levels
  if (kolLeds >= 10)
  {

#if MAX_LEDS < 255
    uint8_t x = kolLeds / 10;            // Координаты
    uint8_t k1 = random8(x * 2);         // Жар
    uint8_t k2 = random8(x * 2) + k1;    // Огонь
    uint8_t k3 = x * 3 + random8(x * 4); // Пламя
    uint8_t k4 = kolLeds - 1;            // Дым
    if ((k4 - k2) < k3)
      k3 = k4;
    else
      k3 = k3 + k2;

#else
    uint16_t x = kolLeds / 10;
    uint16_t k1 = random8(x * 2);         // Жар
    uint16_t k2 = random8(x * 2) + k1;    // Огонь
    uint16_t k3 = x * 3 + random8(x * 4); // Пламя
    uint16_t k4 = kolLeds - 1;            // Дым
    if ((k4 - k2) < k3)
      k3 = k4;
    else
      k3 = k3 + k2;
#endif

#if TOP_POSITION == 0
    if (thisdir == 1)
    { // направление
#endif

#if (TOP_POSITION == 0) || (TOP_POSITION == 2)
      fill_gradient_RGB(leds, 0, CRGB::White, k1, set_new_eorder(CRGB::Yellow)); // Градиент
      fill_gradient_RGB(leds, k1, set_new_eorder(CRGB::Yellow), k2, set_new_eorder(CRGB::Red));
      fill_gradient_RGB(leds, k2, set_new_eorder(CRGB::Red), k3, CRGB::Black);
      if (k3 < k4)
        fill_gradient_RGB(leds, k3, CRGB::Black, k4, CRGB::Black);
      for (uint8_t y = 0; y < x; y++)
        leds[random16(k2, kolLeds - 1)] = set_new_eorder(CRGB::Red);
#endif

#if TOP_POSITION == 0
    }
    else
    {
#endif

#if (TOP_POSITION == 0) || (TOP_POSITION == 1)
      k1 = kolLeds - 1 - k1; // Поворот
      k2 = kolLeds - 1 - k2;
#if MAX_LEDS < 255
      if ((kolLeds - 1) < k3)
        k3 = 0;
      else
        k3 = kolLeds - 1 - k3;
#else
      k3 = kolLeds - 1 - k3;
#endif

      fill_gradient_RGB(leds, k1, CRGB::White, k4, set_new_eorder(CRGB::Yellow)); // Градиент
      fill_gradient_RGB(leds, k2, set_new_eorder(CRGB::Yellow), k1, set_new_eorder(CRGB::Red));
      fill_gradient_RGB(leds, k3, set_new_eorder(CRGB::Red), k2, CRGB::Black);
      if (k3 > 0)
        fill_gradient_RGB(leds, 0, CRGB::Black, k3, CRGB::Black);
      for (uint8_t y = 0; y < x; y++)
        leds[random16(k2)] = set_new_eorder(CRGB::Red);
#endif

#if TOP_POSITION == 0
    }
#endif
  }

} // fire()

#endif

