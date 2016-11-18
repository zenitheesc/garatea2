#include "hGPS.h"

void hGPS::read_GPS(){
	this->begin(9600);
	sendCommand(PMTK_SET_NMEA_OUTPUT_RMCGGA);
	sendCommand(PMTK_SET_NMEA_UPDATE_1HZ);
	//seInterrupt(true);
}

void hGPS::hparse(){
	Serial.print(F("\nTime: "));
    Serial.print(hour, DEC); Serial.print(':');
    Serial.print(minute, DEC); Serial.print(':');
    Serial.print(seconds, DEC); Serial.print('.');
    Serial.println(milliseconds);
    Serial.print(F("Date: "));
    Serial.print(day, DEC); Serial.print('/');
    Serial.print(month, DEC); Serial.print(F("/20"));
    Serial.println(year, DEC);
    Serial.print(F("Fix: ")); Serial.print((int)fix);
    Serial.print(F(" quality: ")); Serial.println((int)fixquality); 
    if (fix) {
      Serial.print(F("Location: "));
      Serial.print(latitude, 4); Serial.print(lat);
      Serial.print(F(", ")); 
      Serial.print(longitude, 4); Serial.println(lon);
      Serial.print(F("Location (in degrees, works with Google Maps): "));
      Serial.print(latitudeDegrees, 4);
      Serial.print(F(", ")); 
      Serial.println(longitudeDegrees, 4);
      
      Serial.print(F("Speed (knots): ")); Serial.println(speed);
      Serial.print(F("Angle: ")); Serial.println(angle);
      Serial.print(F("Altitude: ")); Serial.println(altitude);
      Serial.print(F("Satellites: ")); Serial.println((int)satellites);
    }
}

float hGPS::get_latitude(){
	return latitudeDegrees;
}
float hGPS::get_longitude(){
	return longitudeDegrees;
}
float hGPS::get_speed(){
	speed = speed * 0.51444; // Conversao de knots para m/s
	return speed;
}
float hGPS::get_altitude(){
	return altitude;
}

