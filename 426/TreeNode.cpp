#include "TreeNode.h"

TreeNode::TreeNode()
{
	Parent = NULL;
	NW = NULL;
	NO = NULL;
	SW = NULL;
	SO = NULL;
	part = NULL;
	quad = new Quadrant();
	height = 0;
	tot_particles = 0;
	child_particles = 0;
	Mass = 0;
	CenterOfMass = "0:0";
    below = 0;
}

TreeNode::TreeNode(int size)
{
	Parent = NULL;
	NW = NULL;
	NO = NULL;
	SW = NULL;
	SO = NULL;
	part = NULL;
	quad = new Quadrant(size);
	height = 0;
	tot_particles = 0;
	child_particles = 0;
	Mass = 0;
    below = 0;
    
    double Cord = size/2;
    string cord = to_string(Cord);
    
    //CenterOfMass = strca(cord, cord);
    CenterOfMass = "0:0";
    
  
}

TreeNode::~TreeNode()
{
	
	if(NW != NULL)
	{
		delete NW;
		NW = NULL;
	}
	
	if(NO != NULL)
	{
		delete NO;
		NO = NULL;
	}
	
	if(SW != NULL)
	{
		delete SW;
		SW = NULL;
	}
	
	if(SO != NULL)
	{
		delete SO;
		SO = NULL;
	}
	
	if(this->part != NULL)
	{
		//delete this->part;
		//this->part = NULL;
	}
	//cout << "6 " << endl;
	if(this->quad != NULL)
	{
		delete this->quad;
		this->quad = NULL;
	}	
	//cout << "7" << endl;
	
	
}

void TreeNode::createSubNode(int quad)
{
	//creates new TreeNode Object which will be pointed to
	
	//cout << "Create Sub Method" << endl;
	//cout << "Quad " << quad << endl;
	
	TreeNode *sub;
	sub = new TreeNode();
	sub->Parent = this;
	sub->height = this->height+1;
	
	sub->setQuadrant(quad);
	
	this->child_particles += 1;
    
	if(quad == 0)
	{
		this->NW = sub;
	}
	else if(quad == 1)
	{
		this->NO = sub;
	}
	else if(quad == 2)
	{
		this->SW = sub;
	}
	else if(quad == 3)
	{
		this->SO = sub;
		
	}
	
}

TreeNode* TreeNode::SubNode(int quad)
{
	//returns the Quadrant that is requested
	
	//cout << "Sub Node Method GETTER" << endl;
	//cout << quad << endl;
	
	if(quad == 0)
	{
		return this->NW;
	}
	else if(quad == 1)
	{
		return this->NO;
	}
	else if(quad == 2)
	{
		return this->SW;
	}
	else if(quad == 3)
	{
		//cout << "INSIDE " << this->SO <<endl;
		return this->SO;
	}
    else
    {
        cout << quad << endl;
        exit(0);
    }
    return NULL;
}

void TreeNode::P_ResetTree()
{
	//Recursively Travels the tree and deletes the TreeNode Pointer calls Destructor ~TreeNode()
	
	bool nw = false;
	bool no = false;
	bool sw = false;
	bool so = false;
	
	if(this->NW != NULL)
	{
		this->NW->P_ResetTree();
		nw = true;
	}
	if(this->NO != NULL)
	{
		this->NO->P_ResetTree();
		no = true;
	}
	if(this->SW != NULL)
	{
		this->SW->P_ResetTree();
		sw = true;
	}
	if(this->SO != NULL)
	{
		this->SO->P_ResetTree();
		so = true;
	}
	
	if(nw)
	{
		//cout << "delete nw" << endl;
		//cout << "height " << this->NW->height << endl;
		//cout << "particle " << this->NW->part << endl;
		delete this->NW;
		this->NW = NULL;
		}
	
	if(no)
	{
		//cout << "delete n0" << endl;
		//cout << "height " << this->NO->height << endl;
		//cout << "particle " << this->NO->part << endl;
		delete this->NO;
		this->NO = NULL;
	}
	
	if(sw)
	{
		//cout << "delete sw" << endl;
		//cout << "height " << this->SW->height << endl;
		//cout << "particle " << this->SW->part << endl;
		delete this->SW;
		this->SW = NULL;
	}
	
	if(so)
	{
		//cout << "delete so" << endl;
		//cout << "height " << this->SO->height << endl;
		//cout << "particle " << this->SO->part << endl;
		delete this->SO;
		this->SO = NULL;
	}
	
	if(this->Parent != NULL && this->child_particles > 0 && this->tot_particles == 0)
	{
		//cout << "height " << this->height << endl;
		//cout << "delete Node" << endl;
		//cout << "particle " << this->part << endl;
        
		delete this;
	}
    
    if(this->Parent == NULL)
    {
        this->height = 0;
        this->tot_particles = 0;
        this->child_particles = 0;
        this->Mass = 0;
        this->CenterOfMass = "0:0";
    }
	
}

void TreeNode::ResetTree()
{
	this->P_ResetTree();
	
	NW = NULL;
	NO = NULL;
	SW = NULL;
	SO = NULL;
	
	
	height = 0;
	tot_particles = 0;
	child_particles = 0;
	Mass = 0;
	CenterOfMass = "0:0";
	
}

int TreeNode::getQuadrant(Particle n_particle)
{
	//According to the current Node the new Quadrant of the Particle is found
	double NWx_q = this->quad->NWx_p;
	double NWy_q = this->quad->NWy_p;
	double NOx_q = this->quad->NOx_p;
	double NOy_q = this->quad->NOy_p;
	double SWx_q = this->quad->SWx_p;
	double SWy_q = this->quad->SWy_p;
	double SOx_q = this->quad->SOx_p;
	double SOy_q = this->quad->SOy_p;
	
	double x_part = n_particle.xCord;
	double y_part = n_particle.yCord;
	
	double W_O = (NWx_q + NOx_q)/2;
	double N_S = (NWy_q + SWy_q)/2;
	
	//Test West or East
	if(x_part < W_O)
	{
		//Test North or South
		if(y_part < N_S)
		{
			return 0;
		}
		else
		{
			return 2;
		}
	}
	else
	{
		if(y_part < N_S)
		{
			return 1;
		}
		else
		{
			return 3;
		}
	}
	
}

void TreeNode::setQuadrant(int sector)
{
	//Creates the Quadrant (which is selected by the user) for a SubNode From the Parent
	double NWx_q = this->Parent->quad->NWx_p;
	double NWy_q = this->Parent->quad->NWy_p;
	double NOx_q = this->Parent->quad->NOx_p;
	double NOy_q = this->Parent->quad->NOy_p;
	double SWx_q = this->Parent->quad->SWx_p;
	double SWy_q = this->Parent->quad->SWy_p;
	double SOx_q = this->Parent->quad->SOx_p;
	double SOy_q = this->Parent->quad->SOy_p;
	
	double W_O = (NWx_q + NOx_q)/2;
	double N_S = (NWy_q + SWy_q)/2;
	
	if(sector == 0)
	{
		this->quad->NWx_p = NWx_q;
		this->quad->NWy_p = NWy_q;
		this->quad->NOx_p = W_O;
		this->quad->NOy_p = NWy_q;
		this->quad->SWx_p = NWx_q;
		this->quad->SWy_p = N_S;
		this->quad->SOx_p = W_O;
		this->quad->SOy_p = N_S;
        this->quad->Size = NWx_q - NOx_q;
	}
	else if(sector == 1)
	{
		this->quad->NWx_p = W_O;
		this->quad->NWy_p = NWy_q;
		this->quad->NOx_p = NOx_q;
		this->quad->NOy_p = NOy_q;
		this->quad->SWx_p = W_O;
		this->quad->SWy_p = N_S;
		this->quad->SOx_p = NOx_q;
		this->quad->SOy_p = N_S;
        this->quad->Size = NWx_q - NOx_q;
	}
	else if(sector == 2)
	{
		this->quad->NWx_p = NWx_q;
		this->quad->NWy_p = N_S;
		this->quad->NOx_p = W_O;
		this->quad->NOy_p = N_S;
		this->quad->SWx_p = NWx_q;
		this->quad->SWy_p = SWy_q;
		this->quad->SOx_p = W_O;
		this->quad->SOy_p = SWy_q;
        this->quad->Size = NWx_q - NOx_q;
	}
	else if(sector == 3)
	{
		this->quad->NWx_p = W_O;
		this->quad->NWy_p = N_S;
		this->quad->NOx_p = NOx_q;
		this->quad->NOy_p = SOy_q;
		this->quad->SWx_p = W_O;
		this->quad->SWy_p = SWy_q;
		this->quad->SOx_p = SOx_q;
		this->quad->SOy_p = SOy_q;
        this->quad->Size = NWx_q - NOx_q;
	}
	
}


void TreeNode::InsertToNode(Particle &n_Particle)
{
    
	TreeNode* temp;
	//cout << "temp" << endl;
	Particle* partic;
	//cout << "part" << endl;
	
	int quad;
	
    //partic = &n_Particle;
    
	if(this->tot_particles > 1)
	{
		quad = this->getQuadrant(n_Particle);
		
		if(this->SubNode(quad) == NULL)
		{
			//cout << "create one " << endl;
			//cout << quad << endl;
			this->createSubNode(quad);
		}
		
        this->SubNode(quad)->InsertToNode(n_Particle);
	}
	else if(this->tot_particles == 1)
	{
		partic = this->part;
        
		quad = this->getQuadrant(*partic);
        
		if(this->SubNode(quad) == NULL)
		{
			//cout << "create two " << this->tot_particles << endl;
			this->createSubNode(quad);
            
		}
		
        this->SubNode(quad)->InsertToNode(*partic);
        
        this->part = NULL;
		
		quad = this->getQuadrant(n_Particle);
		
		if(this->SubNode(quad) == NULL)
		{
			//cout << "create three " << endl;
			//cout << quad << endl;
			this->createSubNode(quad);
            
		}
        this->SubNode(quad)->InsertToNode(n_Particle);

	}
	else if(this->tot_particles == 0)
	{
        this->part = &n_Particle;
	}
    
    this->tot_particles += 1;
	
	
	temp = NULL;
	delete temp;
	partic = NULL;
	delete partic;
}

void TreeNode::ComputeMassDistribution()
{
	TreeNode* temp;
	
	if(this->tot_particles == 1)
	{
		this->CenterOfMass = this->part->Position;
		this->Mass = this->part->Mass;
		
	}
	else
	{
		for(int i=0; i<4; i++)
		{
			temp = this->SubNode(i);
			
			if(temp != NULL)
			{
				temp->ComputeMassDistribution();
			
				this->Mass += temp->Mass;
				
				string calc = temp->Mass * temp->CenterOfMass;
				
				this->CenterOfMass = this->CenterOfMass + calc;
				
				//cout << "Mass " << this->Mass << endl;
				//cout << "COM " << this->CenterOfMass << endl;
				
			}
		}
		this->CenterOfMass = this->CenterOfMass / this->Mass;
	}
	temp = NULL;
	delete temp;
}


string TreeNode::CalculateForceTree(Particle &particle)
{
	TreeNode* temp;
	Particle* part;
	
	double gravi_c = 6.674* pow(10,-11);
	
	double r = 0;
	double distance = 0;
	double result = 0;
	
	double theta = 0.5;
	
	double force = 0;
	string Force = "0:0";
	string Direct = "";
	
	
	if(this->tot_particles == 1)
	{
        //cout << "TOT = 1 " << endl;
		part = this->part;
		
		distance = abs(Distance(part->Position, particle.Position));
		
		if(distance == 0)
		{
			return "0:0";
		}
		
		force = gravi_c*(particle.Mass * part->Mass)/(pow(distance,2));
		Direct = Direction(particle.Position, part->Position);
		
		Force = force * Direct;
		
	}
	else
	{
		r = abs(Distance(particle.Position,this->CenterOfMass));
		
		if(r == 0)
		{
			return "0:0";
		}
		
		distance = this->quad->Size;
		result = distance/r;
		
		if(result < theta)
		{
            //cout << "Hit " << endl;
            
			force = gravi_c*(particle.Mass * this->Mass)/(pow(r,2));
			Direct = Direction(particle.Position, this->CenterOfMass);
			
			Force = force * Direct;
			
		}
		else
		{
            //cout << "Miss " << endl;
			for(int i=0; i<4; i++)
			{
				temp = this->SubNode(i);
				
				if(temp != NULL)
				{
					Force = Force + temp->CalculateForceTree(particle);
				}
			}
		}
	}
    
	return Force;

}

void TreeNode::printTree()
{
	
	TreeNode* temp;
	
    cout << "Height: " << this->height << " ";
    //cout << "Domain: " << i << " ";
    //cout << "Particle: " << this->part << " ";
    cout << " tot_particles: " << this->tot_particles << " ";
    cout << " child_particles: " << this->child_particles << " ";
    cout << " Mass: " << this->Mass << " ";
    cout << " CenterOfMass: " << this->CenterOfMass << endl;
    
    
	for(int i=0; i<4; i++)
	{
		temp = this->SubNode(i);
		
		if(temp != NULL)
		{
			temp->printTree();
		}
	}	
			

}

/*int main()
{
	TreeNode* p = new TreeNode();
	
	delete p;
	return 0;
}*/


