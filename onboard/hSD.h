#include <ArduinoStream.h>
#include <bufstream.h>
#include <ios.h>
#include <iostream.h>
#include <istream.h>
#include <MinimumSerial.h>
#include <ostream.h>
#include <Sd2Card.h>
#include <SdBaseFile.h>
#include <SdFat.h>
#include <SdFatConfig.h>
#include <SdFatmainpage.h>
#include <SdFatStructs.h>
#include <SdFatUtil.h>
#include <SdFile.h>
#include <SdInfo.h>
#include <SdStream.h>
#include <SdVolume.h>

class hSD {
private:
	SdFat SD;
  	SdFile arq;
public:
	hSD();
	void write_on_DHT(float f);
	void write_on_UVX(float f);
	void write_on_GPS(float f);
	void write_on_MS5611(float f);
	void write_on_DS18B20(float f);
	void write_on_LSM303D(double d);
};
