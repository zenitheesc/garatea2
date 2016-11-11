#include "MS5611.h"

class hMS5611 : public MS5611{
private:
	uint32_t RawTemp;
    uint32_t RawPressure;

    double RealTemp;
	double RealPress;
	float Altitude;  
	   
public:
	hMS5611() : MS5611() {};

	void startBar();

	void readRawTemp();
	void readRawPressuro();
	void readRealTemp();
	void readRealPress();
	void computeAltitude();
	void readAll();

	uint32_t getRawTemp();
	uint32_t getRawPressure();
	double getRealTemp();
	double getRealPress();
	float getAltitude();  
};