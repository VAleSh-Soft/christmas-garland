#ifndef ADDINGS_H
#define ADDINGS_H

#if CANDLE_KOL > 0
// ==== Свечи ========================================
DEFINE_GRADIENT_PALETTE(candle_Pal){
    0, 255, 0, 0,        // red
    90, 255, 255, 255,   // full white
    180, 255, 255, 0,    // bright yellow
    255, 255, 255, 255}; // full white

uint8_t PolCandle = 1; // Положение свечи

void addcandle()
{
  uint16_t poz = PolCandle;
  CRGBPalette16 myPal = candle_Pal;

  if (NUM_LEDS > CANDLE_KOL)
  {
    uint16_t kol = NUM_LEDS / CANDLE_KOL; // Количество свечей

    for (uint16_t x = 0; x < kol; x++)
    {
      if (poz < NUM_LEDS)
        leds[poz] = ColorFromPalette(myPal, random8(255));
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

  for (i = 0; i < NUM_LEDS; i++)
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
    leds[random8(NUM_LEDS)] += CRGB::White;
#else
    leds[random16(NUM_LEDS)] += CRGB::White;
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

  if (KolLed < 10)
    kol = KolLed / 3;
  if (kol >= 2)
  {
    uint8_t nn = n;
    switch (nn)
    {
    case 1:
      for (uint8_t x = 0; x < kol; x++)
        leds[KolLed - random8(kol * 2)] = CRGB::White;
      break; // Бенгальский
    case 2:
      leds[KolLed - 1] = CRGB::White;
      break; // 1 яркий
    case 3:
      leds[KolLed] = CRGB::White;
      leds[KolLed - 1] = CRGB::Red;
      leds[KolLed - 2] = CRGB::Violet;
      break; // Метеорит
    }
  }
}

#if TOP_LENGTH > 0
// ==== Обработка конца гирлянды =====================
void top()
{
#if TOP_EFFECT == 0
  fill_solid(&leds[NUM_LEDS - TOP_LENGTH], TOP_LENGTH, TOP_COLOR);
#else
#if MAX_LEDS < 255
  static uint8_t x;
#else
  static uint16_t x;
#endif

  fadeToBlackBy(&leds[NUM_LEDS - TOP_LENGTH], TOP_LENGTH, TOP_FADING); // Затухание к черному
  EVERY_N_MILLIS_I(toptimer, TOP_DELAY)
  { // Sets the original delay time.
#if TOP_EFFECT == 1
#if TOP_LENGTH < 255
    leds[NUM_LEDS - TOP_LENGTH + random8(0, TOP_LENGTH)] = TOP_COLOR;
#else
    leds[NUM_LEDS - TOP_LENGTH + random16(0, TOP_LENGTH)] = TOP_COLOR;
#endif
#elif TOP_EFFECT == 2
    if ((x <= NUM_LEDS - TOP_LENGTH) || (x >= NUM_LEDS))
      x = NUM_LEDS - 1;
    else
      x--;
    leds[x] = TOP_COLOR;
#else
    if ((x < NUM_LEDS - TOP_LENGTH) || (x >= NUM_LEDS - 1))
      x = NUM_LEDS - TOP_LENGTH;
    else
      x++;
    leds[x] = TOP_COLOR;
#endif
  }
#endif
} // top()
#endif

// ==== Обработчик нажатий кнопок ====================
void BtnHandler()
{

#if KEY_ON > 0
  {
    switch (btn1.getButtonState())
    {
    case BTN_ONECLICK:
      Protocol = 1;
      Command = BTN1_1;
#if LOG_ON == 1
      Serial.println(F("BTN1 Click"));
#endif
#if LED_ON > 0
      LED1_FleshH(1); // мигнуть светодиодом 1
#endif
      break;
    case BTN_DBLCLICK:
      Protocol = 1;
      Command = BTN1_2;
#if LOG_ON == 1
      Serial.println(F("BTN1 2Click"));
#endif
#if LED_ON > 0
      LED1_FleshH(2); // мигнуть 2 раза светодиодом 1
#endif
      break;
    case BTN_LONGCLICK:
      Protocol = 1;
      Command = BTN1_PRESS;
#if LOG_ON == 1
      Serial.println(F("BTN1 Step"));
#endif
#if LED_ON > 0
      LED1_FleshL(1); // мигнуть  светодиодом 1
#endif
      break;
    }
  }
#if KEY_ON > 1
  {
    switch (btn2.getButtonState())
    {
    case BTN_ONECLICK:
      Protocol = 1;
      Command = BTN2_1;
#if LOG_ON == 1
      Serial.println(F("BTN2 Click"));
#endif
#if LED_ON > 0
      LED1_FleshH(1); // мигнуть светодиодом 1
#endif
      break;
    case BTN_DBLCLICK:
      Protocol = 1;
      Command = BTN2_2;
#if LOG_ON == 1
      Serial.println(F("BTN2 2Click"));
#endif
#if LED_ON > 0
      LED1_FleshH(2); // мигнуть 2 раза светодиодом 1
#endif
      break;
    case BTN_LONGCLICK:
      Protocol = 1;
      Command = BTN2_PRESS;
#if LOG_ON == 1
      Serial.println(F("BTN2 Step"));
#endif
#if LED_ON > 0
      LED1_FleshL(1); // мигнуть  светодиодом 1
#endif
      break;
    }
  }
#if KEY_ON > 2
  {
    switch (btn3.getButtonState())
    {
    case BTN_ONECLICK:
      Protocol = 1;
      Command = BTN3_1;
#if LOG_ON == 1
      Serial.println(F("BTN3 Click"));
#endif
#if LED_ON > 0
      LED1_FleshH(1); // мигнуть светодиодом 1
#endif
      break;
    case BTN_DBLCLICK:
      Protocol = 1;
      Command = BTN3_2;
#if LOG_ON == 1
      Serial.println(F("BTN3 2Click"));
#endif
#if LED_ON > 0
      LED1_FleshH(2); // мигнуть 2 раза светодиодом 1
#endif
      break;
    case BTN_LONGCLICK:
      Protocol = 1;
      Command = BTN3_PRESS;
#if LOG_ON == 1
      Serial.println(F("BTN3 Step"));
#endif
#if LED_ON > 0
      LED1_FleshL(1); // мигнуть  светодиодом 1
#endif
      break;
    }
  }
#if KEY_ON > 3
  {
    switch (btn4.getButtonState())
    {
    case BTN_ONECLICK:
      Protocol = 1;
      Command = BTN4_1;
#if LOG_ON == 1
      Serial.println(F("BTN4 Click"));
#endif
#if LED_ON > 0
      LED1_FleshH(1); // мигнуть светодиодом 1
#endif
      break;
    case BTN_DBLCLICK:
      Protocol = 1;
      Command = BTN4_2;
#if LOG_ON == 1
      Serial.println(F("BTN4 2Click"));
#endif
#if LED_ON > 0
      LED1_FleshH(2); // мигнуть 2 раза светодиодом 1
#endif
      break;
    case BTN_LONGCLICK:
      Protocol = 1;
      Command = BTN4_PRESS;
#if LOG_ON == 1
      Serial.println(F("BTN4 Step"));
#endif
#if LED_ON > 0
      LED1_FleshL(1); // мигнуть  светодиодом 1
#endif
      break;
    }
  }
#endif
#endif
#endif
#endif
}

#endif
