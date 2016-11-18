//
//  BUZZ.cpp
//  testec ARDUINO
//
//  Created by Danilo Oliveira on 11/10/16.
//  Copyright © 2016 Danilo Oliveira. All rights reserved.
//

#include "BUZZ.h"

BUZZ::BUZZ(int buzzPin){
    pinMode(buzzPin, OUTPUT);
    this->buzzPin = buzzPin;
}

BUZZ::~BUZZ(){
    
}

void BUZZ::beeper(int n){
    Serial.println(F("Estou no beeper"));
	for (int i = 0; i <= n; i++) {
        digitalWrite(this->buzzPin, HIGH);
        delay(0.5);
        digitalWrite(this->buzzPin, LOW);
        delay(0.5);
        
    }
}

void BUZZ::beep(){
    
    buzzPin = 2;
    digitalWrite(buzzPin, HIGH);

    delay(200);
    digitalWrite(buzzPin, LOW);
    delay(200);
    digitalWrite(buzzPin, HIGH);
    delay(200);
    digitalWrite(buzzPin, LOW);
    delay(200);
    digitalWrite(buzzPin, HIGH);
    delay(400);
    digitalWrite(buzzPin, LOW); // Finish beep with low state.
    Serial.println(F("Estou no beep"));
}

int BUZZ::getBuzzPin(){
    return buzzPin;
}
