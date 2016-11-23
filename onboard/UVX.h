#ifndef UVX_h
#define UVX_h

#include <Arduino.h>
#include <Wire.h>


class UVX{
private:
	char UVA[7], UVB[7], UVC[7];
public:
	UVX();
	void readUVX(void);
	char* get_UVA();
	char* get_UVB();
	char* get_UVC();
};


#endif