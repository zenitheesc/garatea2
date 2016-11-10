#include "DallasTemperature.h"

class hDS18B20 : public DallasTemperature {
private:
	float Temperatura;
public:
	hDS18B20(OneWire* o) : DallasTemperature(o) {};
	void start();
	void leTemperatura();
	float getTemperatura();
};