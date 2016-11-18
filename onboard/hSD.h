#ifndef hSD_h
#define hSD_h

#include <SdFat.h>

class hSD {
private:
	SdFile myFile;
	SdFat SD;
public:
	hSD(int pin);
	void Write(String s);
	void Write_GPS(int altitude);
	void Close();
};


#endif
