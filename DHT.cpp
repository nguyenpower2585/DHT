/* DHT library 1.0 by enotdev */
#include "DHT.h"

/* DHT dht();
Enables the library */
DHT::DHT(void) {}

/* void dht.begin(uint8_t pin, uint8_t model, uint8_t cnt=6);
Starts the sensor.
Parameters:
* uint8_t pin: number of digital pin where sensor is connected
* uint8_t model: model of sensor, one of these:
    - DHT11
	- DHT21
	- DHT22
* uint8_t cnt: this parameter changes count of bytes what controller will take from
  sensor. Default is 6. We don't recommend to change it.
*/
void DHT::begin(uint8_t pin, uint8_t model, uint8_t cnt) {
 _pin = pin;
 _model = model;
 _count = cnt;
 firstreading = true;
 pinMode(_pin, INPUT);
 digitalWrite(_pin, HIGH);
 _lastreadtime = 0;
}

/* float dht.readTemp(bool scale);
Reads the temperature from sensor.
Parameters:
* bool scale: scale of value. It may be FARENHEIT, CELCIUS or KELVIN.
*/
float DHT::readTemp(uint8_t scale) {
 float f;
 if (read()) {
  switch (_model) {
   case DHT11: 
    f = data[2];
   break;
   case DHT21:
   case DHT22:
    f = data[2] & 0x7F;
	f *= 256;
	f += data[3];
    f /= 10;
	if (data[2] & 0x80) {f *= -1;}
   break;
  }
  if (scale == FARENHEIT) {f = f * 9 / 5 + 32;}
  if (scale == KELVIN) {f = f - 273.15;}
  return f;
 } else {
  Serial.println("Fail in procedure DHT::readTemp()");
  return NAN;
 }
}

/* float dht.readHumidity(void);
Reads the temperature from sensor.
Parameters:
* bool scale: scale of value. It may be FARENHEIT, CELCIUS or KELVIN.
*/
float DHT::readHumidity(void) {
 float f;
 if (read()) {
  switch (_model) {
   case DHT11:
    f = data[0];
   break;
   case DHT21:
   case DHT22:
    f = data[0];
	f *= 256;
	f += data[1];
	f /= 10;
   break;
  }
  return f;
 } else {
  Serial.println("Fail in procedure DHT::readHumidity()");
  return NAN;
 }
}

boolean DHT::read(void) {
 uint8_t laststate = HIGH, counter = 0, j = 0, i;
 unsigned long currenttime;
 digitalWrite(_pin, HIGH);
 delay(250);
 currenttime = millis();
 if (currenttime < _lastreadtime) {
  _lastreadtime = 0;
 }
 if (!firstreading && ((currenttime - _lastreadtime) < 2000)) {
  return true;
 }
 firstreading = false;
 _lastreadtime = millis();
 data[0] = data[1] = data[2] = data[3] = data[4] = 0;
 pinMode(_pin, OUTPUT);
 digitalWrite(_pin, LOW);
 delay(20);
 cli();
 digitalWrite(_pin, HIGH);
 delayMicroseconds(40);
 pinMode(_pin, INPUT);
 for (i=0; i<85; i++) {
  counter = 0;
  while (digitalRead(_pin) == laststate) {
   counter++;
   delayMicroseconds(1);
   if (counter == 255) {break;}
  }
  laststate = digitalRead(_pin);
  if (counter == 255) {break;}
  if ((i >= 4) && (i%2 == 0)) {
   data[j/8] <<= 1;
   if (counter > _count) {data[j/8] |= 1;}
   j++;
  }
 }
 sei();
 return ((j >= 40) && (data[4] == ((data[0] + data[1] + data[2] + data[3]) & 0xFF)));
}