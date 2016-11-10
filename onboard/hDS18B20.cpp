#include "hDS18B20.hpp"

void hDS18B20::start(){
	this->begin();
}

void hDS18B20::leTemperatura(){
	this->requestTemperatures();
	Temperatura = this->getTempCByIndex(0);
}

float hDS18B20::getTemperatura(){
	return Temperatura;
}

