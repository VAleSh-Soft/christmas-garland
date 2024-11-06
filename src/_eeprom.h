#pragma once

#include "../setting.h"
#include "_leds.h"
#include <EEPROM.h>

// ===================================================

#if defined(ARDUINO_ARCH_ESP8266) || defined(ARDUINO_ARCH_ESP32) || defined(ARDUINO_ARCH_RP2040)
#define __EEPROM_IN_FLASH__ 1
#else
#define __EEPROM_IN_FLASH__ 0
#endif

// ===================================================

#if __EEPROM_IN_FLASH__
#define EEPROM_SIZE 128
#endif

// ===================================================

#if __EEPROM_IN_FLASH__
void eeprom_update(uint16_t _index, uint8_t _data)
{
  if (EEPROM.read(_index) != _data)
  {
    EEPROM.write(_index, _data);
  }
}
#endif

uint8_t read_eeprom_8(uint16_t _index)
{
#if __EEPROM_IN_FLASH__
  EEPROM.begin(EEPROM_SIZE);
#endif

  uint8_t result = EEPROM.read(_index);

#if __EEPROM_IN_FLASH__
  EEPROM.end();
#endif

  return result;
}

void write_eeprom_8(uint16_t _index, uint8_t _data)
{
#if __EEPROM_IN_FLASH__
  EEPROM.begin(EEPROM_SIZE);
  eeprom_update(_index, _data);
  EEPROM.commit();
  EEPROM.end();
#else

  EEPROM.update(_index, _data);

#endif
}

// ===================================================

#if SAVE_EEPROM > 0
// инициализация параметров, сохраненных в EEPROM
void eeprom_init()
{
  numLeds = read_eeprom_8(EEPROM_INDEX_FOR_STRANDLEN);
  ledMode = read_eeprom_8(EEPROM_INDEX_FOR_STARTMODE);

  // проверка правильности в EEPROM байта корректности записи
  if ((read_eeprom_8(EEPROM_INDEX_FOR_ISINIT) != INITVAL) ||
      (numLeds > MAX_LEDS) ||
      ((ledMode > MAX_MODE) && (ledMode != 100)))
  { // Не корректен
    write_eeprom_8(EEPROM_INDEX_FOR_STARTMODE, INITMODE);
#if MAX_LEDS < 255
    write_eeprom_8(EEPROM_INDEX_FOR_STRANDLEN, INITLEN);
#else
    write_eeprom_8(EEPROM_INDEX_FOR_STRANDLEN, (uint16_t)(INITLEN) & 0x00ff);
    write_eeprom_8(EEPROM_INDEX_FOR_STRANDLEN + 1, (uint16_t)(INITLEN) >> 8);
#endif
    write_eeprom_8(EEPROM_INDEX_FOR_STRANDEL, INITDEL);

    extFlag.Glitter = GLITER_ON;
    extFlag.Background = BACKGR_ON;
    extFlag.Candle = CANDLE_ON;
#if SAVE_EEPROM == 1
    write_eeprom_8(EEPROM_INDEX_FOR_EXTFLAG, extFlag.Byte);
#endif
#if !defined(EORDER)
    write_eeprom_8(EEPROM_INDEX_FOR_EORDER, eorder_index);
#endif
    write_eeprom_8(EEPROM_INDEX_FOR_ISINIT, INITVAL);

    ledMode = INITMODE;
    numLeds = INITLEN;
    meshdelay = INITDEL;
  }
  else
  {
#if SAVE_EEPROM == 1
    extFlag.Byte = read_eeprom_8(EEPROM_INDEX_FOR_EXTFLAG); // Прочитаем расширенные настройки
#else
    extFlag.Glitter = GLITER_ON;    // Флаг включения блеска
    extFlag.Background = BACKGR_ON; // Флаг включения заполнения фона
    extFlag.Candle = CANDLE_ON;     // Флаг включения свечей
#endif

    maxBright = read_eeprom_8(EEPROM_INDEX_FOR_BRIGHT);
#if !defined(EORDER)
    eorder_index = read_eeprom_8(EEPROM_INDEX_FOR_EORDER);
    if (eorder_index > 5)
    {
      eorder = 0;
    }
#endif
    ledMode = read_eeprom_8(EEPROM_INDEX_FOR_STARTMODE);
    numLeds = read_eeprom_8(EEPROM_INDEX_FOR_STRANDLEN);
#if MAX_LEDS < 255
    if (read_eeprom_8(EEPROM_INDEX_FOR_STRANDLEN + 1))
      // Если почемуто светодиодов больше чем размер переменной
      numLeds = MAX_LEDS;
#else
    numLeds += (uint16_t)read_eeprom_8(EEPROM_INDEX_FOR_STRANDLEN + 1) << 8;
#endif
    meshdelay = read_eeprom_8(EEPROM_INDEX_FOR_STRANDEL);
  }
}
#endif
