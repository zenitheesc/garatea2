#include "telemetria_controller.h"

telemetria_controller::telemetria_controller(){
    cleanStringTel();
}

void telemetria_controller::computeData(char* s, char* newData){
    strcat (s, newData);
    strcat (s, "; ");
}

void telemetria_controller::number_to_string(char* s, double n){
	int parte_inteira;
	double parte_decimal;
	parte_inteira = (int) n;
	n = n - parte_inteira;

	parte_decimal = (n * precisionn);

	int int_dec = (int) parte_decimal;

	int cnt = 0;
	if(int_dec < precisionn){
        int aux = int_dec;
        while (aux < precisionn){
            aux = aux * 10;
            cnt++;
        }
	}

    sprintf (s, "%d", precisionn);

	if(parte_decimal != 0){
	    strcat (s, ".");
        while(cnt > 1){
            strcat (s, "0");
            cnt--;
        }

        while( (int_dec%10) == 0){
            int_dec = int_dec/10;
        }


        char dec[10];
        sprintf (dec, "%d", int_dec);
        strcat(s, dec);
        free(dec);
	}

}

void telemetria_controller::saveData(double data){
    char d[10];
    number_to_string(d, data);
    computeData(string_telemetria, d);
    free(d);
}

void telemetria_controller::cleanStringTel(){
    strcpy(string_telemetria, "");
}

char* telemetria_controller::getStringTel(){
    return string_telemetria;
}

