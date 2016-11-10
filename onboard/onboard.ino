//#include <avr/wdt.h> // Biblioteca utilizada pelo watchdog timer.
//#include "StateMach.h"

//StateMach estados;

void setup(){
	//Serial.println("cusao");
    Serial.begin(9600); 
    //wdt_enable(WDTO_4S); // Computador ira reiniciar se o timer nao for resetado em 4s
     pinMode(13, OUTPUT);
}

void loop(){
  digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(1000);                       // wait for a second
  digitalWrite(LED_BUILTIN, LOW);    // turn the LED off by making the voltage LOW
  delay(1000); 
	Serial.println("CUSAO");
    //wdt_reset(); // Funcao que reseta o timer
    //estados.Main_State();
    delay(2000);
    
}

