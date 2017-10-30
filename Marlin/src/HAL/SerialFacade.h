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

class SerialFacadeBase {
public:
  virtual void begin(uint32_t baudrate) = 0;
  virtual int peek() = 0;
  virtual int read() = 0;
  virtual void write(uint8_t send) = 0;
  #if TX_BUFFER_SIZE > 0
    virtual void flushTX() = 0;
  #endif
  virtual int available() = 0;
  virtual void flush() = 0;

  virtual void printf(const char *format, ...) {
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

  virtual operator bool() = 0;

  virtual void print(const char value[]) = 0;
  virtual void print(char value, int base = 0) = 0;
  virtual void print(unsigned char value, int base = 0) = 0;
  virtual void print(int value, int base = 10) = 0;
  virtual void print(unsigned int value, int base = 10) = 0;
  virtual void print(long value, int base = 10) = 0;
  virtual void print(unsigned long value, int base = 10) = 0;

  virtual void print(float value, int round = 2) = 0;
  virtual void print(double value, int round = 2) = 0;

  virtual void println(const char value[]) = 0;
  virtual void println(char value, int base = 0) = 0;
  virtual void println(unsigned char value, int base = 0) = 0;
  virtual void println(int value, int base = 10) = 0;
  virtual void println(unsigned int value, int base = 10) = 0;
  virtual void println(long value, int base = 10) = 0;
  virtual void println(unsigned long value, int base = 10) = 0;
  virtual void println(float value, int round = 2) = 0;
  virtual void println(double value, int round = 2) = 0;
  virtual void println(void) = 0;
};

template <typename T> class SerialFacade : public SerialFacadeBase {
private:
  T& serial;

public:
  SerialFacade(T& serial) : serial(serial)                 {}

  virtual void begin(uint32_t baudrate)                     { serial.begin(baudrate); }
  virtual int peek()                                        { return serial.peek(); }
  virtual int read()                                        { return serial.read(); }
  void write(uint8_t send)                                  { serial.write(send); }
  #if TX_BUFFER_SIZE > 0
    virtual void flushTX()                                  { serial.flushTX(); }
  #endif
  virtual int available()                                   { return serial.available(); }
  virtual void flush()                                      { serial.flush(); }

  virtual operator bool()                                   { return serial ? true : false; }

  virtual void print(const char value[])                    { serial.print(value); }
  virtual void print(char value, int base = 0)              { serial.print(value, base); }
  virtual void print(unsigned char value, int base = 0)     { serial.print(value, base); }
  virtual void print(int value, int base = 10)              { serial.print(value, base); }
  virtual void print(unsigned int value, int base = 10)     { serial.print(value, base); }
  virtual void print(long value, int base = 10)             { serial.print(value, base); }
  virtual void print(unsigned long value, int base = 10)    { serial.print(value, base); }

  virtual void print(float value, int round = 2)            { serial.print(value, round); }
  virtual void print(double value, int round = 2)           { serial.print(value, round); }

  virtual void println(const char value[])                  { serial.println(value); }
  virtual void println(char value, int base = 0)            { serial.println(value, base); }
  virtual void println(unsigned char value, int base = 0)   { serial.println(value, base); }
  virtual void println(int value, int base = 10)            { serial.println(value, base); }
  virtual void println(unsigned int value, int base = 10)   { serial.println(value, base); }
  virtual void println(long value, int base = 10)           { serial.println(value, base); }
  virtual void println(unsigned long value, int base = 10)  { serial.println(value, base); }
  virtual void println(float value, int round = 2)          { serial.println(value, round); }
  virtual void println(double value, int round = 2)         { serial.println(value, round); }
  virtual void println(void)                                { serial.println(); }
};

#endif // _SERIALFACADE_H_
