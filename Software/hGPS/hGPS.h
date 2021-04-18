#ifndef hGPS_h
#define hGPS_h

#include "Adafruit_GPS.h"
#include <HardwareSerial.h>

#define GPS_TX 3
#define GPS_RX 2

class hGPS : public Adafruit_GPS {
private:	
	HardwareSerial serial = Serial;
	
public:
	hGPS(): Adafruit_GPS(&serial) {
	};
	void hparse();
	void read_GPS();
	float get_latitude();
	float get_longitude();
	float get_speed();
	float get_altitude();
	float get_fix();
};

#endif