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

void BUZZ::beep(void){
    //digitalWrite(this->buzzPin, BUZZ.ON);
}

int BUZZ::getBuzzPin(){
    return buzzPin;
}
