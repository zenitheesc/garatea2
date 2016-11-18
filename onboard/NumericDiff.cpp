#include "NumericDiff.h"

NumericDiff::NumericDiff(double h){
  this->h = h;
  CTE = 1 / (12*h);
  for(int i = 0; i < 5; i++){
    f[i] = 0;
  }
}

void NumericDiff::addData(double y){
	for(int i = 0; i < 4; i++){
		f[i] = f[i+1];
	}
	f[4] = y;
}

void NumericDiff::computeDiff(){
	D = CTE * ( f[0] - 8*f[1] + 8*f[3] - f[4] );
}

double NumericDiff::getAngularCoef(){
	return D;
}

