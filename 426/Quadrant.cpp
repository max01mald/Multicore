#include "Quadrant.h"

Quadrant::Quadrant(): NWx_p(0), NWy_p(0), NOx_p(0), NOy_p(0), SWx_p(0), SWy_p(0), SOx_p(0), SOy_p(0), Mass(0), CenterOfMass("0:0")
{
}

Quadrant::Quadrant(int size)
{
	this->NWx_p = 0;
	this->NWy_p = 0;
	this->NOx_p = size;
	this->NOy_p = 0;
	this->SWx_p = 0;
	this->SWy_p = size;
	this->SOx_p = size;
	this->SOy_p = size;
	
	this->Size = size;
}

void Quadrant::setCord(double nwx, double nwy, double nox, double noy, double swx, double swy, double sox, double soy)
{
	this->NWx_p = nwx;
	this->NWy_p = nwy;
	this->NOx_p = nox;
	this->NOy_p = noy;
	this->SWx_p = swx;
	this->SWy_p = swy;
	this->SOx_p = sox;
	this->SOy_p = soy;
	
	this->Size = abs(NWx_p - NOx_p); 
	
}



