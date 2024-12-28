#pragma once

#if SAVE_EEPROM
#include "_eeprom.h"
#endif
#include "function.h"

// ==== Работа с кнопками ============================
#if BUTTONS_NUM

void bootme();
void meshwait();
void getCommand();

void setMode(uint8_t Mode)
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
  strobeMode(Mode, 1); // Does NOT reset to 0.
#endif
#if CANDLE_KOL > 0
  polCandle = random8(CANDLE_KOL);
#endif
}

void getCommand()
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
#if SAVE_EEPROM
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
#if SAVE_EEPROM
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
#if SAVE_EEPROM
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
#if SAVE_EEPROM
        write_eeprom_8(EEPROM_INDEX_FOR_BRIGHT, maxBright);
#endif

        CTG_PRINT(F("Brightness- "));
        CTG_PRINTLN(maxBright);

        break;
#endif

#if Command_Reset
      case Command_Reset: //  Сброс всех настроек
        ledMode = 0;
        strobeMode(ledMode, 1);
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

          write_eeprom_8(EEPROM_INDEX_FOR_EXTFLAG, extFlag.Byte);

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

          write_eeprom_8(EEPROM_INDEX_FOR_EXTFLAG, extFlag.Byte);

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
          polCandle = random8(CANDLE_KOL);

          write_eeprom_8(EEPROM_INDEX_FOR_EXTFLAG, extFlag.Byte);

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
            setMode(newMode - 1);
          else
            setMode(MAX_MODE - 1);

          CTG_PRINTLN(F("Previous mode"));
        }
        break;
#endif

#if Command_Previous_mode_Demo
      case Command_Previous_mode_Demo: //  Предыдущий эффект. Оставляет демонстрационный режим
        if (protocol == 1)
        { // отключить повтор
          if (newMode > 0)
            setMode(newMode - 1);
          else
            setMode(MAX_MODE - 1);
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
            setMode(0);
          else
            setMode(newMode + 1);

          CTG_PRINTLN(F("Next mode"));
        }
        break;
#endif

#if Command_Next_mode_Demo
      case Command_Next_mode_Demo: //  Следующий эффект. Оставляет демонстрационный режим
        if (protocol == 1)
        { // отключить повтор
          if (newMode >= (MAX_MODE - 1))
            setMode(0);
          else
            setMode(newMode + 1);
          setOn(demorun);

          CTG_PRINTLN(F("Next mode + Demo"));
        }
        break;
#endif

#if Command_Mode_0
      case Command_Mode_0: //  Эффект 0
        setMode(0);
        break;
#endif

#if Command_Mode_1
      case Command_Mode_1: //  Эффект 1
        setMode(1);
        break;
#endif

#if Command_Mode_2
      case Command_Mode_2: //  Эффект 2
        setMode(2);
        break;
#endif

#if Command_Mode_3
      case Command_Mode_3: //  Эффект 3
        setMode(3);
        break;
#endif

#if Command_Mode_4
      case Command_Mode_4: //  Эффект 4
        setMode(4);
        break;
#endif

#if Command_Mode_5
      case Command_Mode_5: //  Эффект 5
        setMode(5);
        break;
#endif

#if Command_Mode_6
      case Command_Mode_6: //  Эффект 6
        setMode(6);
        break;
#endif

#if Command_Mode_7
      case Command_Mode_7: //  Эффект 7
        setMode(7);
        break;
#endif

#if Command_Mode_8
      case Command_Mode_8: //  Эффект 8
        setMode(8);
        break;
#endif

#if Command_Mode_9
      case Command_Mode_9: //  Эффект 9
        setMode(9);
        break;
#endif

#if Command_Mode_10
      case Command_Mode_10: //  Эффект 10
        setMode(10);
        break;
#endif

#if Command_Mode_11
      case Command_Mode_11: //  Эффект 11
        setMode(11);
        break;
#endif

#if Command_Mode_12
      case Command_Mode_12: //  Эффект 12
        setMode(12);
        break;
#endif

#if Command_Mode_13
      case Command_Mode_13: //  Эффект 13
        setMode(13);
        break;
#endif

#if Command_Mode_14
      case Command_Mode_14: //  Эффект 14
        setMode(14);
        break;
#endif

#if Command_Mode_15
      case Command_Mode_15: //  Эффект 15
        setMode(15);
        break;
#endif

#if Command_Mode_16
      case Command_Mode_16: //  Эффект 16
        setMode(16);
        break;
#endif

#if Command_Mode_17
      case Command_Mode_17: //  Эффект 17
        setMode(17);
        break;
#endif

#if Command_Mode_18
      case Command_Mode_18: //  Эффект 18
        setMode(18);
        break;
#endif

#if Command_Mode_19
      case Command_Mode_19: //  Эффект 19
        setMode(19);
        break;
#endif

#if Command_Mode_20
      case Command_Mode_20: //  Эффект 20
        setMode(20);
        break;
#endif

#if Command_Mode_21
      case Command_Mode_21: //  Эффект 21
        setMode(21);
        break;
#endif

#if Command_Mode_22
      case Command_Mode_22: //  Эффект 22
        setMode(22);
        break;
#endif

#if Command_Mode_23
      case Command_Mode_23: //  Эффект 23
        setMode(23);
        break;
#endif

#if Command_Mode_24
      case Command_Mode_24: //  Эффект 24
        setMode(24);
        break;
#endif

#if Command_Mode_25
      case Command_Mode_25: //  Эффект 25
        setMode(25);
        break;
#endif

#if Command_Mode_26
      case Command_Mode_26: //  Эффект 26
        setMode(26);
        break;
#endif

#if Command_Mode_27
      case Command_Mode_27: //  Эффект 27
        setMode(27);
        break;
#endif

#if Command_Mode_28
      case Command_Mode_28: //  Эффект 28
        setMode(28);
        break;
#endif

#if Command_Mode_29
      case Command_Mode_29: //  Эффект 29
        setMode(29);
        break;
#endif

#if Command_Mode_30
      case Command_Mode_0: //  Эффект 30
        setMode(30);
        break;
#endif

#if Command_Mode_31
      case Command_Mode_31: //  Эффект 31
        setMode(31);
        break;
#endif

#if Command_Mode_32
      case Command_Mode_32: //  Эффект 32
        setMode(32);
        break;
#endif

#if Command_Mode_33
      case Command_Mode_33: //  Эффект 33
        setMode(33);
        break;
#endif

#if Command_Mode_34
      case Command_Mode_34: //  Эффект 34
        setMode(34);
        break;
#endif

#if Command_Mode_35
      case Command_Mode_35: //  Эффект 35
        setMode(35);
        break;
#endif

#if Command_Mode_36
      case Command_Mode_36: //  Эффект 36
        setMode(36);
        break;
#endif

#if Command_Mode_37
      case Command_Mode_37: //  Эффект 37
        setMode(37);
        break;
#endif

#if Command_Mode_38
      case Command_Mode_38: //  Эффект 38
        setMode(38);
        break;
#endif

#if Command_Mode_39
      case Command_Mode_39: //  Эффект 39
        setMode(39);
        break;
#endif

#if Command_Mode_40
      case Command_Mode_40: //  Эффект 40
        setMode(40);
        break;
#endif

#if Command_Mode_41
      case Command_Mode_41: //  Эффект 41
        setMode(41);
        break;
#endif

#if Command_Save_Mode
      case Command_Save_Mode: //  Сохранить эффект как запускающийся первым
        if (protocol == 1)
        { // отключить повтор
#if SAVE_EEPROM
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
#if SAVE_EEPROM
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
#if SAVE_EEPROM
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
#if SAVE_EEPROM
        writeStrandLen();

        write_eeprom_8(EEPROM_INDEX_FOR_EXTFLAG, extFlag.Byte); // сохраним в EPROM расширенные настройки
#endif

        CTG_PRINTLN(F("Setup Mode Off "));
        CTG_PRINT(F("Leds num: "));
        CTG_PRINTLN(numLeds);
        print_eorder();
        CTG_PRINTLN(F("Reset "));

        bootme();
        break;
#endif

      default:
        break; // We could do something by default

      } // switch command
    }

    protocol = 0; // Reset protocol variable to not read the same value twice.

  } // if protocol

} // getCommand()

void bootme()
{ // This is used to reset all the Arduinos so that their millis() counters are all in sync.
#if defined(ARDUINO_ARCH_AVR)
  asm volatile("jmp 0");
#elif defined(ARDUINO_ARCH_ESP8266) || defined(ARDUINO_ARCH_ESP32)
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
