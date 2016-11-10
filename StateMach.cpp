#include "StateMach.h"

void StateMach::Main_State(){

    this->_myServo.CloseWindow();
//    this->_dht.baud(9600);
    this->_climbingMode = true;

    // Loop de execucao dos modos
    while(true) {
        if(this->_climbingMode) ClimbingMode();
        if(this->_exposureMode) ExposureMode();
        if(this->_fallingMode) FallingMode();
        if(this->_rescueMode) RescueMode();
    }
}

void StateMach::ClimbingMode(){
	this->_buzzer.beeper(1); // Pisca Buzzer 1 vez pra sabermos que estamos no modo 1 

    delay(0.05);
    this->_dht.readDHT();
    delay(0.05);
    //readBarometer();
    //delay(0.05);
    //readCompass();
    delay(0.05);
    this->_uvx.readUVX();
    delay(0.05);
    //this->_tempex.readTEMPEX();
    delay(0.05);
    this->_gps.readGPS();
    delay(0.05);
    //writeData(); // gravar dados.txt
    if (this->_gps.get_altitude() > 20000.0 /*|| barAltitude > 20000.0*/) {
        this->_climbingMode = false;        
        this->_exposureMode = true;
        this->_myServo.OpenWindow();
    }
}

void StateMach::ExposureMode(){

    this->_buzzer.beeper(2); // Pisca Buzzer 2 vezes pra sabermos que estamos no modo 2
    
    delay(0.05);
    this->_dht.readDHT();
    delay(0.05);
    //readBarometer();
    //delay(0.05);
    //readCompass();
    delay(0.05);
    this->_uvx.readUVX();
    delay(0.05);
    //this->_tempex.readTEMPEX();
    delay(0.05);
    this->_gps.readGPS();
    delay(0.05);
    
    if (this->_gps.get_altitude() > 25000.0 /*|| barAltitude > 25000.0*/) {
        //if(isFallingBAR() || isFallingGPS()) { // Funcao que comparando a maxima altitude registrada e a altitude atual, retorna se a sonda ta caindo ou nao
            this->_exposureMode = false;
            this->_fallingMode = true;
            this->_myServo.CloseWindow();
        //}
    }
}

void StateMach::FallingMode()
{
    this->_buzzer.beeper(3); // Pisca Buzzer 3 vezes pra sabermos que estamos no modo 3

    delay(0.05);
    this->_dht.readDHT();
    delay(0.05);
    //readBarometer();
    //delay(0.05);
    //readCompass();
    delay(0.05);
    this->_uvx.readUVX();
    delay(0.05);
    //this->_tempex.readTEMPEX();
    delay(0.05);
    this->_gps.readGPS();
    delay(0.05);

    /*if (hasLanded()) {
        this->_fallingMode = false;
        this->_rescueMode = true;
    }*/
}

void StateMach::RescueMode(){
    this->_buzzer.beeper(5);
    delay(10000); // Valor ainda a ser pensado
}
