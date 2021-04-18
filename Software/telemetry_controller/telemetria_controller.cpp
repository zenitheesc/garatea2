#include "telemetria_controller.h"

telemetria_controller::telemetria_controller(){
    cleanStringTel();
}

void telemetria_controller::computeData(char* s, char* newData){
    strcat (s, newData);
    strcat (s, ";");
}

void telemetria_controller::number_to_string(char* s, double n){
	n = n * 100;
    int resultado = (int) n;

    strcpy(s, "");

    sprintf(s, "%d", resultado);
}

void telemetria_controller::saveData(double data){
    strcpy(d, "\0");
    number_to_string(d, data);
    computeData(string_telemetria, d);
    free(d);
}

void telemetria_controller::cleanStringTel(){
    strcpy(string_telemetria, "$$zenith");
}

char* telemetria_controller::getStringTel(){
    return string_telemetria;
}

void telemetria_controller::transmission(char* s){
    Wire.beginTransmission(25);
    Wire.write(s);
    Wire.endTransmission();
}