#include "StateMach.h"

void StateMach::Main_State(){

    //_hms5611.startBar();
    //_dht.begin();
    //_hds18b20.start();
    //_hlsm303.start();
    _myServo.CloseWindow();
    Serial.println(_myServo.read());
    //_myServo.detach();  
    _climbingMode = true;
    Serial.println("Estou no Main state");

    // Loop de execucao dos modos
    while(true) {
        if(this->_climbingMode) ClimbingMode();
        if(this->_exposureMode) ExposureMode();
        if(this->_fallingMode) FallingMode();
        if(this->_rescueMode) RescueMode();
    }
}

void StateMach::ClimbingMode(){
    Serial.println("Estou no ClimbingMode");    
	_buzzer.beep(); // Pisca Buzzer 1 vez pra sabermos que estamos no modo 1 
    delay(5);
    _dht.readDHT();
    Serial.println(_dht.getTemp());
    Serial.println(_dht.getHumd());
    Serial.println(_dht.getHIdx());
    delay(5);
    _hms5611.readAll(); // OK funcionando
    Serial.println(_hms5611.getAltitude());
    Serial.println(_hms5611.getRealTemp());
    Serial.println(_hms5611.getRealPress());
    delay(5);
    _hds18b20.leTemperatura();
    Serial.println(_hds18b20.getTemperatura());    
    delay(5);
    _hlsm303.readAc();
    Serial.println(_hlsm303.getMod());
    delay(5);
    //this->_uvx.readUVX();
    delay(5);
    //this->_gps.read_GPS();
    delay(3000);
    //writeData(); // gravar dados.txt
    /*if (this->_gps.get_altitude() > 20000.0 || barAltitude > 20000.0) {
        this->_climbingMode = false;        
        this->_exposureMode = true;
        this->_myServo.OpenWindow();
    }*/


}

void StateMach::ExposureMode(){

    _buzzer.beeper(2); // Pisca Buzzer 2 vezes pra sabermos que estamos no modo 2
    
    delay(5);
    _dht.readDHT();
    delay(5);
    _hms5611.readAll();
    delay(0.05);
    _hlsm303.readAc();
    delay(5);
    _uvx.readUVX();
    delay(5);
    _hds18b20.leTemperatura();
    delay(5);
    _gps.read_GPS();
    delay(5);
    
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
    delay(5);
    this->_dht.readDHT();
    delay(5);
    _hms5611.readAll();
    delay(5);
    _hlsm303.readAc();
    delay(5);
    this->_uvx.readUVX();
    delay(5);
    _hds18b20.leTemperatura();
    delay(5);
    this->_gps.read_GPS();
    delay(5);

    /*if (hasLanded()) {
        this->_fallingMode = false;
        this->_rescueMode = true;
    }*/
}

void StateMach::RescueMode(){
    this->_buzzer.beeper(5);
    delay(10000); // Valor ainda a ser pensado
}
