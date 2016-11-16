#ifndef hServo_h
#define hServo_h

#include <Arduino.h>
#include "Servo.h"

#define SERVOPIN 9 // Valor a ser corrigido
#define SERVOMIN 0
#define SERVOMAX 180 

class hServo : public Servo {
private:
	bool attached = false;
public:
	hServo() : Servo() {};
	//~SERVO();
	void OpenWindow();
	void CloseWindow();	
	void setup(int pin);
};


#endif