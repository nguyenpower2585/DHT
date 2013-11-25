/* DHT library 1.0 by enotdev */
#ifndef DHT_H
#define DHT_H

#if ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

#define DHT11 11
#define DHT22 22
#define DHT21 21

#define CELCIUS 1
#define FARENHEIT 2
#define KELVIN 3

class DHT {
 public:
  DHT(void);
  void begin(uint8_t pin, uint8_t model, uint8_t cnt=6);
  float readTemp(uint8_t scale = false);
  float readHumidity(void);

  private:
  uint8_t data[6];
  uint8_t _pin, _model, _count;
  boolean read(void);
  unsigned long _lastreadtime;
  boolean firstreading;
};
#endif