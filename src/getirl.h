#pragma once

#if SAVE_EEPROM > 0
#include "_eeprom.h"
#endif

// ==== Работа с кнопками ============================
#if BUTTONS_NUM

void bootme();
void meshwait();
void getirl();

void SetMode(uint8_t Mode)
{
  setOff(demorun);
#if CHANGE_ON == 1
  newMode = Mode;
  stepMode = 1;
#if CHANGE_SPARK == 4
  randSpark = random8(3) + 1;
#endif
#else
  ledMode = Mode;
  meshwait();
  strobe_mode(Mode, 1); // Does NOT reset to 0.
#endif
#if CANDLE_KOL > 0
  PolCandle = random8(CANDLE_KOL);
#endif
}

void getirl()
{ // Обработка команд с кнопок

  if (protocol)
  {

    if ((ledMode < 220) || (ledMode >= 230) || (demorun < 100))
    {
      LED2_Off; // Выключить светодиод

      CTG_PRINT(F("command: 0x"));
      CTG_PRINTLN_2(command, HEX);

      switch (command)
      {

#if Command_Brightness_plus
      case Command_Brightness_plus: //  Увеличить максимальную яркость и остановится если достигли максимума
        maxBright = min((maxBright < 5) ? maxBright + 1 : maxBright / 2 * 3, 255);
        LEDS.setBrightness(maxBright);
#if SAVE_EEPROM > 0
        write_eeprom_8(EEPROM_INDEX_FOR_BRIGHT, maxBright);
#endif

        CTG_PRINT(F("Brightness+ "));
        CTG_PRINTLN(maxBright);

        break;
#endif

#if Command_Brightness_plus_R
      case Command_Brightness_plus_R: //  Увеличить максимальную яркость, при достижения максимума начать с минимума
        if (maxBright == 255)
          maxBright = 1;
        else
          maxBright = min((maxBright < 5) ? maxBright + 1 : maxBright / 2 * 3, 255);
        LEDS.setBrightness(maxBright);
#if SAVE_EEPROM > 0
        write_eeprom_8(EEPROM_INDEX_FOR_BRIGHT, maxBright);
#endif

        CTG_PRINT(F("Brightness+ "));
        CTG_PRINTLN(maxBright);

        break;
#endif

#if Command_Brightness_minus
      case Command_Brightness_minus: //  Уменьшить максимальную яркость и остановится если достигли минимума
        maxBright = max((maxBright < 5) ? maxBright - 1 : maxBright / 3 * 2, 1);
        LEDS.setBrightness(maxBright);
#if SAVE_EEPROM > 0
        write_eeprom_8(EEPROM_INDEX_FOR_BRIGHT, maxBright);
#endif

        CTG_PRINT(F("Brightness- "));
        CTG_PRINTLN(maxBright);

        break;
#endif

#if Command_Brightness_minus_R
      case Command_Brightness_minus_R: //  Уменьшить максимальную яркость, при достижения минимума начать с максимума
        if (maxBright == 1)
          maxBright = 255;
        else
          maxBright = max((maxBright < 5) ? maxBright - 1 : maxBright / 3 * 2, 1);
        LEDS.setBrightness(maxBright);
#if SAVE_EEPROM > 0
        write_eeprom_8(EEPROM_INDEX_FOR_BRIGHT, maxBright);
#endif

        CTG_PRINT(F("Brightness- "));
        CTG_PRINTLN(maxBright);

        break;
#endif

#if Command_Reset
      case Command_Reset: //  Сброс всех настроек
        ledMode = 0;
        strobe_mode(ledMode, 1);
        LEDS.show();
        bootme();

        CTG_PRINTLN(F("Reset"));

        break;
#endif

#if Command_Stop
      case Command_Stop: //  Стоп
        setOff(demorun);
        ledMode = 255;
        palchg = 0;
        solid = CRGB::Black;
        LEDS.setBrightness(0);

        CTG_PRINTLN(F("Stop"));

        break;
#endif

#if Command_Start
      case Command_Start: //  Старт
        setOn(demorun);
        ledMode = newMode;
        LEDS.setBrightness(maxBright);

        CTG_PRINTLN(F("Start"));

        break;
#endif

#if Command_Start_Stop
      case Command_Start_Stop: //  Старт/Стоп
        if (demorun >= 100)
        {
          setOn(demorun);
          ledMode = newMode;
          LEDS.setBrightness(maxBright);

          CTG_PRINTLN(F("Start"));
        }
        else
        {
          setOff(demorun);
          ledMode = 255;
          palchg = 0;
          solid = CRGB::Black;
          LEDS.setBrightness(0);

          CTG_PRINTLN(F("Stop"));
        }
        break;
#endif

#if Command_Demo_On
      case Command_Demo_On: //  Востановим демо режим (какой был до этого)
        setOn(demorun);
        meshwait();

        CTG_PRINTLN(F("Demo On"));

        break;
#endif

#if Command_Demo_Sequence
      case Command_Demo_Sequence: //  Включит демо режим (перебор)
        demorun = 1;
        meshwait();

        CTG_PRINTLN(F("Demo Sequence On"));

        break;
#endif

#if Command_Demo_Random
      case Command_Demo_Random: //  Включит демо режим (Случайно)
        demorun = 2;
        meshwait();

        CTG_PRINTLN(F("Demo Random On"));

        break;
#endif

#if Command_Demo_Sequence_Select
      case Command_Demo_Sequence_Select: //  Включит демо режим из выбранных режимов (перебор)
        demorun = 3;
        meshwait();

        CTG_PRINTLN(F("Demo Sequence Select On"));

        break;
#endif

#if Command_Demo_Random_Select
      case Command_Demo_Random_Select: //  Включит демо режим из выбранных режимов (Случайно)
        demorun = 4;
        meshwait();

        CTG_PRINTLN(F("Demo Random Select On"));

        break;
#endif

#if Command_Setup_Mode_On
      case Command_Setup_Mode_On: //  Перейти в режим настройки
        if (demorun < 100)
          demorun += 100;
        ledMode = 200;
        LED2_On; // Включить светодиод

        CTG_PRINTLN(F("Setup Mode On "));

        break;
#endif

#if Command_Length_Garland_plus
      case Command_Length_Garland_plus: //  Увеличить количество светодиодов в гирлянде
        setOff(demorun);
        ledMode = 200;
        if (numLeds < (MAX_LEDS - 1))
          numLeds++; // Новое значение
#if SAVE_EEPROM > 0
#if MAX_LEDS < 255
        write_eeprom_8(EEPROM_INDEX_FOR_STRANDLEN, numLeds); // Сохранить в память
        write_eeprom_8(EEPROM_INDEX_FOR_STRANDLEN + 1, 0);    // Сохранить в память
#else
        write_eeprom_8(EEPROM_INDEX_FOR_STRANDLEN, (uint16_t)(numLeds) & 0x00ff); // Сохранить в память
        write_eeprom_8(EEPROM_INDEX_FOR_STRANDLEN + 1, (uint16_t)(numLeds) >> 8); // Сохранить в память
#endif
#endif

        CTG_PRINT(F("Length Garland "));
        CTG_PRINTLN(numLeds);

        break;
#endif

#if Command_Length_Garland_minus
      case Command_Length_Garland_minus: //  Уменьшить количество светодиодов в гирлянде
        setOff(demorun);
        ledMode = 200;
        if (numLeds > 0)
          numLeds--; // Новое значение
#if SAVE_EEPROM > 0
#if MAX_LEDS < 255
        write_eeprom_8(EEPROM_INDEX_FOR_STRANDLEN, numLeds); // Сохранить в память
        write_eeprom_8(EEPROM_INDEX_FOR_STRANDLEN + 1, 0);    // Сохранить в память
#else
        write_eeprom_8(EEPROM_INDEX_FOR_STRANDLEN, (uint16_t)(numLeds) & 0x00ff); // Сохранить в память
        write_eeprom_8(EEPROM_INDEX_FOR_STRANDLEN + 1, (uint16_t)(numLeds) >> 8); // Сохранить в память
#endif
#endif

        CTG_PRINT(F("Length Garland "));
        CTG_PRINTLN(numLeds);

        break;
#endif

#if Command_Rotate
      case Command_Rotate: //  Сменить направление движения эффектов
        if (protocol == 1)
        { // отключить повтор
          thisdir = thisdir * -1;

          CTG_PRINTLN(F("Rotate"));
        }
        break;
#endif

#if Command_Speed_minus
      case Command_Speed_minus: //  Замедлить движение
        if (thisdelay < 1000)
          thisdelay++;

        CTG_PRINT(F("Speed- "));
        CTG_PRINTLN(thisdelay);

        break;
#endif

#if Command_Speed_plus
      case Command_Speed_plus: //  Ускорить движение
        if (thisdelay > 0)
          thisdelay--;

        CTG_PRINT(F("Speed+ "));
        CTG_PRINTLN(thisdelay);

        break;
#endif

#if Command_Glitter
      case Command_Glitter: //  Включить/выключить сверкание
        if (protocol == 1)
        { // отключить повтор
          extFlag.Glitter = !extFlag.Glitter;

          CTG_PRINT(F("Glitter "));
          CTG_PRINTLN(extFlag.Glitter);
        }
        break;
#endif

#if Command_BackGround
      case Command_BackGround: //  Включить/выключить заполнение фона
        if (protocol == 1)
        { // отключить повтор
          extFlag.Background = !extFlag.Background;

          CTG_PRINT(F("BackGround "));
          CTG_PRINTLN(extFlag.Background);
        }
        break;
#endif

#if Command_Candle
      case Command_Candle: //  Включить/выключить Свечки
#if CANDLE_KOL > 0
        if (protocol == 1)
        { // отключить повтор
          extFlag.Candle = !extFlag.Candle;
          PolCandle = random8(CANDLE_KOL);

          CTG_PRINT(F("Candle "));
          CTG_PRINTLN(extFlag.Candle);
        }
#endif
        break;
#endif

#if Command_Previous_mode
      case Command_Previous_mode: //  Предыдущий эффект
        if (protocol == 1)
        { // отключить повтор
          if (newMode > 0)
            SetMode(newMode - 1);
          else
            SetMode(MAX_MODE - 1);

          CTG_PRINTLN(F("Previous mode"));
        }
        break;
#endif

#if Command_Previous_mode_Demo
      case Command_Previous_mode_Demo: //  Предыдущий эффект. Оставляет демонстрационный режим
        if (protocol == 1)
        { // отключить повтор
          if (newMode > 0)
            SetMode(newMode - 1);
          else
            SetMode(MAX_MODE - 1);
          setOn(demorun);

          CTG_PRINTLN(F("Previous mode + Demo"));
        }
        break;
#endif

#if Command_Next_mode
      case Command_Next_mode: //  Следующий эффект
        if (protocol == 1)
        { // отключить повтор
          if (newMode >= (MAX_MODE - 1))
            SetMode(0);
          else
            SetMode(newMode + 1);

          CTG_PRINTLN(F("Next mode"));
        }
        break;
#endif

#if Command_Next_mode_Demo
      case Command_Next_mode_Demo: //  Следующий эффект. Оставляет демонстрационный режим
        if (protocol == 1)
        { // отключить повтор
          if (newMode >= (MAX_MODE - 1))
            SetMode(0);
          else
            SetMode(newMode + 1);
          setOn(demorun);

          CTG_PRINTLN(F("Next mode + Demo"));
        }
        break;
#endif

#if Command_Mode_0
      case Command_Mode_0: //  Эффект 0
        SetMode(0);
        break;
#endif

#if Command_Mode_1
      case Command_Mode_1: //  Эффект 1
        SetMode(1);
        break;
#endif

#if Command_Mode_2
      case Command_Mode_2: //  Эффект 2
        SetMode(2);
        break;
#endif

#if Command_Mode_3
      case Command_Mode_3: //  Эффект 3
        SetMode(3);
        break;
#endif

#if Command_Mode_4
      case Command_Mode_4: //  Эффект 4
        SetMode(4);
        break;
#endif

#if Command_Mode_5
      case Command_Mode_5: //  Эффект 5
        SetMode(5);
        break;
#endif

#if Command_Mode_6
      case Command_Mode_6: //  Эффект 6
        SetMode(6);
        break;
#endif

#if Command_Mode_7
      case Command_Mode_7: //  Эффект 7
        SetMode(7);
        break;
#endif

#if Command_Mode_8
      case Command_Mode_8: //  Эффект 8
        SetMode(8);
        break;
#endif

#if Command_Mode_9
      case Command_Mode_9: //  Эффект 9
        SetMode(9);
        break;
#endif

#if Command_Mode_10
      case Command_Mode_10: //  Эффект 10
        SetMode(10);
        break;
#endif

#if Command_Mode_11
      case Command_Mode_11: //  Эффект 11
        SetMode(11);
        break;
#endif

#if Command_Mode_12
      case Command_Mode_12: //  Эффект 12
        SetMode(12);
        break;
#endif

#if Command_Mode_13
      case Command_Mode_13: //  Эффект 13
        SetMode(13);
        break;
#endif

#if Command_Mode_14
      case Command_Mode_14: //  Эффект 14
        SetMode(14);
        break;
#endif

#if Command_Mode_15
      case Command_Mode_15: //  Эффект 15
        SetMode(15);
        break;
#endif

#if Command_Mode_16
      case Command_Mode_16: //  Эффект 16
        SetMode(16);
        break;
#endif

#if Command_Mode_17
      case Command_Mode_17: //  Эффект 17
        SetMode(17);
        break;
#endif

#if Command_Mode_18
      case Command_Mode_18: //  Эффект 18
        SetMode(18);
        break;
#endif

#if Command_Mode_19
      case Command_Mode_19: //  Эффект 19
        SetMode(19);
        break;
#endif

#if Command_Mode_20
      case Command_Mode_20: //  Эффект 20
        SetMode(20);
        break;
#endif

#if Command_Mode_21
      case Command_Mode_21: //  Эффект 21
        SetMode(21);
        break;
#endif

#if Command_Mode_22
      case Command_Mode_22: //  Эффект 22
        SetMode(22);
        break;
#endif

#if Command_Mode_23
      case Command_Mode_23: //  Эффект 23
        SetMode(23);
        break;
#endif

#if Command_Mode_24
      case Command_Mode_24: //  Эффект 24
        SetMode(24);
        break;
#endif

#if Command_Mode_25
      case Command_Mode_25: //  Эффект 25
        SetMode(25);
        break;
#endif

#if Command_Mode_26
      case Command_Mode_26: //  Эффект 26
        SetMode(26);
        break;
#endif

#if Command_Mode_27
      case Command_Mode_27: //  Эффект 27
        SetMode(27);
        break;
#endif

#if Command_Mode_28
      case Command_Mode_28: //  Эффект 28
        SetMode(28);
        break;
#endif

#if Command_Mode_29
      case Command_Mode_29: //  Эффект 29
        SetMode(29);
        break;
#endif

#if Command_Mode_30
      case Command_Mode_0: //  Эффект 30
        SetMode(30);
        break;
#endif

#if Command_Mode_31
      case Command_Mode_31: //  Эффект 31
        SetMode(31);
        break;
#endif

#if Command_Mode_32
      case Command_Mode_32: //  Эффект 32
        SetMode(32);
        break;
#endif

#if Command_Mode_33
      case Command_Mode_33: //  Эффект 33
        SetMode(33);
        break;
#endif

#if Command_Mode_34
      case Command_Mode_34: //  Эффект 34
        SetMode(34);
        break;
#endif

#if Command_Mode_35
      case Command_Mode_35: //  Эффект 35
        SetMode(35);
        break;
#endif

#if Command_Mode_36
      case Command_Mode_36: //  Эффект 36
        SetMode(36);
        break;
#endif

#if Command_Mode_37
      case Command_Mode_37: //  Эффект 37
        SetMode(37);
        break;
#endif

#if Command_Mode_38
      case Command_Mode_38: //  Эффект 38
        SetMode(38);
        break;
#endif

#if Command_Mode_39
      case Command_Mode_39: //  Эффект 39
        SetMode(39);
        break;
#endif

#if Command_Mode_40
      case Command_Mode_40: //  Эффект 40
        SetMode(40);
        break;
#endif

#if Command_Mode_41
      case Command_Mode_41: //  Эффект 41
        SetMode(41);
        break;
#endif

#if Command_Save_Mode
      case Command_Save_Mode: //  Сохранить эффект как запускающийся первым
        if (protocol == 1)
        { // отключить повтор
#if SAVE_EEPROM > 0
          write_eeprom_8(EEPROM_INDEX_FOR_STARTMODE, ledMode);

          CTG_PRINTLN(F("Save Mode"));

#endif
        }
        break;
#endif

#if Command_Delay_minus
      case Command_Delay_minus: //  Уменьшить задержку на 100ms
        setOff(demorun);
        ledMode = 201;
        if (meshdelay > 0)
          meshdelay--; // Новое значение
#if SAVE_EEPROM > 0
        write_eeprom_8(EEPROM_INDEX_FOR_STRANDEL, meshdelay);
#endif

        CTG_PRINT(F("Delay "));
        CTG_PRINT(meshdelay * 100);
        CTG_PRINTLN(F(" ms"));

        break;
#endif

#if Command_Delay_plus
      case Command_Delay_plus: //  Увеличить задержку на 100ms
        setOff(demorun);
        ledMode = 201;
        if (meshdelay < 100)
          meshdelay++; // Новое значение
#if SAVE_EEPROM > 0
        write_eeprom_8(EEPROM_INDEX_FOR_STRANDEL, meshdelay);
#endif

        CTG_PRINT(F("Delay "));
        CTG_PRINT(meshdelay * 100);
        CTG_PRINTLN(F(" ms"));

        break;
#endif

#if Command_Palette_Stop
      case Command_Palette_Stop: //  Остановить перебор Палитр
        palchg = 0;

        CTG_PRINT(F("Palette_Stop "));
        CTG_PRINTLN(gCurrentPaletteNumber);

        break;
#endif

#if Command_Palette_Previous
      case Command_Palette_Previous: //  Установить предыдущую палитру
        if (protocol == 1)
        { // отключить повтор
          palchg = 1;
          if (gCurrentPaletteNumber > 0)
            gCurrentPaletteNumber--;
          else
            gCurrentPaletteNumber = gGradientPaletteCount - 1;
          gTargetPalette = (gGradientPalettes[gCurrentPaletteNumber]);

          CTG_PRINT(F("Palette- "));
          CTG_PRINTLN(gCurrentPaletteNumber);
        }
        break;
#endif

#if Command_Palette_Next
      case Command_Palette_Next: //  Установить следующую палитру
        if (protocol == 1)
        { // отключить повтор
          palchg = 2;
          if (gCurrentPaletteNumber < (gGradientPaletteCount - 1))
            gCurrentPaletteNumber++;
          else
            gCurrentPaletteNumber = 0;
          gTargetPalette = (gGradientPalettes[gCurrentPaletteNumber]);

          CTG_PRINT(F("Palette+ "));
          CTG_PRINTLN(gCurrentPaletteNumber);
        }
        break;
#endif

#if Command_Palette_Auto
      case Command_Palette_Auto: //  Включить перебор палитр
        palchg = 3;

        CTG_PRINTLN(F("Continuous palette change"));

        break;
#endif

#if Command_Solid_Black
      case Command_Solid_Black: //  Установить цвет Черный
        setOff(demorun);
        ledMode = 255;
        palchg = 0;
        solid = CRGB::Black;

        CTG_PRINTLN(F("Solid_Black"));

        break;
#endif

#if Command_Solid_Red
      case Command_Solid_Red: //  Установить цвет Красный
        setOff(demorun);
        ledMode = 255;
        palchg = 0;
        solid = set_new_eorder(CRGB::Red);

        CTG_PRINTLN(F("Solid_Red"));

        break;
#endif

#if Command_Solid_Orange
      case Command_Solid_Orange: //  Установить цвет Оранжевый
        setOff(demorun);
        ledMode = 255;
        palchg = 0;
        solid = set_new_eorder(CRGB::Orange);

        CTG_PRINTLN(F("Solid_Orange"));

        break;
#endif

#if Command_Solid_Yellow
      case Command_Solid_Yellow: //  Установить цвет Желтый
        setOff(demorun);
        ledMode = 255;
        palchg = 0;
        solid = set_new_eorder(CRGB::Yellow);

        CTG_PRINTLN(F("Solid_Yellow"));

        break;
#endif

#if Command_Solid_Green
      case Command_Solid_Green: //  Установить цвет Зеленый
        setOff(demorun);
        ledMode = 255;
        palchg = 0;
        solid = set_new_eorder(CRGB::Green);

        CTG_PRINTLN(F("Solid_Green"));

        break;
#endif

#if Command_Solid_SkyBlue
      case Command_Solid_SkyBlue: //  Установить цвет Голубой
        setOff(demorun);
        ledMode = 255;
        palchg = 0;
        solid = set_new_eorder(CRGB::SkyBlue);

        CTG_PRINTLN(F("Solid_SkyBlue"));

        break;
#endif

#if Command_Solid_Blue
      case Command_Solid_Blue: //  Установить цвет Синий
        setOff(demorun);
        ledMode = 255;
        palchg = 0;
        solid = set_new_eorder(CRGB::Blue);

        CTG_PRINTLN(F("Solid_Blue"));

        break;
#endif

#if Command_Solid_Violet
      case Command_Solid_Violet: //  Установить цвет Фиолетовый
        setOff(demorun);
        ledMode = 255;
        palchg = 0;
        solid = set_new_eorder(CRGB::Violet);

        CTG_PRINTLN(F("Solid_Violet"));

        break;
#endif

#if Command_Solid_White
      case Command_Solid_White: //  Установить цвет Белый
        setOff(demorun);
        ledMode = 255;
        palchg = 0;
        solid = CRGB::White;

        CTG_PRINTLN(F("Solid_White"));

        break;
#endif

      default:
        break; // We could do something by default

      } // switch command
    }
    else
    { //        Режим настройки

      CTG_PRINT(F("Setup command: 0x"));
      CTG_PRINTLN_2(command, HEX);

      switch (command)
      {

#if Setup_Command_Setup_Mode_Off
      case Setup_Command_Setup_Mode_Off: // Выйти из режима настройки
#if Setup_Command_Setup_Mode_Off1
      case Setup_Command_Setup_Mode_Off1: // Выйти из режима настройки
#endif
#if Setup_Command_Setup_Mode_Off2
      case Setup_Command_Setup_Mode_Off2: // Выйти из режима настройки
#endif
#if Setup_Command_Setup_Mode_Off3
      case Setup_Command_Setup_Mode_Off3: // Выйти из режима настройки
#endif
                                          // ledMode = newMode;
                                          // setOn(demorun);
#if SAVE_EEPROM > 0
#if MAX_LEDS < 255
        write_eeprom_8(EEPROM_INDEX_FOR_STRANDLEN, numLeds); // Сохранить в память
        write_eeprom_8(EEPROM_INDEX_FOR_STRANDLEN + 1, 0);    // Сохранить в память
#else
        write_eeprom_8(EEPROM_INDEX_FOR_STRANDLEN, (uint16_t)(numLeds) & 0x00ff); // Сохранить в память
        write_eeprom_8(EEPROM_INDEX_FOR_STRANDLEN + 1, (uint16_t)(numLeds) >> 8); // Сохранить в память
#endif

#if SAVE_EEPROM == 1
        write_eeprom_8(EEPROM_INDEX_FOR_EXTFLAG, extFlag.Byte); // сохраним в EPROM расширенные настройки
#endif
#endif

        CTG_PRINTLN(F("Setup Mode Off "));
        CTG_PRINT(F("Leds num: "));
        CTG_PRINTLN(numLeds);
        print_eorder();
        CTG_PRINTLN(F("Reset "));

        bootme();
        break;
#endif
#if Setup_Command_Length_Garland_plus
      case Setup_Command_Length_Garland_plus: //  Увеличить количество светодиодов в гирлянде
        if (numLeds < MAX_LEDS)
          numLeds++; // Новое значение

        CTG_PRINT(F("Length Garland Plus: "));
        CTG_PRINTLN(numLeds);

        break;
#endif

#if Setup_Command_Length_Garland_plus_speed
      case Setup_Command_Length_Garland_plus_speed: //  Увеличить количество светодиодов в гирлянде
        if (numLeds < (MAX_LEDS - 10))
          numLeds += 10;
        else
          numLeds = MAX_LEDS; // Новое значение

        CTG_PRINT(F("Length Garland Plus: "));
        CTG_PRINTLN(numLeds);

        break;
#endif

#if Setup_Command_Length_Garland_minus
      case Setup_Command_Length_Garland_minus: //  Уменьшить количество светодиодов в гирлянде
        if (numLeds > 1)
          numLeds--; // Новое значение

        CTG_PRINT(F("Length Garland Munus: "));
        CTG_PRINTLN(numLeds);

        break;
#endif

#if Setup_Command_Length_Garland_minus_speed
      case Setup_Command_Length_Garland_minus_speed: //  Уменьшить количество светодиодов в гирлянде
        if (numLeds > 10)
          numLeds -= 10;
        else
          numLeds = 1; // Новое значение

        CTG_PRINT(F("Length Garland Munus: "));
        CTG_PRINTLN(numLeds);

        break;
#endif

#if Setup_Command_Solid_Green
      case Setup_Command_Solid_Green: //  Установить цвет Зеленый
        ledMode = 221;                // Новое значение

        CTG_PRINTLN(F("Green Red Blue"));

        break;
#endif

#if Setup_Command_Solid_Red
      case Setup_Command_Solid_Red: //  Установить цвет Красный
        ledMode = 220;              // Новое значение

        CTG_PRINTLN(F("Red Green Blue"));

        break;
#endif

      default:
        break; // We could do something by default

      } // switch command
    }

    protocol = 0; // Reset protocol variable to not read the same value twice.

  } // if protocol

} // getirl()

void bootme()
{ // This is used to reset all the Arduinos so that their millis() counters are all in sync.
#if defined(__AVR__)
  asm volatile("jmp 0");
#elif defined(ESP32)
  ESP.restart();
#elif defined(STM32L1XX_MD)
  NVIC_SystemReset();
#else
  setup();
#endif

} // bootme()

void meshwait()
{ // After we press a mode key, we need to wait a bit for the sequence to start.
  CTG_PRINT(F("Mesh delay: "));
  CTG_PRINT(meshdelay * 100);
  CTG_PRINTLN(F("ms delay."));

  LEDS.delay(meshdelay * 100); // Here's our notamesh wait upon keypress. Oh god I'm so sorry there's a delay statement here. At least it's only used upon mode change keypress.

} // meshwait()

#endif
