///// DERIVADA NUMÉRICA - FÓRMULA DO PONTO MÉDIO DE 5 PONTOS ///////
#include <stdio.h>

class NumericDiff {
private:
	double h;
	double CTE;
	double f[5];
	double D;
public:
	NumericDiff(double h);
	void addData(double y);
	void computeDiff();
	double getAngularCoef();
	bool isFallingND();
};


