#ifndef BLENDWARE_H
#define BLENDWARE_H

#include "function.h"

void blendwave()
{
  CRGB clr1;
  CRGB clr2;
  uint8_t speed;
#if MAX_LEDS < 255
  uint8_t loc1;
#else
  uint16_t loc1;
#endif

  if (kolLeds >= 10)
  {

    speed = beatsin8(6, 0, 255);

    clr1 = blend(CHSV(beatsin8(3, 0, 255), 255, 255), CHSV(beatsin8(4, 0, 255), 255, 255), speed);
    clr2 = blend(CHSV(beatsin8(4, 0, 255), 255, 255), CHSV(beatsin8(3, 0, 255), 255, 255), speed);

#if MAX_LEDS < 255
    loc1 = beatsin8(10, 0, kolLeds - 1);
#else
    loc1 = beatsin16(10, 0, kolLeds - 1);
#endif

    fill_gradient_RGB(leds, 0, set_new_eorder(clr2), loc1, set_new_eorder(clr1));
    fill_gradient_RGB(leds, loc1, set_new_eorder(clr2), kolLeds - 1, set_new_eorder(clr1));
  }
} // blendwave()

#endif


