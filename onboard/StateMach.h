#include <ArduinoStream.h>
#include <bufstream.h>
#include <ios.h>
#include <iostream.h>
#include <istream.h>
#include <MinimumSerial.h>
#include <ostream.h>
#include <Sd2Card.h>
#include <SdBaseFile.h>
#include <SdFat.h>
#include <SdFatConfig.h>
#include <SdFatmainpage.h>
#include <SdFatStructs.h>
#include <SdFatUtil.h>
#include <SdFile.h>
#include <SdInfo.h>
#include <SdStream.h>
#include <SdVolume.h>

#ifndef StateMach_h
#define StateMach_h

#include <Arduino.h>
#include "hDHT.h"
#include "BUZZ.h"
#include "hServo.h"
#include "hGPS.h"
#include "UVX.h"
#include "hDS18B20.h"
#include "hMS5611.h"
#include "hLSM303.h"
#include "hComm.h"
#include "telemetria_controller.h"
#include "NumericDiff.h"


// Pin Define
#define DHTPIN 10 // Valor a ser corrigido
#define BUZZPIN 11 // Valor a ser corrigido
#define UVA_pin 4 // Valor a ser corrigido
#define UVB_pin 5 // Valor a ser corrigido
#define UVC_pin 6 // Valor a ser corrigido
#define SD_PIN 4

#define DHTTYPE DHT22

class StateMach{
private:
	// Create Objects
	hDHT _dht;
	BUZZ _buzzer;
	hServo _myServo;
	UVX _uvx;	
	hGPS _gps;
	hMS5611 _hms5611;
	hDS18B20 _hds18b20;
	hLSM303 _hlsm303;
	hComm _hcomm;
 	SdFat sd;
  	SdFile myFile;
  	telemetria_controller TC;
  	NumericDiff ND;

	// Flags de modos de operacao
	bool _climbingMode = false;
	bool _exposureMode = false;
	bool _fallingMode = false;
	bool _rescueMode = false;

public:
	StateMach(): _dht(DHTPIN, DHTTYPE), _buzzer(BUZZPIN), 
	_myServo(), _uvx(UVA_pin, UVB_pin, UVC_pin),
	 _gps(), _hms5611() , _hds18b20(), _hlsm303(), _hcomm(), ND(1.0) {};

	void ClimbingMode();
	void ExposureMode();
	void FallingMode();
	void RescueMode();
	void Main_State();
  	void READ_ALL();
  	void SERIAL_PRINT_ALL();
};

#endif
