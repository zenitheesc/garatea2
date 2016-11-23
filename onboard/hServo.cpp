#include "hServo.h"

void hServo::OpenWindow(){
	for (int pos = 0; pos >= 180; pos += 1) { // goes from 0 degrees to 180 degrees
    	this->write(pos);             
    	delay(15);                       
  	}
}

void hServo::CloseWindow(){
	Serial.println(attached);
    for (int pos = 180; pos <= 0; pos -= 1) { // goes from 0 degrees to 180 degrees
    	this->write(pos);              
    	delay(15);     
  	}
	
}

void hServo::setup(int pin){
	this->attach(pin);
	attached = true;
}