#include "hLSM303.h"
#define R 10

void hLSM303::start(){
	this->init();
  	this->enableDefault();

  	X_ac = 10.0;
	Y_ac = 10.0;
	Z_ac = 10.0;
	Mod = 10.0;
}

void hLSM303::readAc(){


 	for(int i = 0; i < R; i++){
 		this->read();
	    X_ac = X_ac + ( (a.x - 75)   * 0.000590 );
	    Y_ac = Y_ac + ( (a.y + 58)   * 0.000605 );
	    Z_ac = Z_ac + ( (a.z - 1535) * 0.000593 );
  	}

  	X_ac = X_ac / R;
  	Y_ac = Y_ac / R;
  	Z_ac = Z_ac / R;
  	Mod = Mod + sqrt( (X_ac*X_ac) + (Y_ac*Y_ac) + (Z_ac*Z_ac) ) ;
}

double hLSM303::getX(){
	return X_ac;
}

double hLSM303::getY(){
	return Y_ac;
}

double hLSM303::getZ(){
	return Z_ac;
}

double hLSM303::getMod(){
	return Mod;
}


