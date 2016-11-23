#include "isFalling.h"
#define nro_de_medidas 6 //MARGEM DE SEGURANÇA

//  COEF_ANGULAR CALCULA O COEFICIENTE ANGULAR
//  PARA A MELHOR RETA QUE DESCREVE O COMPORTAMENTO
//  DAS ÚLTIMAS ALTURAS (MARGEM DE SEGURANÇA)
double isFalling::coef_angularGPS(){
    if(ult_auxGPS < nro_de_medidas-1) return 0;

    double media_atual = 0;
    for(int i = 0; i < nro_de_medidas; i++){
        if(ultimas_medidasGPS[i] != 0)
            media_atual = media_atual + ultimas_medidasGPS[i];
    }
    media_atual = media_atual / nro_de_medidas ;
    //printf("media: = %.2f\n", media_atual);

    double desvio, coef, soma_n = 0, soma_d = 0;
    for(int i = 0; i < nro_de_medidas; i++){
        desvio = (ultimas_medidasGPS[i] - media_atual);
       // printf("desvio: = %.2f\n", desvio);
        soma_n = soma_n + (desvio * (i+1));
       // printf("soma n: = %.2f\n", soma_n);
        soma_d = soma_d +(desvio*desvio);
       // printf("soma d: = %.2f\n", soma_d);
    }

    coef = (soma_n / soma_d);
    coef = pow(coef, -1);

    return coef;
}

double isFalling::coef_angularBAR(){
    if(ult_auxBAR < nro_de_medidas-1) return 0;

    double media_atual = 0;
    for(int i = 0; i < nro_de_medidas; i++){
        if(ultimas_medidasBAR[i] != 0)
            media_atual = media_atual + ultimas_medidasBAR[i];
    }
    media_atual = media_atual / nro_de_medidas ;
    //printf("media: = %.2f\n", media_atual);

    double desvio, coef, soma_n = 0, soma_d = 0;
    for(int i = 0; i < nro_de_medidas; i++){
        desvio = (ultimas_medidasBAR[i] - media_atual);
       // printf("desvio: = %.2f\n", desvio);
        soma_n = soma_n + (desvio * (i+1));
       // printf("soma n: = %.2f\n", soma_n);
        soma_d = soma_d +(desvio*desvio);
       // printf("soma d: = %.2f\n", soma_d);
    }

    coef = (soma_n / soma_d);
    coef = pow(coef, -1);

    return coef;
}

//  GUARDAR_MEDIDA INSERE NO VETOR DAS ULTIMAS MEDIDAS
//  A ULTIMA MEDIDA RECEBIDA

void isFalling::guardar_medidaGPS(float f){
    if(ult_auxGPS == nro_de_medidas-1){
        for(int m = 0; m < nro_de_medidas-1; m++)
            ultimas_medidasGPS[m] = ultimas_medidasGPS[m+1];
    }
    else
        ult_auxGPS++;

    ultimas_medidasGPS[ult_auxGPS] = f;
    guardar_coefGPS(coef_angularGPS());

    //IMPRIMIR VETOR DE ALTURAS
    //printf("medida armazenada. [alt = %.2f]\n", ultimas_medidasGPS[ult_auxGPS]);
    /*printf("ULTIMAS 10 ALTURAS: [ ");
    for(int m = 0; m < nro_de_medidas; m++){
        printf("%.0f ", ultimas_medidasGPS[m]);
    }
    printf("]");*/
    return;
}

void isFalling::guardar_medidaBAR(float f){
    if(ult_auxBAR == nro_de_medidas-1){
        for(int m = 0; m < nro_de_medidas-1; m++)
            ultimas_medidasBAR[m] = ultimas_medidasBAR[m+1];
    }
    else
        ult_auxBAR++;

    ultimas_medidasBAR[ult_auxBAR] = f;
    guardar_coefBAR(coef_angularBAR());

    //IMPRIMIR VETOR DE ALTURAS
    //printf("medida armazenada. [alt = %.2f]\n", ultimas_medidasBAR[ult_auxBAR]);
    /*printf("ULTIMAS 10 ALTURAS: [ ");
    for(int m = 0; m < nro_de_medidas; m++){
        printf("%.0f ", ultimas_medidasBAR[m]);
    }
    printf("]");*/
    return;
}

//  GUARDAR_COEF GUARDA, NO VETOR DE COEF. ANGULARES
//  O ULTIMO COEFICIENTE ANGULAR CALCULADO
void isFalling::guardar_coefGPS(double cf){
    if(ult_auxGPS == nro_de_medidas-1){
        for(int m = 0; m < nro_de_medidas-1; m++)
            ultimos_coefGPS[m] = ultimos_coefGPS[m+1];
    }

    ultimos_coefGPS[ult_auxGPS] = cf;

    //IMPRIMIR ULTIMOS COEFICIENTES ANGULARES
    //printf("medida armazenada. [alt = %.2f]", ultimos_coefGPS[ult_auxGPS]);
    //printf("ULTIMOS 10 COEFICIENTES: [ ");
    /*for(int m = 0; m < nro_de_medidas; m++){
        printf("%.1f ", ultimos_coefGPS[m]);
    }*/
    //printf("]\n");
    return;
}

void isFalling::guardar_coefBAR(double cf){
    if(ult_auxBAR == nro_de_medidas-1){
        for(int m = 0; m < nro_de_medidas-1; m++)
            ultimos_coefBAR[m] = ultimos_coefBAR[m+1];
    }

    ultimos_coefBAR[ult_auxBAR] = cf;

    //IMPRIMIR ULTIMOS COEFICIENTES ANGULARES
    //printf("medida armazenada. [alt = %.2f]", ultimos_coefBAR[ult_auxBAR]);
    /*printf("ULTIMOS 10 COEFICIENTES: [ ");
    for(int m = 0; m < nro_de_medidas; m++){
        printf("%.1f ", ultimos_coefBAR[m]);
    }
    printf("]\n");*/
    return;
}

// ISFALLING, BASEADA NO COMPORTAMENTO DOS ULTIMOS
// COEF ANGULARES, DETERMINA SE A SONDA ESTA CAINDO
bool isFalling::isFallingGPS(){
    int counter = 0;
    for(int i = 0; i < nro_de_medidas; i++){
        if(ultimos_coefGPS[i] >= 0)
            counter++;
    }

    if(counter >= (nro_de_medidas/2 + 1))
        return false;
    else
        return true;
}

bool isFalling::isFallingBAR(){
    int counter = 0;
    for(int i = 0; i < nro_de_medidas; i++){
        if(ultimos_coefBAR[i] >= 0)
            counter++;
    }

    if(counter >= (nro_de_medidas/2 + 1))
        return false;
    else
        return true;
}


