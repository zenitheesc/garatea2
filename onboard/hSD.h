#ifndef hSD_h
#define hSD_h

#include "SD.h"

class hSD {
private:
	File myFile;
public:
	hSD(int pin);
	void Write(String s);
	void Write_GPS(int altitude);
	void Close();
};


#endif
