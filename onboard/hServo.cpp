#include "hServo.h"

hServo::hServo(int pin) : myservo(){	
	this->myservo.attach(pin);
}


void hServo::OpenWindow(){
	for(float p = SERVOMAX; p >= SERVOMIN; p--) {
        myservo.write(p/SERVOMAX);
        delay(SERVODELAY);
    }
}

void hServo::CloseWindow(){
	for(float p = SERVOMIN; p <= SERVOMAX; p++) {
        myservo.write(p/SERVOMAX);
        delay(SERVODELAY);
    }
}