#include "hSD.h"

hSD::hSD(int pin){
	if(SD.begin(pin, SPI_HALF_SPEED)) SD.initErrorHalt();		
	myFile.open("test.txt", O_RDWR | O_CREAT | O_AT_END);
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
