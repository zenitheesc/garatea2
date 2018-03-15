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
#include "isFalling.h"
#include <Wire.h>


// Pin Define
#define DHTPIN 2 // Valor a ser corrigido
#define BUZZPIN 4 // Valor a ser corrigido
#define LMSPIN

#define DHTTYPE DHT22

#define ExposureModeAltitude 20000.0
#define CloseWindowAltitude 25000.0
#define RescueModeAltitude 2000.0
#define MaxTimeCloseWindow 7200000

class StateMach {
private:
	// Create Objects
	int contador;
	hDHT _dht;
	BUZZ _buzzer;
	hServo _myServo;
	UVX _uvx;	
	hGPS _gps1;
	hGPS _gps2;
	hComm _hcomm;
  	telemetria_controller TC;
  	NumericDiff ND;
  	isFalling IsF;
  	char SD1[50];
  	char SD2[50];
  	char SD3[50];
  	char SD4[50];
  	char SD5[50];
  	char SDaux[50];
	// Flags de modos de operacao
	bool _climbingMode = true;
	bool _exposureMode = false;
	bool _fallingMode = false;
	bool _rescueMode = false;
	

public:
	StateMach(): _dht(DHTPIN, DHTTYPE), _buzzer(BUZZPIN), 
	_myServo(), _uvx(),	 _gps1(), _gps2(), _hcomm(), TC(), ND(1.0), IsF() {};

	void ClimbingMode();
	void ExposureMode();
	void FallingMode();
	void RescueMode();
	void Main_State();
	void START_ALL();
  	void READ_ALL();
  	void SERIAL_PRINT_ALL();
  	void SAVE_ALL();
  	void TELEMETRIA();
  	void zera_tlast();
};

#endif
