//#include <avr/wdt.h> // Biblioteca utilizada pelo watchdog timer.
#include "StateMach.h"

StateMach estados;

void setup(){
	
    Serial.begin(9600);     
    //wdt_enable(WDTO_4S); // Computador ira reiniciar se o timer nao for resetado em 4s
    pinMode(13, OUTPUT);
}

void loop(){
    	
    //wdt_reset(); // Funcao que reseta o timer
    estados.Main_State();
    delay(2000);
    
}
