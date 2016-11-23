#include "UVX.h"

UVX::UVX(){
	strcpy(UVA, "");
    strcpy(UVB, "");
    strcpy(UVC, "");
}

char* UVX::get_UVA(){
	return UVA;
}
char* UVX::get_UVB(){
	return UVB;
}
char* UVX::get_UVC(){
	return UVC;
}

void UVX::readUVX(void){
	Wire.requestFrom(1, 21);
    delay(500);

    char datastring[22];
    int aux = 0;

    while(Wire.available()){
        datastring[aux] = Wire.read();
        aux = aux + 1;
    }

    for(int i = 0; i < 7; i++){
        UVA[i] = datastring[i];
        UVB[i] = datastring[i+6];
        UVC[i] = datastring[i+13];
    }
}