#ifndef THREE_SIN_PAL_H
#define THREE_SIN_PAL_H

#include "_leds.h"

// three_sin_pal variables ---------------------------------------------------------------------

int wave1;
int wave2;
int wave3;
uint8_t mul1;
uint8_t mul2;
uint8_t mul3;

void three_sin_pal()
{
  if (kolLeds >= 10)
  {

    wave1 += beatsin8(10, -4, 4) * thisdir;
    wave2 += beatsin8(15, -2, 2) * thisdir;
    wave3 += beatsin8(12, -3, 3) * thisdir;

#if MAX_LEDS < 255
    uint8_t k;
#else
    uint16_t k;
#endif

    for (k = 0; k < kolLeds; k++)
    {
      uint8_t tmp = sin8(mul1 * k + wave1) + sin8(mul1 * k + wave2) + sin8(mul1 * k + wave3);
      leds[k] = set_new_eorder(ColorFromPalette(gCurrentPalette, tmp, 255, currentBlending));
    }
  }
} // three_sin_pal()

#endif
