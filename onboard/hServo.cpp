#include "hServo.h"

void hServo::OpenWindow(){
	for (int pos = 180; pos >= 0; pos -= 1) { // goes from 0 degrees to 180 degrees
    	// in steps of 1 degree
    	this->write(pos);              // tell servo to go to position in variable 'pos'
    	delay(15);                       // waits 15ms for the servo to reach the position
  	}
}

void hServo::CloseWindow(){
	Serial.println(F("estou na closeWindow"));
	if(!attached){		
		setup(SERVOPIN);
	}
	Serial.println(attached);
    for (int pos = 0; pos <= 180; pos += 1) { // goes from 0 degrees to 180 degrees
    	// in steps of 1 degree
    	this->write(pos);              // tell servo to go to position in variable 'pos'
    	delay(15);                       // waits 15ms for the servo to reach the position
  	}
	
}

void hServo::setup(int pin){
	this->attach(pin);
	attached = true;
}