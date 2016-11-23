#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <Wire.h>

#define precisionn 100.0

class telemetria_controller {
    public:
        char string_telemetria[64];
        void computeData(char* s, char* newData);
        void number_to_string(char* s, double n);
        telemetria_controller();
        void saveData(double data);
        void cleanStringTel();
        char* getStringTel();
        void transmission(char* s);
};
