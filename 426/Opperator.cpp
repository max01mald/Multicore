#include "Opperator.h"


/*

	Programmed so that the Position "xx:yy" string can be manipulated as if they were numbers"

*/


string operator* (double mass, string position)
{
	string one;
	string two;
	
	double One;
	double Two;
	
	for(int i=0; i<position.length(); i++)
	{
		if(position.substr(i, i+1).compare(":") > 0)
		{
			one = position.substr(0,i);
			two = position.substr(i+1,position.length());
			break;
		}
	}
		
	One = stod(one);
	Two = stod(two);
	
	One *= mass;
	Two *= mass;
	
	string result = to_string(One) + ":";
	result += to_string(Two);
	
	return result;
	
}

string operator+ (string pos1, string pos2)
{
	string one;
	string two;
	string three;
	string four;
	
	double One;
	double Two;
	double Three;
	double Four;
	
	for(int i=0; i<pos1.length(); i++)
	{
		if(pos1.substr(i, i+1).compare(":") > 0)
		{
			one = pos1.substr(0,i);
			two = pos1.substr(i+1,pos1.length());
			break;
		}
	}
	
	for(int i=0; i<pos2.length(); i++)
	{
		if(pos2.substr(i, i+1).compare(":") > 0)
		{
			three = pos2.substr(0,i);
			four = pos2.substr(i+1,pos2.length());
			break;
		}
	}
	
	One = stod(one);
	Two = stod(two);
	Three = stod(three);
	Four = stod(four);
	
	
	One = One + Three;
	Two = Two + Four;
	
	string result = to_string(One) + ":";
	result += to_string(Two);
	
	return result;
	
	
	
}

string operator/ (string position, int mass)
{
	string one;
	string two;
	
	double One;
	double Two;
	
	for(int i=0; i<position.length(); i++)
	{
		if(position.substr(i, i+1).compare(":") > 0)
		{
			one = position.substr(0,i);
			two = position.substr(i+1,position.length());
			break;
		}
	}
	
	One = stod(one);
	Two = stod(two);
	One /= mass;
	Two /= mass;
	
	string result = to_string(One) + ":";
	result += to_string(Two);
	
	return result;
}

double Distance(string pos1, string pos2)
{
	string one;
	string two;
	string three;
	string four;
	
	double One;
	double Two;
	double Three;
	double Four;
	
	for(int i=0; i<pos1.length(); i++)
	{
		if(pos1.substr(i, i+1).compare(":") > 0)
		{
			one = pos1.substr(0,i);
			two = pos1.substr(i+1,pos1.length());
			break;
		}
	}
	
	for(int i=0; i<pos2.length(); i++)
	{
		if(pos2.substr(i, i+1).compare(":") > 0)
		{
			three = pos2.substr(0,i);
			four = pos2.substr(i+1,pos2.length());
			break;
		}
	}
	
	One = stod(one);
	Two = stod(two);
	Three = stod(three);
	Four = stod(four);
	
	One = abs(One - Three);
	Two = abs(Two - Four);
	
	Three = pow(One,2) + pow(Two,2);
	
	Three = sqrt(Three);
	
	return Three;

}

string Direction(string pos1, string pos2)
{
	string one;
	string two;
	string three;
	string four;
	
	int One;
	int Two;
	int Three;
	int Four;
	
	for(int i=0; i<pos1.length(); i++)
	{
		if(pos1.substr(i, i+1).compare(":") > 0)
		{
			one = pos1.substr(0,i);
			two = pos1.substr(i+1,pos1.length());
			break;
		}
	}
	
	for(int i=0; i<pos2.length(); i++)
	{
		if(pos2.substr(i, i+1).compare(":") > 0)
		{
			three = pos2.substr(0,i);
			four = pos2.substr(i+1,pos2.length());
			break;
		}
	}
	
	One = stoi(one);
	Two = stoi(two);
	Three = stoi(three);
	Four = stoi(four);
	
	One = Three - One;
	Two = Four - Two;
	
	string result = to_string(One) + ":";
	result += to_string(Two);
	
	return result;

}

string F_Dir(string pos1, string pos2)
{
    string one;
    string two;
    string three;
    string four;
    
    int One;
    int Two;
    int Three;
    int Four;
    
    for(int i=0; i<pos1.length(); i++)
    {
        if(pos1.substr(i, i+1).compare(":") > 0)
        {
            one = pos1.substr(0,i);
            two = pos1.substr(i+1,pos1.length());
            break;
        }
    }
    
    for(int i=0; i<pos2.length(); i++)
    {
        if(pos2.substr(i, i+1).compare(":") > 0)
        {
            three = pos2.substr(0,i);
            four = pos2.substr(i+1,pos2.length());
            break;
        }
    }
    
    One = stoi(one);
    Two = stoi(two);
    Three = stoi(three);
    Four = stoi(four);
    
    One = Three - One;
    Three = Four - Three;
    
    
    
    string result = to_string(One) + ":";
    result += to_string(Two);
    
    return result;

}

string strca(string one, string two)
{
    int One = one.length();
    int Two = two.length();
    int size = One + Two + 1;
    
    char temp[size];
    
    for(int i = 0; i<One; i++)
    {
        temp[i] = one[i];
    }
    temp[One] = ':';
    
    for(int i=One+1; i<Two+One; i++)
    {
        temp[i] = two[i-(One+1)];
    }
    
    return temp;
}
