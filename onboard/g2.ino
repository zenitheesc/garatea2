//Identificação do input de cada sensor
#define DHTPIN 2 //dht22 no pino 2
#define DHTTYPE DHT22
#define ONE_WIRE_BUS 8 //ds18b20 no pino 8

//BIBLIOTECAS DO ACELERÔMETRO
#include <Wire.h>
#include <LSM303.h>

//Bibliotecas do sensor de umidade DHT22
#include "DHT.h"

//Bibliotecas do sensor de temperatura DS18B20
#include <OneWire.h>
#include <DallasTemperature.h>

//Configurações globais dos sensores
//Configuração do ac
LSM303 compass; 
//Configuração do dht22
DHT dht(DHTPIN, DHTTYPE);
//COnfiguração do ds28b20
OneWire oneWire(ONE_WIRE_BUS); 
DallasTemperature sensors(&oneWire);


//Setup do Arduino
void setup() {
    Serial.begin(9600);

    //Iniciando o acelerômetro
    Wire.begin();
    compass.init();
    compass.enableDefault();

    //Iniciando o DHT22
    dht.begin(); 

    //Iniciando o DS18B20
    sensors.begin();
}

float* le_dht22(float (&leitura_dht22)[3]){ //Método de referencia garente que o vetor tenha o tamanho apropriado!
      if(sizeof(leitura_dht22) < 12) { //redundancia na verificação de memória
        Serial.print("Não há memória reservada suficiente para ler o sensor DHT22");
        leitura_dht22[0] = -1.0;
        return leitura_dht22;
      } else {
        leitura_dht22[0] = dht.readHumidity();
        leitura_dht22[1] = dht.readTemperature();
        leitura_dht22[2] = dht.computeHeatIndex(leitura_dht22[1], leitura_dht22[0], false);
        return leitura_dht22;
    }
}

void imprime_dht22(float* leitura_dht22){
      Serial.print("\nLeituras do DHT22:");
      Serial.print("\nHumidade: ");
      Serial.print(leitura_dht22[0]);
      Serial.print("\nTemperatura: ");
      Serial.print(leitura_dht22[1]);
      Serial.print(" *C ");
      Serial.print("\nSensacao termica: ");
      Serial.print(leitura_dht22[2]);
      Serial.print(" *C \n");
      return;
}

void imprime_lms303d(){
      char report[80];
      Serial.print("\nLeituras do LMS303D:");
      snprintf(report, sizeof(report), "\nAceleracao: (%6d,%6d,%6d)\nCampo Magnetico: (%6d,%6d,%6d)",
      compass.a.x, compass.a.y, compass.a.z,
      compass.m.x, compass.m.y, compass.m.z);
      Serial.println(report);
}

void imprime_ds18b20(){
    Serial.print("\nLeituras do DS18B20:");
    Serial.print("\nTemperatura: ");
    Serial.print(sensors.getTempCByIndex(0));
}

void loop() {
    //realiza leitura do acelerometro
    compass.read();
    //imprime a leitura do acelerometro
    imprime_lms303d();
    
    //vetor para armazenar a leitura do dht22, este vetor DEVE 3 ESPAÇOS PARA FLOAT.
    float leitura_dht22[3] = {-1, -1, -1};
    le_dht22(leitura_dht22); //Tenta realizar a leitura do dht22
    
    //Se conseguiu ler, imprime as leituras do dht22
    if(leitura_dht22[0] != -1) imprime_dht22(leitura_dht22);  
    //Senão, imprime o erro
    else Serial.print("Leitura nao realizada.");

    //Realiza leitura do DS18B20
    sensors.requestTemperatures(); 
    //Imprime leitura do DS18B20
    imprime_ds18b20();
    
    //Delay 5 segundos  
    delay(5000); 
}
