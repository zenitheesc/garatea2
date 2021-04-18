#include "hComm.h"

hComm::hComm(){
	Wire.begin(); // join i2c bus (address optional for master)
}

void hComm::send_Data(int i){
	Wire.beginTransmission(8);
	// Code goes here
	Wire.endTransmission();
}

void request_Data(){
	Wire.requestFrom(8, 30); // 30 Bytes, valor a corrigir

	while (Wire.available()) { // slave may send less than requested
    	char c = Wire.read(); // receive a byte as character
    	//Serial.print(c);         // print the character
  }
}