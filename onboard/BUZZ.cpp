#include "BUZZ.h"

BUZZ::BUZZ(int buzzPin){
	pinMode(buzzPin, OUTPUT);
	this->buzzPin = buzzPin;
}

BUZZ::~BUZZ(){

}

void BUZZ::beep(void){
	digitalWrite(this->buzzPin, BUZZ.ON);
}

int BUZZ::getBuzzPin(){
	return buzzPin;
}