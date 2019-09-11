#ifndef OPPERATOR_H
#define OPPERATOR_H

using namespace std;

#include <iostream>
#include <string>
#include <math.h>


string operator* (double mass, string position);
string operator+ (string pos1, string pos2);
string operator/ (string position, int mass);
double Distance(string pos1, string pos2);
string Direction(string pos1, string pos2);
string strca(string one, string two);


#endif
