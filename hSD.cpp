#include "hSD.h"

hSD::hSD(int pin){
	if(SD.begin(pin))
		Serial.println("SD inicializado.");
}


void hSD::Write(String s){
  myFile = SD.open("gps.txt", FILE_WRITE);
	Serial.println(s);
	myFile.print(s);
  myFile.print("; ");
  myFile.close();
}
