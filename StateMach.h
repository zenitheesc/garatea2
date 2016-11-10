#ifndef StateMach_h
#define StateMach_h

#include <Arduino.h>
#include "hDHT.hpp"
#include "BUZZ.hpp"
#include "SERVO.h"
#include "GPS.h"
#include "UVX.h"
//#include "TEMPEX.h"

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
	GPS _gps;
	//TEMPEX _tempex();


	// Flags de modos de operacao
	bool _climbingMode = false;
	bool _exposureMode = false;
	bool _fallingMode = false;
	bool _rescueMode = false;

public:
	StateMach(): _dht(DHTPIN, DHTTYPE), _buzzer(BUZZPIN), _myServo(SERVOPIN), _uvx(UVA_pin, UVB_pin, UVC_pin), _gps() {};

	void ClimbingMode();
	void ExposureMode();
	void FallingMode();
	void RescueMode();
	void Main_State();

};

#endif
