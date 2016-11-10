#include "DallasTemperature.h"
#include "OneWire.h"

class hDS18B20 : public DallasTemperature {
private:
	float Temperatura;
	OneWire o;
public:
	hDS18B20() : o(1), DallasTemperature(&o) {};
	void start();
	void leTemperatura();
	float getTemperatura();
};