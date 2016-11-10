#include "SERVO.h"

SERVO::SERVO(int pin) : myservo(){	
	this->myservo.attach(pin);
}


void SERVO::OpenWindow(){
	for(float p = SERVOMAX; p >= SERVOMIN; p--) {
        myservo.write(p/SERVOMAX);
        delay(SERVODELAY);
    }
}

void SERVO::CloseWindow(){
	for(float p = SERVOMIN; p <= SERVOMAX; p++) {
        myservo.write(p/SERVOMAX);
        delay(SERVODELAY);
    }
}