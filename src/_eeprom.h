#pragma once

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

uint16_t read_eeprom_16(uint16_t _index)
{
  uint16_t _data;

#if defined(__STM32F1__)
  _data = EEPROM.read(_index);
#else
  EEPROM.get(_index, _data);
#endif
  return (_data);
}

void write_eeprom_16(uint16_t _index, uint16_t _data)
{
#if defined(__STM32F1__)
  EEPROM.update(_index, _data);
#else
  EEPROM.put(_index, _data);
#endif

#if __USE_EEPROM_IN_FLASH__
  EEPROM.commit();
#endif
}

