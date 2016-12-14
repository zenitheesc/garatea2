#include "hMS5611.h"

void hMS5611::startBar(){
	this->begin(MS5611_HIGH_RES);
}
void hMS5611::readRawTemp(){
	RawTemp = this->readRawTemperature();
}
void hMS5611::readRawPressuro(){
	RawPressure = this->readRawPressure();
}
void hMS5611::readRealTemp(){
	RealTemp = this->readTemperature();
}
void hMS5611::readRealPress(){
	RealPress = this->readPressure();
}
void hMS5611::computeAltitude(){
	Altitude = this->setAltitude(this->getRealPress(), 101325.0);
}
void hMS5611::readAll(){
	//Serial.println("leitura ms5611");
	readRawTemp();
	//Serial.println("raw temp ok");
	readRawPressuro();
	//Serial.println("raw press ok");
	readRealTemp();
	//Serial.println("real temp ok");
	readRealPress();
	//Serial.println("real press ok");
	computeAltitude();
	//Serial.println("alt ok");
}
uint32_t hMS5611::getRawTemp(){
	return RawTemp;
}
uint32_t hMS5611::getRawPressure(){
	return RawPressure;
}
double hMS5611::getRealTemp(){
	return RealTemp;
}
double hMS5611::getRealPress(){
	return RealPress;
}
float hMS5611::getAltitude(){
	return Altitude;
}