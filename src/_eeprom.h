#pragma once

#include "../setting.h"
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
void eeprom_init()
{
    // проверка правильности в EEPROM байта корректности записи
  if ((read_eeprom_8(EEPROM_INDEX_FOR_ISINIT) != INITVAL) ||
      (NUM_LEDS > MAX_LEDS) ||
      ((ledMode > maxMode) && (ledMode != 100)))
  { // Не корректен
    write_eeprom_8(EEPROM_INDEX_FOR_STARTMODE, INITMODE);
#if MAX_LEDS < 255
    write_eeprom_8(EEPROM_INDEX_FOR_STRANDLEN, INITLEN);
#else
    write_eeprom_8(EEPROM_INDEX_FOR_STRANDLEN, (uint16_t)(INITLEN) & 0x00ff);
    write_eeprom_8(EEPROM_INDEX_FOR_STRANDLEN + 1, (uint16_t)(INITLEN) >> 8);
#endif
    write_eeprom_8(EEPROM_INDEX_FOR_STRANDEL, INITDEL);

    ExtFlag.Glitter = GLITER_ON;
    ExtFlag.Background = BACKGR_ON;
    ExtFlag.Candle = CANDLE_ON;
#if SAVE_EEPROM == 1
    write_eeprom_8(EEPROM_INDEX_FOR_EXTFLAG, ExtFlag.Byte);
#endif
#if !defined(EORDER)
    write_eeprom_8(EEPROM_INDEX_FOR_EORDER, eorder_index);
#endif
    write_eeprom_8(EEPROM_INDEX_FOR_ISINIT, INITVAL);

    ledMode = INITMODE;
    NUM_LEDS = INITLEN;
    meshdelay = INITDEL;
  }
  else
  {
#if SAVE_EEPROM == 1
    ExtFlag.Byte = read_eeprom_8(EEPROM_INDEX_FOR_EXTFLAG); // Прочитаем расширенные настройки
#else
    ExtFlag.Glitter = GLITER_ON;    // Флаг включения блеска
    ExtFlag.Background = BACKGR_ON; // Флаг включения заполнения фона
    ExtFlag.Candle = CANDLE_ON;     // Флаг включения свечей
#endif

    max_bright = read_eeprom_8(EEPROM_INDEX_FOR_BRIGHT);
#if !defined(EORDER)
    eorder_index = read_eeprom_8(EEPROM_INDEX_FOR_EORDER);
    if (eorder_index > 5)
    {
      eorder = 0;
    }
#endif
    ledMode = read_eeprom_8(EEPROM_INDEX_FOR_STARTMODE);
    NUM_LEDS = read_eeprom_8(EEPROM_INDEX_FOR_STRANDLEN);
#if MAX_LEDS < 255
    if (read_eeprom_8(EEPROM_INDEX_FOR_STRANDLEN + 1))
      // Если почемуто светодиодов больше чем размер переменной
      NUM_LEDS = MAX_LEDS;
#else
    NUM_LEDS += (uint16_t)read_eeprom_8(EEPROM_INDEX_FOR_STRANDLEN + 1) << 8;
#endif
    meshdelay = read_eeprom_8(EEPROM_INDEX_FOR_STRANDEL);
  }
}
#endif
