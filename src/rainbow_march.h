#ifndef RAINBOW_MARCH_H
#define RAINBOW_MARCH_H

#include "_leds.h"

/* Usage - rainbow_march();
 *
 * thisindex
 * thisdiff
 * thisrot
 * thisdir
 */

void rainbow_march()
{ // The fill_rainbow call doesn't support brightness levels
  if (kolLeds >= 10)
  {
    thisindex += thisrot * thisdir;
    fill_rainbow(leds, kolLeds, thisindex, thisdiff); // I don't change deltahue on the fly as it's too fast near the end of the strip.
  }
} // rainbow_march()

#endif

// ***