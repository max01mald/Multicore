#include "ArrNode.h"

ArrNode::ArrNode()
{
    index = -1;
    Pi = -1;
    NOi = -1;
    NWi = -1;
    SOi = -1;
    SWi = -1;
    
    height = 0;
    tot_particles = 0;
    child_particles = 0;
    
    QMass = 0;
    QCenterOfMass = "0:0";
    
    PMass = 0;
    PCenterOfMass = "0:0";
}
ArrNode::ArrNode(TreeNode& tn)
{
    index = -1;
    Pi = -1;
    NOi = -1;
    NWi = -1;
    SOi = -1;
    SWi = -1;
    
    height = tn.height;
    tot_particles = tn.tot_particles;
    child_particles = tn.child_particles;
    
    Qsize = tn.quad->Size;
    QMass = tn.Mass;
    QCenterOfMass = tn.CenterOfMass;
    
    if(tn.part != NULL)
    {
        PMass = tn.part->Mass;
        PCenterOfMass = tn.part->Position;
    }
    else
    {
        PMass = 0;
        PCenterOfMass = "0:0";
    }
}

void ArrNode::toStack(stack<TreeNode> s, TreeNode tn)
{
    
}

void ArrNode::cIndex(int child, int index)
{
    if(child == 0)
    {
        this->NWi = index;
    }
    else if(child == 1)
    {
        this->NOi = index;
    }
    else if(child == 2)
    {
        this->SWi = index;
    }
    else if(child == 3)
    {
        this->SOi = index;
    }
}

int getIndex(int i, TreeNode& tn)
{
    int j=0;
    int sum=0;
    
    while(j<i)
    {
        if(tn.SubNode(j) != NULL)
        {
            //if(tn.SubNode(j)->tot_particles == 1)
            //{
                sum += tn.SubNode(j)->below;
            /*}
            else
            {
                sum += tn.SubNode(j)->tot_particles + 1;
            }*/
            
        }
        
        j++;
    }
    
    return sum;
}

void insertSub(ArrNode& an, int i, int index)
{
    if(i==0)
    {
        an.NOi = index;
    }
    else if(i==1)
    {
        an.NWi = index;
    }
    else if(i==2)
    {
        an.SOi = index;
    }
    else if(i==3)
    {
        an.SWi = index;
    }
}

//Function to transform trre to array, through a in order tree traversal
//Accepts pointer to tree node
//Array of ArrNode(NVDIA limited object/ no strings)
//Ind is the index of the array
//Gi is a pointer to a Global index position

void ArrNode::toArr(TreeNode& tn, ArrNode arr[], int ind, int* Gi)
{
    TreeNode* temp;
    
    //If its the first entry
    if(*Gi == 0)
    {
        //Create arr Node from tree node
        ArrNode a(tn);
        
        //arr node index = global index
        a.index = *Gi;
        //arr node parent index
        a.Pi = -1;
        
        //array at global pointer position
        arr[*Gi] = a;
        
        //indicate that array position is occupied
        arr[*Gi].full = 1;
    }
    
    //For each child do
    for(int i=0; i<4; i++)
    {
        //Pointer points to the child
        temp = tn.SubNode(i);
        
        if(temp != NULL)
        {
            //increment the global index
            *Gi = *Gi + 1;
            
            //transfer info from tree node to arr node
            ArrNode an(*temp);
            
            //set the index of the arr node
            an.index = *Gi;
            
            //set the parent index of the arr node
            an.Pi = ind;
            
            //set child of parent
            insertSub(arr[ind],i, *Gi);
            
            //fill array and mark as occupied
            arr[*Gi] = an;
            arr[*Gi].full = 1;
            
            //call function again
            toArr(*temp, arr,*Gi,Gi);
        }
    }
 
}

void ArrNode::print()
{
    cout << "Index " << this->index << " ";
    cout << "Pi " << this->Pi << " ";
    cout << "Tot " << this->tot_particles << " ";
    cout << "NOi " << this->NOi << " ";
    cout << "NWi " << this->NWi << " ";
    cout << "SOi " << this->SOi << " ";
    cout << "SWi " << this->SWi << " ";
    cout << "HEIGHT " << this->height << " ";
    cout << "MASS " << this->QMass << " ";
    cout << "POS " << this->QCenterOfMass << " ";
    
    
    cout << endl;
}



void ArrNode::printTree(ArrNode an[], int size)
{
    int ind = 0;
    
    while(an[ind].child_particles == 1)
    {
        ind++;
    }
    
    an[ind].print();
    
    while(ind < size)
    {
        ind++;
        an[ind].print();
    }
}

string ArrNode::CalculateForceTree(ArrNode* arr, int size, Particle &particle)
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
    
    int ind = 0;
    int skip = 0;
    
    //cycle through array
    while(ind < size)
    {
        //skip all the geight that has been chosen to skip
        if(arr[ind].height == skip)
        {
            
            if(arr[ind].tot_particles == 1)
            {
                distance = abs(Distance(arr[ind].PCenterOfMass, particle.Position));
                
                if(distance == 0)
                {
                    return "0:0";
                }
                else
                {
                    force = gravi_c*(particle.Mass * arr[ind].PMass)/(pow(distance,2));
                    Direct = Direction(particle.Position, arr[ind].PCenterOfMass);
                    
                    Force = Force + (force * Direct);
                }
            }
            else
            {
                r = abs(Distance(particle.Position,arr[ind].QCenterOfMass));
                
                if(r == 0)
                {
                    return "0:0";
                }
                else
                {
                    distance = arr[ind].Qsize;
                    result = distance/r;
                    
                    if(result < theta)
                    {
                        //cout << "HIT " << ind << endl;
                        
                        force = gravi_c*(particle.Mass * arr[ind].QMass)/(pow(r,2));
                        Direct = Direction(particle.Position, arr[ind].QCenterOfMass);
                        
                        Force = Force + (force * Direct);
                        
                        skip = arr[ind].height;
                        
                    }
                    else
                    {
                        //cout << "MISS " << ind << endl;
                        skip = arr[ind].height+1;
                    }
                }
            }
        }
        ind++;
    }
    
    return Force;
}

/*int main()
{
   int arr[100];
    
    for(int i=0; i<100; i++)
    {
        arr[i] = 0;
    }
    
    TreeNode tn;
    ArrNode an(tn);
    
    for(int i=0; i<100; i++)
    {
        cout << arr[i] << endl;
    }
    
    return 0;
}*/

