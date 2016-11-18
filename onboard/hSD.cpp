#include "hSD.h"

hSD::hSD(){
	SD.begin();
}

void hSD::write_on_DHT(float f){
	arq.open("DHT.txt", O_RDWR | O_CREAT | O_AT_END);
	arq.print(f);
	arq.print("; ");
	arq.close();
}
/*

void hSD::write_on_UVX(float f){
	arquivo.open("UVX.txt", O_RDWR | O_CREAT | O_AT_END);
	arquivo.print(f);
	arquivo.print("; ");
	arquivo.close();
}

void write_on_GPS(float f){
	arquivo.open("GPS.txt", O_RDWR | O_CREAT | O_AT_END);
	arquivo.print(f);
	arquivo.print("; ");
	arquivo.close();
}

void write_on_MS5611(float f){
	arquivo.open("MS5611.txt", O_RDWR | O_CREAT | O_AT_END);
	arquivo.print(f);
	arquivo.print("; ");
	arquivo.close();
}

void write_on_DS18B20(float f){
	arquivo.open("DS18B20.txt", O_RDWR | O_CREAT | O_AT_END);
	arquivo.print(f);
	arquivo.print("; ");
	arquivo.close();
}

void write_on_LSM303D(double d){
	arquivo.open("LSM303D.txt", O_RDWR | O_CREAT | O_AT_END);
	arquivo.print(d);
	arquivo.print("; ");
	arquivo.close();
}


*/