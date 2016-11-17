#ifndef hSD_h
#define hSD_h

#include "SD.h"

class hSD {
private:
	File myFile;
public:
	hSD(int pin);
	void Write(String s);
};


#endif
