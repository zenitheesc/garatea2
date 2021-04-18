#ifndef hCOmm_h
#define hComm_h

#include <Wire.h>

class hComm{

public:
	hComm();
	void send_Data(int i);
	void request_Data();
};

#endif