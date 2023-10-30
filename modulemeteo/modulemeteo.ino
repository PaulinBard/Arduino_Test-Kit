#include "Wire.h"


#include "DHT.h"
DHT dht(2, DHT11);

byte degre[8] = {
0b01100,0b10010,0b10010,0b01100,0b00000,0b00000,0b00000,0b00000
};

void setup() {
  Serial.begin(9600);  // ouvre le port série
 
}

void loop() {
  byte h = dht.readHumidity();
  byte t = dht.readTemperature();

  Serial.print("Temperature: ");
  Serial.println(t);
  Serial.print("Humidity: ");
  Serial.println(h);
  Serial.println("");


  delay(1000);  // attend 1 sec
}