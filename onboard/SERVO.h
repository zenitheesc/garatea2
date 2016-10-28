#ifndef SERVO_h
#define SERVO_h

#include <Arduino.h>
#include <Servo.h>

#define SERVOMIN 0
#define SERVOMAX 180 
#define SERVODELAY 0.05

class SERVO{
private:
	Servo myservo;

public:
	SERVO(int pin);
	//~SERVO();
	void OpenWindow();
	void CloseWindow();	
};


#endif