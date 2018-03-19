#include "StateMach.h"

void StateMach::Main_State(){

    Serial.println(F("I'm in Main state.")); 

    // Start all sensors
    START_ALL();

    // Counter to send to telemetry
    contador = 0;

    // Mode execution loop
   while(true) {
        if(this->_climbingMode) ClimbingMode();
       /* if(this->_exposureMode) ExposureMode();
        if(this->_fallingMode) FallingMode();
        if(this->_rescueMode) RescueMode();*/
    }

}

void StateMach::ClimbingMode(){

    Serial.println("I'm in ClimbingMode");    
	//_buzzer.beep(); // Pisca Buzzer 1 vez pra sabermos que estamos no modo 1 
    Serial.println(contador);
    READ_ALL();
    Serial.println(F("All sensors read."));
    Serial.println(contador);
    SERIAL_PRINT_ALL();
    Serial.println(F("All sensors printed."));
    Serial.println(contador);
    SAVE_ALL();
    Serial.println(F("All data sent to SD card."));
    Serial.println(contador);

    // Telemetry condition
    if( contador > 9 ){
        TELEMETRIA();
        Serial.println(F("Enviou a string para a telemetria por i2c."));
        contador = 0;        
    } else {
        contador++;
        Serial.println(F("Sem tempo para telemetria."));
    }
    Serial.println(contador);

    // State machine check (to exposure mode)
    if (this->_gps1.altitude.meters() > ExposureModeAltitude || this->_gps2.altitude.meters() > ExposureModeAltitude/* BMP180 TBM */) {
        // Opens exp window
        this->_myServo.OpenWindow();

        this->_climbingMode = false;        
        this->_exposureMode = true;        
    }
}

void StateMach::ExposureMode(){

    // Exposure mode beep
    _buzzer.beeper(2);

    // Needs to check if sensors are available
    READ_ALL();
    SERIAL_PRINT_ALL();
    SAVE_ALL();
    TELEMETRIA();

    // Update angular coef data
    IsF.guardar_medidaGPS(_gps1.altitude.meters());
    IsF.guardar_medidaGPS(_gps2.altitude.meters());

    ND.addData(_gps1.altitude.meters());
    ND.addData(_gps2.altitude.meters());

    // Check if probe is falling
    if (this->_gps1.altitude.meters() > CloseWindowAltitude || this->_gps2.altitude.meters() > CloseWindowAltitude/* BMP180 TBM */) {
        if( IsF.isFallingBAR() || IsF.isFallingGPS() || ND.isFallingND() ) { 
            // Close exp window
            this->_myServo.CloseWindow();

            this->_exposureMode = false;
            this->_fallingMode = true;            
        }

        /* We no longer use an acelerometer (_hlsm303)
        if(this->_gps.altitude.meters() > 28000.0){
            if(_hlsm303.getMod() < 2.0){
                this->_myServo.CloseWindow();
                this->_exposureMode = false;
                this->_fallingMode = true;                
            }
        }*/
    }

    if(millis() == MaxTimeCloseWindow){
        this->_myServo.CloseWindow();
    }
}

void StateMach::FallingMode(){

    READ_ALL();
    SERIAL_PRINT_ALL();
    SAVE_ALL();
    TELEMETRIA();

    if (_gps1.altitude.meters() < RescueModeAltitude || _gps2.altitude.meters() < RescueModeAltitude) {
        this->_fallingMode = false;
        this->_rescueMode = true;
    }
}

void StateMach::RescueMode(){
    this->_buzzer.beeper(5);
    delay(10000);
}

void StateMach::START_ALL(){
    Serial.println("Inicializando sesores.");
    
    _ss.begin(GPSBaud);
    Serial.println(F("gps _ss ok"));

    _ubk.begin(GPSBaud);
    Serial.println(F("gps _ubk ok"));
    /*_gps.begin(9600);
    Serial.println(F("gps ok"));*/

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
    
    /*_gps.read_GPS();
    Serial.println(F("ok"));
    delay(5);*/

    // Needs 2 gps

    // Needs EEPROM
    
    // Needs BMP180
}


void StateMach::SERIAL_PRINT_ALL(){
    //DHT
    Serial.println(_dht.getTemp()); 
    Serial.println(_dht.getHumd());
    Serial.println(_dht.getHIdx());


    //GPS
   /* Serial.println(_gps.get_fix());
    Serial.println(_gps.get_latitude());
    Serial.println(_gps.get_longitude());
    Serial.println(_gps.get_speed());
    Serial.println(_gps.altitude.meters());*/
    
    
}

void StateMach::SAVE_ALL() {
    strcat(SD1, "");
    strcat(SDaux, "");
    

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
    TC.number_to_string(SDaux, _gps.altitude.meters());
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

}

void StateMach::TELEMETRIA() {
   /* TC.saveData(_gps.get_latitude());
    TC.saveData(_gps.get_longitude());
    TC.saveData(_gps.altitude.meters());
    TC.saveData(_gps.get_speed());*/

    /*TC.saveData(_gps1.isValid());
    TC.saveData(_gps2.isValid());*/

    Serial.println(TC.getStringTel());

    TC.transmission(TC.getStringTel());
    
    TC.cleanStringTel();

    /*TC.saveData(_uvx.get_UVA());
    TC.saveData(_uvx.get_UVC());    
    TC.saveData(_uvx.get_UVB());
    

    TC.transmission(TC.getStringTel());
    TC.cleanStringTel();*/
}
