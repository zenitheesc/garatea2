#include "DallasTemperature.h"
#include "OneWire.h"

#define hDS18B20_PIN 8

class hDS18B20 : public DallasTemperature {
private:
	float Temperatura;
	OneWire o;
public:
	hDS18B20() : o(hDS18B20_PIN), DallasTemperature(&o) {};
	void start();
	void leTemperatura();
	float getTemperatura();
};