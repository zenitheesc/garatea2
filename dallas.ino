#include "hDS18B20.hpp"
#include "OneWire.h"

#define ONE_WIRE_BUS 2

OneWire oneWire(ONE_WIRE_BUS);

//COnfiguração do ds28b20
hDS18B20 sensor(&oneWire);

//Setup do Arduino
void setup() {
	Serial.begin(9600);
    sensor.start();
}

void loop() {
	sensor.leTemperatura();
	Serial.print(sensor.getTemperatura());
	Serial.print("\n");
	delay(1000);
}
