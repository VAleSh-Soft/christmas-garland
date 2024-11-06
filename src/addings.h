#ifndef ADDINGS_H
#define ADDINGS_H

#include "_leds.h"

#if CANDLE_KOL > 0
// ==== Свечи ========================================
DEFINE_GRADIENT_PALETTE(candle_Pal){
    0, 255, 0, 0,        // red
    90, 255, 255, 255,   // full white
    180, 255, 255, 0,    // bright yellow
    255, 255, 255, 255}; // full white

void addcandle()
{
  uint16_t poz = polCandle;
  CRGBPalette16 myPal = candle_Pal;

  if (numLeds > CANDLE_KOL)
  {
    uint16_t kol = numLeds / CANDLE_KOL; // Количество свечей

    for (uint16_t x = 0; x < kol; x++)
    {
      if (poz < numLeds)
        leds[poz] = set_new_eorder(ColorFromPalette(myPal, random8(255)));
      poz += CANDLE_KOL;
    }
  }
}
#endif

// ==== Черный фон ===================================
void addbackground()
{
#if MAX_LEDS < 255
  uint8_t i;
#else
  uint16_t i;
#endif

  for (i = 0; i < numLeds; i++)
    if ((leds[i].r < 5) &&
        (leds[i].g < 5) &&
        (leds[i].b < 5))
      leds[i].b += 5; // CRGB(5, 5, 5);
}

// ==== Блеск ========================================
void addglitter(fract8 chanceOfGlitter)
{
  if (random8() < chanceOfGlitter)
  {
#if MAX_LEDS < 255
    leds[random8(numLeds)] += CRGB::White;
#else
    leds[random16(numLeds)] += CRGB::White;
#endif
  }
}

// ==== Бенгальский огонь ============================
void sparkler(uint8_t n) // Бенгальский огонь
// 0 - нет эффектов
// 1 - Бенгальский огонь
// 2 - 1 яркий светодиод
// 3 - метеорит
// 4 - случайный эффект
{
  uint8_t kol = 3;

  if (kolLeds < 10)
    kol = kolLeds / 3;
  if (kol >= 2)
  {
    uint8_t nn = n;
    switch (nn)
    {
    case 1:
      for (uint8_t x = 0; x < kol; x++)
        leds[kolLeds - random8(kol * 2)] = CRGB::White;
      break; // Бенгальский
    case 2:
      leds[kolLeds - 1] = CRGB::White;
      break; // 1 яркий
    case 3:
      leds[kolLeds] = CRGB::White;
      leds[kolLeds - 1] = set_new_eorder(CRGB::Red);
      leds[kolLeds - 2] = set_new_eorder(CRGB::Violet);
      break; // Метеорит
    }
  }
}

#if TOP_LENGTH > 0
// ==== Обработка конца гирлянды =====================
void top()
{
#if TOP_EFFECT == 0
  fill_solid(&leds[numLeds - TOP_LENGTH], TOP_LENGTH, set_new_eorder(TOP_COLOR));
#else
#if MAX_LEDS < 255
  static uint8_t x;
#else
  static uint16_t x;
#endif

  fadeToBlackBy(&leds[numLeds - TOP_LENGTH], TOP_LENGTH, TOP_FADING); // Затухание к черному
  EVERY_N_MILLIS_I(toptimer, TOP_DELAY)
  { // Sets the original delay time.
#if TOP_EFFECT == 1
#if TOP_LENGTH < 255
    leds[numLeds - TOP_LENGTH + random8(0, TOP_LENGTH)] = set_new_eorder(TOP_COLOR);
#else
    leds[numLeds - TOP_LENGTH + random16(0, TOP_LENGTH)] = set_new_eorder(TOP_COLOR);
#endif
#elif TOP_EFFECT == 2
    if ((x <= numLeds - TOP_LENGTH) || (x >= numLeds))
      x = numLeds - 1;
    else
      x--;
    leds[x] = set_new_eorder(TOP_COLOR);
#else
    if ((x < numLeds - TOP_LENGTH) || (x >= numLeds - 1))
      x = numLeds - TOP_LENGTH;
    else
      x++;
    leds[x] = set_new_eorder(TOP_COLOR);
#endif
  }
#endif
} // top()
#endif

// ==== Обработчик нажатий кнопок ====================
void BtnHandler()
{

#if BUTTONS_NUM
  {
    switch (btn1.getButtonState())
    {
    case BTN_ONECLICK:
      protocol = 1;
      command = BTN1_1;

      CTG_PRINTLN(F("BTN1 Click"));

      LED1_FleshH(1); // мигнуть светодиодом 1

      break;
    case BTN_DBLCLICK:
      protocol = 1;
      command = BTN1_2;

      CTG_PRINTLN(F("BTN1 DblClick"));

      LED1_FleshH(2); // мигнуть 2 раза светодиодом 1

      break;
    case BTN_LONGCLICK:
      protocol = 1;
      command = BTN1_PRESS;

      CTG_PRINTLN(F("BTN1 Step"));

      LED1_FleshL(1); // мигнуть  светодиодом 1

      break;
    }
  }
#if BUTTONS_NUM > 1
  {
    switch (btn2.getButtonState())
    {
    case BTN_ONECLICK:
      protocol = 1;
      command = BTN2_1;

      CTG_PRINTLN(F("BTN2 Click"));

      LED1_FleshH(1); // мигнуть светодиодом 1

      break;
    case BTN_DBLCLICK:
      protocol = 1;
      command = BTN2_2;

      CTG_PRINTLN(F("BTN2 DblClick"));

     LED1_FleshH(2); // мигнуть 2 раза светодиодом 1

      break;
    case BTN_LONGCLICK:
      protocol = 1;
      command = BTN2_PRESS;

      CTG_PRINTLN(F("BTN2 Step"));

      LED1_FleshL(1); // мигнуть  светодиодом 1

      break;
    }
  }
#if BUTTONS_NUM > 2
  {
    switch (btn3.getButtonState())
    {
    case BTN_ONECLICK:
      protocol = 1;
      command = BTN3_1;

      CTG_PRINTLN(F("BTN3 Click"));

      LED1_FleshH(1); // мигнуть светодиодом 1

      break;
    case BTN_DBLCLICK:
      protocol = 1;
      command = BTN3_2;

      CTG_PRINTLN(F("BTN3 DblClick"));

      LED1_FleshH(2); // мигнуть 2 раза светодиодом 1

      break;
    case BTN_LONGCLICK:
      protocol = 1;
      command = BTN3_PRESS;

      CTG_PRINTLN(F("BTN3 Step"));

      LED1_FleshL(1); // мигнуть  светодиодом 1

      break;
    }
  }
#if BUTTONS_NUM > 3
  {
    switch (btn4.getButtonState())
    {
    case BTN_ONECLICK:
      protocol = 1;
      command = BTN4_1;

      CTG_PRINTLN(F("BTN4 Click"));

      LED1_FleshH(1); // мигнуть светодиодом 1

      break;
    case BTN_DBLCLICK:
      protocol = 1;
      command = BTN4_2;

      CTG_PRINTLN(F("BTN4 DblClick"));

      LED1_FleshH(2); // мигнуть 2 раза светодиодом 1

      break;
    case BTN_LONGCLICK:
      protocol = 1;
      command = BTN4_PRESS;

      CTG_PRINTLN(F("BTN4 Step"));

      LED1_FleshL(1); // мигнуть  светодиодом 1

      break;
    }
  }
#endif
#endif
#endif
#endif
}

#endif
