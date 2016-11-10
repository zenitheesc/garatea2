#include "LSM303.h"

class hLSM303 : public LSM303 {
private:
	double X_ac;
	double Y_ac;
	double Z_ac;
	double Mod;
public:
	hLSM303() : LSM303() {};
	void start();
	void readAc();
	double getX();
	double getY();
	double getZ();
	double getMod();
};


