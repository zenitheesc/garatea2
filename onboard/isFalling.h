#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define nro_de_medidas 6 //MARGEM DE SEGURAN�A


class isFallingChecker {
private:
	double ultimas_medidasGPS[nro_de_medidas] = {0.0}; // VETOR QUE CONTÉM AS ULTIMAS ALTURAS DO GPS
	double ultimas_medidasBAR[nro_de_medidas] = {0.0}; // VETOR QUE CONTEM AS ULTTIMAS ALTURAS DO BAROMETRO
	double ultimos_coefGPS[nro_de_medidas] = {0.0};    // VETOR QUE CONTÉM OS ÚLTIMOS COEF. ANGULARES DO GPS
	double ultimos_coefBAR[nro_de_medidas] = {0.0};    // VETOR QUE CONTÉM OS ÚLTIMOS COEF. ANGULARES DO BAROMETRO
	int ult_auxGPS = -1; //NECESSÁRIO PARA O FUNCIONAMENTO CORRETO DA FUNÇAO GUARDAR MEDIDA
	int ult_auxBAR = -1;
	float faltitude;
public:
	double coef_angularGPS();
	double coef_angularBAR();
	void guardar_medidaGPS();
	void guardar_medidaBAR();
	void guardar_coefGPS(double cf);
	void guardar_coefBAR(double cf);
	bool isFallingGPS();
	bool isFallingBAR();
	bool hasLanded(double hGPS);
};
