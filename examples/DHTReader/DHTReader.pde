/* DHTReader
to DHT library 1.0 by enotdev

This sketch reads temperature & humidity and sends it to Serial port.

* Connect pin 1 (on the left) of the sensor to +5V
* Connect pin 2 of the sensor to whatever your pin
* Connect pin 4 (on the right) of the sensor to GROUND
* Connect a 10K resistor from pin 2 (data) to pin 1 (power) of the sensor
*/

#include "DHT.h"

#define DHTPIN 2     // what pin we're connected to
/* Your model of sensor:
 if DHT11 - don't replace anything
 if DHT21 (AM2301) - replace string to #define DHTTYPE DHT21
 if DHT22 (AM2302) - replace string to #define DHTTYPE DHT22 */
#define DHTTYPE DHT11

DHT dht;

void setup() {
 Serial.begin(9600); 
 Serial.println("DHT Library Test: DHTReader");
 dht.begin(DHTPIN, DHTTYPE);
}

void loop() {
  // Reading temperature or humidity takes about 250 milliseconds!
  float h = dht.readHumidity();
  // You can get data in other scales: FARENHEIT or KELVIN
  float t = dht.readTemp(CELCIUS);

  // check if data is valid
  if (isnan(t) || isnan(h)) {
    Serial.println("Fail while reading..");
  } else {
  Serial.print("Temp: "); 
  Serial.print(t);
  // If you've changed the scale, write another letter here! (F or K instead C)
  Serial.print(" *C\t");
  Serial.print("Hmdt: "); 
  Serial.print(h);
  Serial.println(" %");
 }
 delay(500);
}
