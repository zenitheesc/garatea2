#include "StateMach.h"

void StateMach::Main_State(){
    Serial.println(F("Estou no Main state.")); 
    START_ALL();
    contador = 0;

    // Loop de execucao dos modos
   while(true) {
        if(this->_climbingMode) ClimbingMode();
       /* if(this->_exposureMode) ExposureMode();
        if(this->_fallingMode) FallingMode();
        if(this->_rescueMode) RescueMode();*/
    }

}

void StateMach::ClimbingMode(){
    Serial.println("Estou no ClimbingMode");    
	//_buzzer.beep(); // Pisca Buzzer 1 vez pra sabermos que estamos no modo 1 
    Serial.println(contador);
    READ_ALL();
    Serial.println(F("Leu todos os sensores."));
    Serial.println(contador);
    SERIAL_PRINT_ALL();
    Serial.println(F("Imprimiu todos os sensores."));
    Serial.println(contador);
    SAVE_ALL();
    Serial.println(F("Enviou todos por i2c para o SD."));
    Serial.println(contador);
    //CONDIÇÃO DA TELEMETRIA:
    if( contador > 9 ){
        TELEMETRIA();
        Serial.println(F("Enviou a string para a telemetria por i2c."));
        contador = 0;        
    } else {
        contador++;
        Serial.println(F("Sem tempo para telemetria."));
    }
    Serial.println(contador);
    /*if (this->_gps.get_altitude() > 20000.0 || _hms5611.getAltitude() > 20000.0) {
        this->_climbingMode = false;        
        this->_exposureMode = true;
        this->_myServo.OpenWindow();
    }*/
}
/*
void StateMach::ExposureMode(){
    //_buzzer.beeper(2); // Pisca Buzzer 2 vezes pra sabermos que estamos no modo 2

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
        if( IsF.isFallingBAR() || IsF.isFallingGPS() || ND.isFallingND() ) { 
        // Funcao que comparando a maxima altitude registrada e a altitude atual, retorna se a sonda ta caindo ou nao
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
    //this->_buzzer.beeper(5);
    delay(10000); // Valor ainda a ser pensado
}*/

void StateMach::START_ALL(){
    Serial.println("Inicializando sesores.");
    
    _hms5611.startBar();
    Serial.println(F("5611 ok"));
  
    _hds18b20.start();
    Serial.println(F("ds18b20 ok"));

    _hlsm303.start();
    Serial.println(F("ac ok"));

    _gps.begin(9600);
    Serial.println(F("gps ok"));

    _myServo.setup(5);
    Serial.println(F("servo ok"));

    _dht.begin();
    Serial.println(F("dht ok"));

    _climbingMode = true;
    Wire.begin();

    Serial.println("Sensores incializados.");
}

void StateMach::READ_ALL(){
    _dht.readDHT();
    Serial.println(F("ok"));
    delay(5);

    //_uvx.readUVX();
    //delay(5);
    
    /*_gps.read_GPS();
    Serial.println(F("ok"));
    delay(5);*/

    _hms5611.readAll();
    Serial.println(F("ok"));
    delay(5);
    

    _hds18b20.leTemperatura();
    Serial.println(F("ok"));
    delay(5);

    _hlsm303.readAc();
    Serial.println(F("ok"));
    delay(5);
}


void StateMach::SERIAL_PRINT_ALL(){
    //DHT
    Serial.println(_dht.getTemp()); 
    Serial.println(_dht.getHumd());
    Serial.println(_dht.getHIdx());

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

    //GPS
   /* Serial.println(_gps.get_fix());
    Serial.println(_gps.get_latitude());
    Serial.println(_gps.get_longitude());
    Serial.println(_gps.get_speed());
    Serial.println(_gps.get_altitude());*/


/*

    //UVX
    Serial.println(_uvx.get_UVA());
    Serial.println(_uvx.get_UVB());
    Serial.println(_uvx.get_UVC());
    */
    
    
}

void StateMach::SAVE_ALL() {
    strcat(SD1, "");
    strcat(SDaux, "");
    
     //DS18B20
    TC.number_to_string(SDaux, _hds18b20.getTemperatura());
    TC.computeData(SD1, SDaux); //4
    strcpy(SDaux, "");

    //LSM303D
    TC.number_to_string(SDaux, _hlsm303.getX());
    TC.computeData(SD1, SDaux); //4
    strcpy(SDaux, "");
    TC.number_to_string(SDaux, _hlsm303.getY());
    TC.computeData(SD1, SDaux); //4
    strcpy(SDaux, "");
    TC.number_to_string(SDaux, _hlsm303.getZ());
    TC.computeData(SD1, SDaux); //4
    strcpy(SDaux, "");
    TC.number_to_string(SDaux, _hlsm303.getMod());
    TC.computeData(SD1, SDaux); //4
    strcpy(SDaux, "");

    Wire.beginTransmission(15);
    Wire.write(SD1);
    Wire.endTransmission();
    Serial.println(SD1);
    strcpy(SD1, ""); 
    delay(500);

    /*//GPS
    TC.number_to_string(SDaux, _gps.get_latitude());
    TC.computeData(SD1, SDaux); //10
    strcpy(SDaux, "");
    TC.number_to_string(SDaux, _gps.get_longitude());
    TC.computeData(SD1, SDaux); //10
    strcpy(SDaux, "");
    TC.number_to_string(SDaux, _gps.get_speed());
    TC.computeData(SD1, SDaux); //5
    strcpy(SDaux, "");
    TC.number_to_string(SDaux, _gps.get_altitude());
    TC.computeData(SD1, SDaux); //7
    strcpy(SDaux, "");

    Wire.beginTransmission(15);
    Wire.write(SD1);
    Wire.endTransmission();
    strcpy(SD1, "");
    delay(1000);*/


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


    Wire.beginTransmission(15);
    Wire.write(SD1);
    Wire.endTransmission();
    Serial.println(SD1);
    strcpy(SD1, ""); 
    delay(500);

    //hMS5611      
    /*TC.number_to_string(SDaux, _hms5611.getRawTemp());
    TC.computeData(SD1, SDaux); //4
    strcpy(SDaux, "");
    Wire.write(SD1);
    Wire.endTransmission();
    delay(500);
    strcpy(SD1, ""); 
    TC.number_to_string(SDaux, _hms5611.getRawPressure());
    TC.computeData(SD1, SDaux); // 7
    strcpy(SDaux, "");*/

    TC.number_to_string(SDaux, _hms5611.getRealTemp());
    TC.computeData(SD1, SDaux); //4
    strcpy(SDaux, "");
    TC.number_to_string(SDaux, _hms5611.getRealPress());
    TC.computeData(SD1, SDaux); // 7
    strcpy(SDaux, "");
    TC.number_to_string(SDaux, _hms5611.getAltitude());
    TC.computeData(SD1, SDaux); //7
    strcpy(SDaux, "");

    Wire.beginTransmission(15);
    Wire.write(SD1);
    Wire.endTransmission();
    Serial.println(SD1);
    strcpy(SD1, "");
    delay(500);

    

/*
    //UVX
    strcat(SD1, _uvx.get_UVA());
    strcat(SD1, _uvx.get_UVB());
    strcat(SD1, _uvx.get_UVC());

    Wire.beginTransmission(7);
    Wire.write(SD1);
    Wire.endTransmission();
    Serial.println(SD1);
    strcpy(SD1, ""); 
    delay(1000);
    */
}

void StateMach::TELEMETRIA() {
   /* TC.saveData(_gps.get_latitude());
    TC.saveData(_gps.get_longitude());
    TC.saveData(_gps.get_altitude());
    TC.saveData(_gps.get_speed());*/

    TC.saveData(_hms5611.getRealTemp());
    TC.saveData(_hlsm303.getMod());
    TC.saveData(_gps.get_fix());

    Serial.println(TC.getStringTel());

    TC.transmission(TC.getStringTel());
    
    TC.cleanStringTel();

    /*TC.saveData(_uvx.get_UVA());
    TC.saveData(_uvx.get_UVC());    
    TC.saveData(_uvx.get_UVB());
    

    TC.transmission(TC.getStringTel());
    TC.cleanStringTel();*/
}
