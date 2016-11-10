//
//  BUZZ.cpp
//  testec ARDUINO
//
//  Created by Danilo Oliveira on 11/10/16.
//  Copyright © 2016 Danilo Oliveira. All rights reserved.
//

#include "BUZZ.hpp"

BUZZ::BUZZ(int buzzPin){
    //pinMode(buzzPin, OUTPUT);
    this->buzzPin = buzzPin;
}

BUZZ::~BUZZ(){
    
}

void BUZZ::beeper(int n){
	for (int i = 0; i < n; i++) {
        digitalWrite(this->buzzPin, HIGH);
        delay(0.5);
        digitalWrite(this->buzzPin, LOW);
        delay(0.5);
        
    }
}

void BUZZ::beep(void){
    digitalWrite(this->buzzPin, HIGH);
    delay(0.5);
    digitalWrite(this->buzzPin, LOW);
    delay(0.5);
    digitalWrite(this->buzzPin, HIGH);
    delay(0.5);
    digitalWrite(this->buzzPin, LOW);
    delay(0.5);
    digitalWrite(this->buzzPin, HIGH);
    delay(2);
    digitalWrite(this->buzzPin, LOW); // Finish beep with low state.
}

int BUZZ::getBuzzPin(){
    return buzzPin;
}
