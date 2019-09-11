#ifndef PARTICLE_H
#define PARTICLE_H

using namespace std;

#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <vector>
#include <iostream>
#include <pthread.h>
#include <math.h>

class Particle
{
	public:
	//Constructor
	Particle();
	Particle(double xcord, double ycord, int mass, int galaxy);
	
	//Method
	vector<Particle*> UniverseCreation(int uni1, int uni2, vector<Particle*> *Particles1, vector<Particle*> *Particles2);
	void PartForceCalc(string position, string Force);
	string add(string Position, string Force);
    void PartReversal();
    
	double xCord;
	double yCord;
	string Position;
	int Mass;
	int Galaxy;
	string Force;
    double Fx;
    double Fy;
	string Direction;
    double Dx;
    double Dy;
    string Velocity;
    double Vx;
    double Vy;
	unsigned char r;
	unsigned char g;
	unsigned char b;
	unsigned char a;
	
};

#endif
