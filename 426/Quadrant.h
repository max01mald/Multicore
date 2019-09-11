#ifndef QUADRANT_H
#define QUADRANT_H

#include "Particle.h"

class Quadrant
{
	public:
	//Constructor
	Quadrant();
	Quadrant(int size);
	//Methods
	void setCord(double nwx, double nwy, double nox, double noy, double swx, double swy, double sox, double soy);
	
	double NWx_p;
	double NWy_p;
	double NOx_p;
	double NOy_p;
	double SWx_p;
	double SWy_p;
	double SOx_p;
	double SOy_p;
	
	int Size;
	int Mass;
	string CenterOfMass;
	
	
};


#endif