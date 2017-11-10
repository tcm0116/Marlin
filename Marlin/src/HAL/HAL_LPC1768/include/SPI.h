/*
 * Copyright (c) 2010 by Cristian Maglie <c.maglie@arduino.cc>
 * Copyright (c) 2014 by Paul Stoffregen <paul@pjrc.com> (Transaction API)
 * Copyright (c) 2014 by Matthijs Kooijman <matthijs@stdin.nl> (SPISettings AVR)
 * Copyright (c) 2014 by Andrew J. Kroll <xxxajk@gmail.com> (atomicity fixes)
 * SPI Master library for arduino.
 *
 * This file is free software; you can redistribute it and/or modify
 * it under the terms of either the GNU General Public License version 2
 * or the GNU Lesser General Public License version 2.1, both as
 * published by the Free Software Foundation.
 */

#ifndef _SPI_H_INCLUDED
#define _SPI_H_INCLUDED

#include <Arduino.h>
#include "HAL_SPI.h"

#ifndef LSBFIRST
  #define LSBFIRST 0
#endif
#ifndef MSBFIRST
  #define MSBFIRST 1
#endif

#define SPI_MODE0 0x00
#define SPI_MODE1 0x04
#define SPI_MODE2 0x08
#define SPI_MODE3 0x0C

class SPISettings {
public:
  SPISettings(uint32_t clock, uint8_t bitOrder, uint8_t dataMode) :
    clock(clock),
    bitOrder(bitOrder),
    dataMode(dataMode) {
  }
  SPISettings() :
    clock(4000000),
    bitOrder(MSBFIRST),
    dataMode(SPI_MODE0) {
  }
private:
  uint32_t clock;
  uint8_t bitOrder;
  uint8_t dataMode;

  friend class SPIClass;
};


class SPIClass {
public:
  // Initialize the SPI library
  inline static void begin() { spiBegin(); }

  // Before using SPI.transfer() or asserting chip select pins,
  // this function is used to gain exclusive access to the SPI bus
  // and configure the correct settings.
  inline static void beginTransaction(SPISettings s) {
    settings = s;
    spiInit(settings.clock);
  }

  // Write to the SPI bus (MOSI pin) and also receive (MISO pin)
  inline static uint8_t transfer(uint8_t data) { spiSend(data); return spiRec(); }
  inline static uint16_t transfer16(uint16_t data) { 
    union { uint16_t val; struct { uint8_t lsb; uint8_t msb; }; } in, out;
    in.val = data;
    if (settings.bitOrder == MSBFIRST) {
      out.msb = transfer(in.msb);
      out.lsb = transfer(in.lsb);
    } else {
      out.lsb = transfer(in.lsb);
      out.msb = transfer(in.msb);
    }
    return out.val;
  }
  inline static void transfer(void *buf, size_t count) {
    uint8_t* p = (uint8_t*)buf;
    while (count-- > 0) {
      *p = transfer(*p);
      p++;
    }
  }
  inline static void endTransaction(void) { /* do nothing */ }

private:
  static SPISettings settings;
};

extern SPIClass SPI;

#endif
