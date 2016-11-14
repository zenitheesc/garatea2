#ifndef hServo_h
#define hServo_h

#include <Arduino.h>
#include "Servo.h"

#define SERVOMIN 0
#define SERVOMAX 180 
#define SERVODELAY 0.05

class hServo : public Servo {
private:
	Servo myservo;

public:
	hServo(int pin);
	//~SERVO();
	void OpenWindow();
	void CloseWindow();	
};


#endif