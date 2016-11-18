#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define precisionn 1000000.0

class telemetria_controller {
    private:
        char string_telemetria[64];
        void computeData(char* s, char* newData);
        void number_to_string(char* s, double n);
    public:
        telemetria_controller();
        void saveData(double data);
        void cleanStringTel();
        char* getStringTel();
    
};
