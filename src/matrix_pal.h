#ifndef MATRIX_PAL_H
#define MATRIX_PAL_H

#include "function.h"

/* Usage - matrix_pal();
 *
 *  This is one of the few routines I have with pixel counting.
 *
 *
 * currentPalette, targetPalette
 * thisrot
 * thisindex
 * bgclr
 * bgbri
 * thisdir
 * thisbright
 */

void matrix_pal()
{ // One line matrix

  if (thisrot)
    thisindex++; // Increase palette index to change colours on the fly

  if (kolLeds >= 10)
  {

    if (random8(90) > 80)
    {
      if (thisdir == -1)
        leds[0] = set_new_eorder(ColorFromPalette(gCurrentPalette, thisindex, 255, currentBlending)); // Foreground matrix colour
      else
        leds[kolLeds - 1] = set_new_eorder(ColorFromPalette(gCurrentPalette, thisindex, 255, currentBlending));
    }
    else
    {
      if (thisdir == -1)
        leds[0] = set_new_eorder(CHSV(bgclr, 255, bgbri)); // Background colour
      else
        leds[kolLeds - 1] = set_new_eorder(CHSV(bgclr, 255, bgbri));
    }

#if MAX_LEDS < 255
    uint8_t i;
#else
    uint16_t i;
#endif

    if (thisdir == -1)
    { // Move the foreground colour down the line.
      for (i = kolLeds - 1; i > 0; i--)
        leds[i] = leds[i - 1];
    }
    else
    {
      for (i = 0; i < kolLeds - 1; i++)
        leds[i] = leds[i + 1];
    }
  }
} // matrix_pal()

#endif

