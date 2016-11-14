#include "hDHT.h"
#define DHTTYPE DHT22



void hDHT::readDHT(void)
{
    boolean err = this->read();
    if (!err) {
        Temp = this->readTemperature();
        Humd = this->readHumidity();
        HIdx = this->computeHeatIndex(Temp, Humd, false);
    }
}

float hDHT::getTemp(){
    return Temp;
}

float hDHT::getHumd(){
    return Humd;
}

float hDHT::getHIdx(){
    return HIdx;
}
