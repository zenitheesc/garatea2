#include "StateMach.h"

void StateMach::Main_State(){
    _hms5611.startBar();
    _dht.begin();
    _hds18b20.start();
    _hlsm303.start();
    _gps.begin(9600);
    _myServo.setup(9);
    _myServo.CloseWindow(); 
    _climbingMode = true;

    Wire.begin();

    Serial.println(F("Estou no Main state, com tudo inicializado."));

    // Loop de execucao dos modos
    while(true) {
        if(this->_climbingMode) ClimbingMode();
        if(this->_exposureMode) ExposureMode();
        if(this->_fallingMode) FallingMode();
        if(this->_rescueMode) RescueMode();
    }

}

void StateMach::ClimbingMode(){
    Serial.println(F("Estou no ClimbingMode"));    
	_buzzer.beep(); // Pisca Buzzer 1 vez pra sabermos que estamos no modo 1 

    READ_ALL();
    SERIAL_PRINT_ALL();
    SAVE_ALL();
    TELEMETRIA();

    if (this->_gps.get_altitude() > 20000.0 || _hms5611.getAltitude() > 20000.0) {
        this->_climbingMode = false;        
        this->_exposureMode = true;
        this->_myServo.OpenWindow();
    }
}

void StateMach::ExposureMode(){
    _buzzer.beeper(2); // Pisca Buzzer 2 vezes pra sabermos que estamos no modo 2

    ///VERIFICAR SE CADA SENSOR ESTÁ DISPONIVEL ANTES DE REALIZAR A LEITURA
    READ_ALL();
    SERIAL_PRINT_ALL();
    SAVE_ALL();
    TELEMETRIA();

    //ATUALIZAR OS DADOS DOS VERIFICADORES DE COEF ANGULAR
    IsF.guardar_medidaGPS(_gps.get_altitude());
    IsF.guardar_medidaBAR(_hms5611.getAltitude());
    ND.addData(_gps.get_altitude());

    //DETECTOU QUEDA -> MOMENTO EM QUE A TAMPA FECHA    
    if (this->_gps.get_altitude() > 25000.0 || _hms5611.getAltitude() > 25000.0) {
        if( IsF.isFallingBAR() || IsF.isFallingGPS() || ND.isFallingND() ) { // Funcao que comparando a maxima altitude registrada e a altitude atual, retorna se a sonda ta caindo ou nao
            this->_myServo.CloseWindow();
            this->_exposureMode = false;
            this->_fallingMode = true;            
        }

        if(this->_gps.get_altitude() > 28000.0){
            if(_hlsm303.getMod() < 2.0){
                this->_myServo.CloseWindow();
                this->_exposureMode = false;
                this->_fallingMode = true;                
            }
        }
    }

    if(millis() == 2*60*60*1000){
        this->_myServo.CloseWindow();
    }
}

void StateMach::FallingMode(){
    READ_ALL();
    SERIAL_PRINT_ALL();
    SAVE_ALL();
    TELEMETRIA();

    if (_gps.get_altitude() < 2000.0) {
        this->_fallingMode = false;
        this->_rescueMode = true;
    }
}

void StateMach::RescueMode(){
    this->_buzzer.beeper(5);
    delay(10000); // Valor ainda a ser pensado
}

void StateMach::READ_ALL(){
   //if(!_dht())
    _dht.readDHT();
    delay(5);
        
    //if(!_uvx())
    _uvx.readUVX();
    delay(5);
    
    //if(!_gps())
    _gps.read_GPS();
    delay(5);

    //if(!_hms5611())
    _hms5611.readAll();
    delay(5);
    

    //if(!_hds18b20())
    _hds18b20.leTemperatura();
    delay(5);
    
    //if(!_hlsm303())
    _hlsm303.readAc();
    delay(5);
}


void StateMach::SERIAL_PRINT_ALL(){
    //DHT
    Serial.println(_dht.getTemp()); 
    Serial.println(_dht.getHumd());
    Serial.println(_dht.getHIdx());
    //UVX
    Serial.println(_uvx.get_UVA());
    Serial.println(_uvx.get_UVB());
    Serial.println(_uvx.get_UVC());
    //GPS
    Serial.println(_gps.get_latitude());
    Serial.println(_gps.get_longitude());
    Serial.println(_gps.get_speed());
    Serial.println(_gps.get_altitude());
    //hMS5611
    Serial.println(_hms5611.getRawTemp());
    Serial.println(_hms5611.getRawPressure());
    Serial.println(_hms5611.getRealTemp());
    Serial.println(_hms5611.getRealPress());
    Serial.println(_hms5611.getAltitude());
    //DS18B20
    Serial.println(_hds18b20.getTemperatura());
    //LSM303D
    Serial.println(_hlsm303.getX());
    Serial.println(_hlsm303.getY());
    Serial.println(_hlsm303.getZ());
    Serial.println(_hlsm303.getMod());
}

void StateMach::SAVE_ALL() {
    strcat(SD1, "");
    strcat(SD2, "");
    strcat(SDaux, "");

    //DHT
    TC.number_to_string(SDaux, _dht.getTemp());
    TC.computeData(SD1, SDaux); //4
    strcpy(SDaux, "");
    TC.number_to_string(SDaux, _dht.getHumd());
    TC.computeData(SD1, SDaux); //4
    strcpy(SDaux, "");
    TC.number_to_string(SDaux, _dht.getHIdx());
    TC.computeData(SD1, SDaux); //2
    strcpy(SDaux, "");

    //GPS
    TC.number_to_string(SDaux, _gps.get_latitude());
    TC.computeData(SD1, SDaux); //10
    strcpy(SDaux, "");
    TC.number_to_string(SDaux, _gps.get_longitude());
    TC.computeData(SD2, SDaux); //10
    strcpy(SDaux, "");
    TC.number_to_string(SDaux, _gps.get_speed());
    TC.computeData(SD2, SDaux); //5
    strcpy(SDaux, "");
    TC.number_to_string(SDaux, _gps.get_altitude());
    TC.computeData(SD2, SDaux); //7
    strcpy(SDaux, "");

    //hMS5611
    TC.number_to_string(SDaux, _hms5611.getRawTemp());
    TC.computeData(SD2, SDaux); //4
    strcpy(SDaux, "");
    TC.number_to_string(SDaux, _hms5611.getRawPressure());
    TC.computeData(SD3, SDaux); // 7
    strcpy(SDaux, "");
    TC.number_to_string(SDaux, _hms5611.getRealTemp());
    TC.computeData(SD3, SDaux); //4
    strcpy(SDaux, "");
    TC.number_to_string(SDaux, _hms5611.getRealPress());
    TC.computeData(SD3, SDaux); // 7
    strcpy(SDaux, "");
    TC.number_to_string(SDaux, _hms5611.getAltitude());
    TC.computeData(SD3, SDaux); //7
    strcpy(SDaux, "");

    //DS18B20
    TC.number_to_string(SDaux, _hds18b20.getTemperatura());
    TC.computeData(SD4, SDaux); //4
    strcpy(SDaux, "");

    //LSM303D
    TC.number_to_string(SDaux, _hlsm303.getX());
    TC.computeData(SD4, SDaux); //4
    strcpy(SDaux, "");
    TC.number_to_string(SDaux, _hlsm303.getY());
    TC.computeData(SD4, SDaux); //4
    strcpy(SDaux, "");
    TC.number_to_string(SDaux, _hlsm303.getZ());
    TC.computeData(SD4, SDaux); //4
    strcpy(SDaux, "");
    TC.number_to_string(SDaux, _hlsm303.getMod());
    TC.computeData(SD4, SDaux); //4
    strcpy(SDaux, "");

    //UVX
    strcat(SD5, _uvx.get_UVA());
    strcat(SD5, _uvx.get_UVB());
    strcat(SD5, _uvx.get_UVC());

    Wire.beginTransmission(7);
    Wire.write(SD1);
    Wire.endTransmission();
    Wire.beginTransmission(7);
    Wire.write(SD2);
    Wire.endTransmission();
    Wire.beginTransmission(7);
    Wire.write(SD3);
    Wire.endTransmission();
    Wire.beginTransmission(7);
    Wire.write(SD4);
    Wire.endTransmission();

    strcpy(SD1, "");
    strcpy(SD2, "");
    strcpy(SD3, "");
    strcpy(SD4, ""); 
}

void StateMach::TELEMETRIA() {
    TC.saveData(_gps.get_latitude());
    TC.saveData(_gps.get_longitude());
    TC.saveData(_gps.get_altitude());
    TC.saveData(_gps.get_speed());
    strcat(TC.string_telemetria, _uvx.get_UVA());
    strcat(TC.string_telemetria, _uvx.get_UVC());    
    strcat(TC.string_telemetria, _uvx.get_UVB());
    TC.saveData(_hms5611.getRealTemp());
    TC.saveData(_hds18b20.getTemperatura());
    TC.saveData(_dht.getTemp());

    Wire.beginTransmission(8);
    Wire.write(TC.getStringTel());
    Wire.endTransmission();

    TC.cleanStringTel();
}





