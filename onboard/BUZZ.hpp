//
//  BUZZ.hpp
//  testec ARDUINO
//
//  Created by Danilo Oliveira on 11/10/16.
//  Copyright © 2016 Danilo Oliveira. All rights reserved.
//

#ifndef BUZZ_hpp
#define BUZZ_hpp

#include <stdio.h>

class BUZZ
{
public:
    BUZZ(int buzzPin);
    ~BUZZ();
    
    enum{
        ON,
        OFF
    };
    
    void beep(void); // Toque intermitente a cada segundo
    void beeper(int n); //
    int getBuzzPin();
private:
    int buzzPin = 0; // Information for some function who needs this
};


#endif /* BUZZ_hpp */
