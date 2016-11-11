#ifndef StateMach_h
#define StateMach_h

#include <Arduino.h>
#include "hDHT.hpp"
#include "BUZZ.hpp"
#include "SERVO.h"
#include "hGPS.hpp"
#include "UVX.h"
#include "hDS18B20.hpp"
#include "hMS5611.hpp"
//#include "OneWire.h"

// Pin Define
#define DHTPIN 1 // Valor a ser corrigido
#define BUZZPIN 2 // Valor a ser corrigido
#define SERVOPIN 3 // Valor a ser corrigido
#define UVA_pin 4 // Valor a ser corrigido
#define UVB_pin 5 // Valor a ser corrigido
#define UVC_pin 6 // Valor a ser corrigido

#define DHTTYPE DHT22

class StateMach{
private:
	// Create Objects
	hDHT _dht;
	BUZZ _buzzer;
	SERVO _myServo;
	UVX _uvx;	
	hDS18B20 _ds18b20;
	hGPS _gps;
	hMS5611 _hms5611;

	// Flags de modos de operacao
	bool _climbingMode = false;
	bool _exposureMode = false;
	bool _fallingMode = false;
	bool _rescueMode = false;

public:
	StateMach(): _dht(DHTPIN, DHTTYPE), _buzzer(BUZZPIN), 
	_myServo(SERVOPIN), _uvx(UVA_pin, UVB_pin, UVC_pin),
	 _gps(),/* o(1),*/ _ds18b20(), _hms5611() {};

	void ClimbingMode();
	void ExposureMode();
	void FallingMode();
	void RescueMode();
	void Main_State();

};

#endif
