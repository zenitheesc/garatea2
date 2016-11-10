#include "hGPS.hpp"

void hGPS::read_GPS(){
	this->begin(9600);
	sendCommand(PMTK_SET_NMEA_OUTPUT_RMCGGA);
	sendCommand(PMTK_SET_NMEA_UPDATE_1HZ);
	//seInterrupt(true);
}

void hGPS::hparse(){
	Serial.print("\nTime: ");
    Serial.print(hour, DEC); Serial.print(':');
    Serial.print(minute, DEC); Serial.print(':');
    Serial.print(seconds, DEC); Serial.print('.');
    Serial.println(milliseconds);
    Serial.print("Date: ");
    Serial.print(day, DEC); Serial.print('/');
    Serial.print(month, DEC); Serial.print("/20");
    Serial.println(year, DEC);
    Serial.print("Fix: "); Serial.print((int)fix);
    Serial.print(" quality: "); Serial.println((int)fixquality); 
    if (fix) {
      Serial.print("Location: ");
      Serial.print(latitude, 4); Serial.print(lat);
      Serial.print(", "); 
      Serial.print(longitude, 4); Serial.println(lon);
      Serial.print("Location (in degrees, works with Google Maps): ");
      Serial.print(latitudeDegrees, 4);
      Serial.print(", "); 
      Serial.println(longitudeDegrees, 4);
      
      Serial.print("Speed (knots): "); Serial.println(speed);
      Serial.print("Angle: "); Serial.println(angle);
      Serial.print("Altitude: "); Serial.println(altitude);
      Serial.print("Satellites: "); Serial.println((int)satellites);
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
uint8_t hGPS::get_hour(){
	return hour;
}
uint8_t hGPS::get_minute(){
	return minute;
}
uint8_t hGPS::get_second(){
	return seconds;
}