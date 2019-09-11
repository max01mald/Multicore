#include "Particle.h"


Particle::Particle(): xCord(0), yCord(0), Position("0:0"), Mass(0), Galaxy(0), Force("0:0")
{
	this->r = 162;
	this->g = 11;
	this->b = 11;
	this->a = 255;
}

Particle::Particle(double xcord, double ycord, int mass, int galaxy): xCord(xcord), yCord(ycord), Mass(mass), Galaxy(galaxy), Force("0:0")
{
	Position = to_string(xcord) + ":" + to_string(ycord);
	if(Galaxy == 1)
	{
		this->r = 162;
		this->g = 11;
		this->b = 11;
		this->a = 255;
	}
	else
	{
		this->r = 243;
		this->g = 247;
		this->b = 64;
		this->a = 255;
	}
}


//Fills the vector with the sizes of two galaxies and creates the universe

//The idea is that one galaxy will be created as a square in the size indicated

//The universe will be 20% higher and wider

bool Inside_Circ(int x, int y, int r, int cx, int cy)
{
    x = abs(x - cx);
    y = abs(y - cy);
    
    double line = pow(x,2) + pow(y,2);
    line = sqrt(line);
    
    if(line < r)
    {
        return true;
    }
    return false;
    
}

double Distan(string pos1, string pos2)
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

string operator- (string pos1, string pos2)
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
    
    
    One = One - Three;
    Two = Two - Four;
    
    
    string result = to_string(One) + ":";
    result += to_string(Two);
    
    return result;
    
    
    
}


string mult (double mass, string position)
{
    string one;
    string two;
    
    double One;
    double Two;
    
    //cout << "MULT FUNC" << position << endl;
    
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


string divide (string position, int mass)
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

double angle_calc(string val)
{
    double x = 0;
    double y = 0;
    
    for(int i=0;i<val.length();i++)
    {
        if(val.substr(i, i+1).compare(":") > 0)
        {
            x = stod(val.substr(0,i));
            y = stod(val.substr(i+1,val.length()));
            break;
        }
    }
    
    double result = atan2(y,x);
    
    return result;
}

double tan_min(string part, string center)
{
    string diff = part-center;
    
    double angle = angle_calc(diff);
    
    return angle + 3.1415926/2;
}


vector<Particle*> Particle::UniverseCreation(int uni1, int uni2, vector<Particle*> *Particles1, vector<Particle*> *Particles2)
{
	vector<Particle*> part_vec;
	int mass = 0;
	
    double radius = sqrt(uni1/3.1415926);
    double radius2 = sqrt(uni2/3.1415926);
    
    int size = 100;
    
    int center_x_1 = 0.4*size;
    int center_y_1 = 0.4*size;
    
    int center_x_2 = 0.6*size;
    int center_y_2 = 0.6*size;
    
    radius = radius/4;
    radius2 = radius2/4;
    
    bool center = true;
    bool center2 = true;
    
	
    while((uni1 + uni2)>0)
    {
        double x = 0;
        double y = 0;
        
        if(center && uni1>0)
        {
            x = center_x_1;
            y = center_y_1;
            
            mass = 100000;
            center = false;
        }
        else if(uni1>0)
        {
            x = ((double)rand() * ((center_x_1+radius)-(center_x_1-radius))) / (double)RAND_MAX +  (center_x_1-radius);
            y = ((double)rand() * ((center_y_1+radius)-(center_y_1-radius)))/ (double)RAND_MAX +  (center_y_1-radius);
            mass = 50 + rand() % (100-50);
        }
        
        
        if(center2 && uni1 == 0)
        {
            x = center_x_2;
            y = center_y_2;
            
            mass = 100000;
            center2 = false;
        }
        else if(uni2>0 && uni1 == 0)
        {
            x = ((double)rand() * ((center_x_2+radius2)-(center_x_2-radius2))) / (double)RAND_MAX +  (center_x_2-radius2);
            y = ((double)rand() * ((center_y_2+radius2)-(center_y_2-radius2)))/ (double)RAND_MAX +  (center_y_2-radius2);
            mass = 50 + rand() % (100-50);
        }
        
        double gravi_c = 6.674* pow(10,-11);
        double orb_vel = 0;
        double angle = 0;
        double vel_x = 0;
        double vel_y = 0;
        
        string velocity = "0:0";
        string CENTER = "";
        Particle *part;
        
        if(uni1>0)
        {
            part = new Particle(x, y, mass, 1);
            CENTER = to_string(center_x_1) + ":" + to_string(center_y_1);
            
            orb_vel = sqrt(gravi_c * 18000000/ Distan(part->Position,CENTER));
            angle = tan_min(part->Position, CENTER);
            
            vel_x = orb_vel * cos(angle);
            vel_y = orb_vel * sin(angle);
            
            velocity = to_string(vel_x) + ":" + to_string(vel_y);
            
            if(x== center_x_1 && y == center_y_1)
            {
                velocity = "0:0";
            }
            
            //cout << "VEL " << velocity << endl;
            
            part->Velocity = velocity;
        }
        else if(uni2>0)
        {
            part = new Particle(x, y, mass, 2);
            CENTER = to_string(center_x_2) + ":" + to_string(center_y_2);
            
            orb_vel = sqrt(gravi_c * 18000000/ Distan(part->Position,CENTER));
            angle = tan_min(part->Position, CENTER);
            
            vel_x = orb_vel * cos(angle);
            vel_y = orb_vel * sin(angle);
            
            velocity = to_string(vel_x) + ":" + to_string(vel_y);
            
            if(x== center_x_2 && y == center_y_2)
            {
                velocity = "0:0";
            }
            
            //cout << "VEL " << velocity << endl;
            
            part->Velocity = velocity;
        }
        
        part_vec.push_back(part);
        
        if(uni1>0)
        {
            Particles1->push_back(part);
            uni1 -= 1;
        }
        else if(uni1==0)
        {
            if(uni2>0)
            {
                Particles2->push_back(part);
                uni2 -=1;
            }
        }
    }
    
    
	
	cout<<"TOT"<<part_vec.size()<<endl;
    cout<<"1"<<Particles1->size()<<endl;
    cout<<"2"<<Particles2->size()<<endl;
    
	return part_vec;

}

string Particle::add(string Position, string Force)
{
	string one;
	string two;
	
	string three;
	string four;
	
	double One;
	double Two;
	double Three;
	double Four;
	
	for(int i=0; i<Position.length(); i++)
	{
		if(Position.substr(i, i+1).compare(":") > 0)
		{
			one = Position.substr(0,i);
			two = Position.substr(i+1,Position.length());
			break;
		}
	}
	
	for(int i=0; i<Force.length(); i++)
	{
		if(Force.substr(i, i+1).compare(":") > 0)
		{
			three = Force.substr(0,i);
			four = Force.substr(i+1,Force.length());
			break;
		}
	}
		
	One = stod(one);
	Two = stod(two);
	Three = stod(three);
	Four = stod(four);
	
	One += Three;
	Two += Four;
	
	string result = to_string(One) + ":";
	result += to_string(Two);
	
	return result;
	
}

void Particle::PartForceCalc(string position, string Force)
{
    double time = 3.0;
    string force = mult(pow(time,2),Force);
    force = divide(force,2);
    
    //cout << "VELOCITY " << this->Velocity << endl;
    //cout << "FORCE " << Force << endl;
    
    
    string vel = mult(time,this->Velocity);
    
    force = add(force,vel);
    
    this->Position = this->add(position,force);
	
	string one = "";
	string two = "";
	
	for(int i=0; i<this->Position.length(); i++)
	{
		if(this->Position.substr(i, i+1).compare(":") > 0)
		{
			one = this->Position.substr(0,i);
			two = this->Position.substr(i+1,this->Position.length());
			break;
		}
	}
	
	this->xCord = stod(one);
	this->yCord = stod(two);
    
    force = mult(time, Force);
    this->Velocity = add(this->Velocity,force);
	
}

void Particle::PartReversal()
{
    int count = 0;
    
    string vel = this->Velocity;
    
    for(int i=0; i<this->Velocity.size(); i++)
    {
        if(vel.substr(i,i+1).compare("+"))
        {
            cout << vel[i] << endl;
            count += 1;
            exit(0);
        }
    }
    
}
