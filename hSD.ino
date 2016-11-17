#include "hSD.h"

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  hSD _SD(4);  
  _SD.Write("vamo ae"); 
}

void loop() {
  // put your main code here, to run repeatedly:
  
}
