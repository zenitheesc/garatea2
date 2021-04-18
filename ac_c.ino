#include <Wire.h>
#include "hLSM303.hpp"

hLSM303 compass;

void setup()
{
  Serial.begin(9600);
  Wire.begin();
  compass.start();
}

void loop()
{
  compass.readAc();
  Serial.print("Ac: ");
  Serial.print(compass.getX());
  Serial.print(", ");
  Serial.print(compass.getY());
  Serial.print(", ");
  Serial.print(compass.getZ());
  Serial.print(", ");
  Serial.print(compass.getMod());
  Serial.print("\n");
  delay(1000);
}

