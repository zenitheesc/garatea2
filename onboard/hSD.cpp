#include "hSD.h"

hSD::hSD(int pin){
	if(SD.begin(pin))
		Serial.println("SD inicializado.");
	myFile = SD.open("gps.txt", FILE_WRITE);
}


void hSD::Write(String s){  	
	Serial.println(s);
	myFile.print(s);
  	myFile.print("; ");
 
}

void hSD::Write_GPS(int altitude){
	myFile.print(altitude);
	myFile.close();
}
