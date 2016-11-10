#include "DHT.h"
#include "BUZZ.hpp"
#include "SERVO.h"

// Pin Define
#define DHTPIN 2
#define BUZZPIN 1 // VALOR A CORRIGIR
#define SERVOPIN 1 // VALOR A CORRIGIR

#define DHTTYPE DHT22

// Create Objects
DHT dht(DHTPIN, DHTTYPE);
BUZZ buzzer(BUZZPIN);
SERVO myServo(SERVOPIN);

void setup(){
 Serial.begin(9600); 
 dht.begin();
}

void loop(){
    delay(2000);
    float h = dht.readHumidity();
    float t = dht.readTemperature();
    float hic = dht.computeHeatIndex(t, h, false);

      Serial.print("\nHumidity: ");
      Serial.print(h);
      Serial.print("\nTemperature: ");
      Serial.print(t);
      Serial.print(" *C ");
      Serial.print("\nHeat index: ");
      Serial.print(hic);
      Serial.print(" *C ");
}

