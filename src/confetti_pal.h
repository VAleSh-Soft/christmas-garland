#ifndef CONFETTI_PAL_H
#define CONFETTI_PAL_H

#include "_leds.h"

/* This is adapted from the confetti routine created by Mark Kriegsman */

/*  Usage - confetti_pal();
 *
 *  thisfade
 *  thisdelay
 *  currentPalette and targetPalette
 *  thisdiff
 *  thisindex
 *  thisinc
 *  thisbright
 */

void confetti_pal()
{ // random colored speckles that blink in and fade smoothly
  if (kolLeds >= 10)
  {
    fadeToBlackBy(leds, kolLeds, thisfade); // Задухание светодиодов на значение thisfade
#if MAX_LEDS < 255
    uint8_t pos = random8(kolLeds);
#else
    uint16_t pos = random16(kolLeds);
#endif
    leds[pos] = set_new_eorder(ColorFromPalette(gCurrentPalette,
                                                thisindex + random8(thisdiff) / 4,
                                                255,
                                                currentBlending)); // Munge the values and pick a colour from the palette
    thisindex = thisindex + thisinc;                               // base palette counter increments here.
  }
} // confetti_pal()

#endif

// ***