#include "hLSM303.hpp"
#define R 10

void hLSM303::start(){
	this->init();
  	this->enableDefault();
}

void hLSM303::readAc(){
	X_ac = 0;
	Y_ac = 0;
	Z_ac = 0;
	Mod = 0;

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


