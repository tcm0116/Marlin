/**
 * Marlin 3D Printer Firmware
 * Copyright (C) 2016 MarlinFirmware [https://github.com/MarlinFirmware/Marlin]
 *
 * Based on Sprinter and grbl.
 * Copyright (C) 2011 Camiel Gubbels / Erik van der Zalm
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

/**
 * SerialFacade.h - Wrapper class for the various serial port implementations in Marlin
 */

#ifndef _SERIALFACADE_H_
#define _SERIALFACADE_H_

#include "../core/macros.h"

template <typename T> class SerialFacade {
private:
  static T& serial;

public:
  SerialFacade(T& serial) : serial(serial) {}

  static inline operator bool()                                         { return !!serial; }

  static FORCE_INLINE void begin(uint32_t baudrate)                     { serial.begin(baudrate); }
  static FORCE_INLINE int peek()                                        { return serial.peek(); }
  static FORCE_INLINE int read()                                        { return serial.read(); }
  static FORCE_INLINE void write(uint8_t send)                          { serial.write(send); }
  #if TX_BUFFER_SIZE > 0
    static FORCE_INLINE void flushTX()                                  { serial.flushTX(); }
  #endif
  static FORCE_INLINE int available()                                   { return serial.available(); }
  static FORCE_INLINE void flush()                                      { serial.flush(); }

  static FORCE_INLINE void print(const char value[])                    { serial.print(value); }
  static FORCE_INLINE void print(char value, int base = 0)              { serial.print(value, base); }
  static FORCE_INLINE void print(unsigned char value, int base = 0)     { serial.print(value, base); }
  static FORCE_INLINE void print(int value, int base = 10)              { serial.print(value, base); }
  static FORCE_INLINE void print(unsigned int value, int base = 10)     { serial.print(value, base); }
  static FORCE_INLINE void print(long value, int base = 10)             { serial.print(value, base); }
  static FORCE_INLINE void print(unsigned long value, int base = 10)    { serial.print(value, base); }
  static FORCE_INLINE void print(float value, int round = 2)            { serial.print(value, round); }
  static FORCE_INLINE void print(double value, int round = 2)           { serial.print(value, round); }

  static FORCE_INLINE void println(const char value[])                  { serial.println(value); }
  static FORCE_INLINE void println(char value, int base = 0)            { serial.println(value, base); }
  static FORCE_INLINE void println(unsigned char value, int base = 0)   { serial.println(value, base); }
  static FORCE_INLINE void println(int value, int base = 10)            { serial.println(value, base); }
  static FORCE_INLINE void println(unsigned int value, int base = 10)   { serial.println(value, base); }
  static FORCE_INLINE void println(long value, int base = 10)           { serial.println(value, base); }
  static FORCE_INLINE void println(unsigned long value, int base = 10)  { serial.println(value, base); }
  static FORCE_INLINE void println(float value, int round = 2)          { serial.println(value, round); }
  static FORCE_INLINE void println(double value, int round = 2)         { serial.println(value, round); }
  static FORCE_INLINE void println(void)                                { serial.println(); }

  static inline void printf(const char *format, ...) {
    char RxBuffer[256];
    va_list vArgs;
    va_start(vArgs, format);
    int length = vsnprintf(RxBuffer, 256, format, vArgs);
    va_end(vArgs);
    if (length > 0 && length < 256) {
      for (int i = 0; i < length; ++i)
        write(RxBuffer[i]);
    }
  }

};

#endif // _SERIALFACADE_H_
