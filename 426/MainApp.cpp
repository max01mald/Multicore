#include "MainApp.h"

MainApp::MainApp(int galaxy1, int galaxy2)
{
	Particle* part = new Particle();
	
	Particles = part->UniverseCreation(galaxy1,galaxy2,&Particles1,&Particles2);
    
	cout<< "constructor " << Particles.size() << endl;
	
	delete part;
	
    int size = 100;
	
	TreeNode* n_root = new TreeNode(size);
    TreeNode* n_root1 = new TreeNode(size);
    TreeNode* n_root2 = new TreeNode(size);
    
	Root = n_root;
    Root1 = n_root1;
    Root2 = n_root2;
    
	
}

void Insert(MainApp &mapp, int t)
{
    int size = mapp.Particles.size()/7;
    
    for(int i=t*size; i<(t*size)+size; i++)
    {
        mapp.Root->InsertToNode(*mapp.Particles[i]);
    }
}



void MainApp::BuildTree(MainApp& mapp)
{
    
   
}

void ForCal(MainApp &mapp, int t)
{
    int size = mapp.Particles.size()/7;
    
    for(int i=t*size; i<(t*size)+size; i++)
    {
        Particle* part;
        part = mapp.Particles[i];
        
        part->Force = mapp.Root->CalculateForceTree(*part);
        
        //cout << "Before force " << mapp.Particles[i]->Position << endl;
       
        //cout << "PART MASS: " << mapp.Particles[i]->Mass << endl;
        //cout << "PART FORCE: " << mapp.Particles[i]->Force << endl;
        
        part->PartForceCalc(part->Position, part->Force);
        
        //cout << "After force " << mapp.Particles[i]->Position << endl;
        
        //cout << mapp.Root->quad->Size << endl;
        
        if(mapp.Particles[i]->xCord > mapp.Root->quad->Size)
        {
            //printf("X OUT OF BOUNDS");
            mapp.Particles.erase(mapp.Particles.begin()+i);
        }
        
        if(mapp.Particles[i]->yCord > mapp.Root->quad->Size)
        {
            //printf("Y OUT OF BOUNDS");
            mapp.Particles.erase(mapp.Particles.begin()+i);
        }
        
        //cout << "FORCE: " << this->Particles[i]->Force << endl;
        //cout << "Direction: " << this->Particles[i]->Direction << endl;
    }
}

void MainApp::CalcForce(MainApp& mapp)
{
    //Create Within Function
    
    for(int t=0; t<7; t++)
    {
        /*thread th (ForCal, ref(mapp), t);
        
        th.join();*/
    }
    
    //With Locks
    
   
	/*for(int i=0; i<mapp.Particles.size(); i++)
	{
		Particle* part;
		part = mapp.Particles[i];
		
		part->Force = mapp.Root->CalculateForceTree(*part);
		
		cout << "Before force " << mapp.Particles[i]->Position << endl;
		
		part->PartForceCalc(part->Position, part->Force);
		
		cout << "After force " << mapp.Particles[i]->Position << endl;
		
        cout << mapp.Root->quad->Size << endl;
        
        if(mapp.Particles[i]->xCord > mapp.Root->quad->Size)
        {
            printf("X OUT OF BOUNDS");
            mapp.Particles.erase(mapp.Particles.begin()+i);
        }
        
        if(mapp.Particles[i]->yCord > mapp.Root->quad->Size)
        {
            printf("Y OUT OF BOUNDS");
            mapp.Particles.erase(mapp.Particles.begin()+i);
        }
        
		//cout << "FORCE: " << this->Particles[i]->Force << endl;
		//cout << "Direction: " << this->Particles[i]->Direction << endl;
	}*/
    

}

void MainApp::printParticles()
{
	cout << "Particles size: " << this->Particles.size() << endl;
	
	for(int i=0; i<this->Particles.size(); i++)
	{
		cout << "Position: " <<this->Particles[i]->Position << " ";
		cout << " Mass: " << this->Particles[i]->Mass << " ";
		cout << " Galaxy: " << this->Particles[i]->Galaxy << " ";
		cout << " Force: " << this->Particles[i]->Force << endl;
		//cout << " Direction: " << this->Particles[i]->Direction << endl;
	}

}

void MainApp::printTree()
{
	this->Root->printTree();
}

void MainApp::printTree1()
{
    this->Root1->printTree();
}

void MainApp::printTree2()
{
    this->Root2->printTree();
}

void MainApp::printAnTree()
{
    int size = 0;
    
    ArrNode* arr = this->An;
    
    for(int i=0;i<this->An_size;i++)
    {
        if(arr[i].full)
        {
            arr[i].print();
            size += 1;
        }
        else
        {
            break;
        }
        
    }
}

void MainApp::printAnTree1()
{
    int size = 0;
    
    ArrNode* arr = this->An1;
    
    for(int i=0;i<this->An_size1;i++)
    {
        if(arr[i].full)
        {
            arr[i].print();
            size += 1;
        }
        else
        {
            break;
        }
        
    }
}

void MainApp::printAnTree2()
{
    int size = 0;
    
    ArrNode* arr = this->An2;
    
    for(int i=0;i<this->An_size2;i++)
    {
        if(arr[i].full)
        {
            arr[i].print();
            size += 1;
        }
        else
        {
            break;
        }
        
    }
}

/*int main(int argc, char** argv)
{
	
	
	MainApp mapp(100,100);
	
	mapp.BuildTree();
	//mapp.Root->ComputeMassDistribution();
	//mapp.CalcForce();
	
	//mapp.printParticles();
	
	//mapp.printTree();
	
 
    
    
	return 0;
};*/









