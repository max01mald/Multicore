#include "OpenGL.h"


#include </usr/local/Cellar/tbb/2018_U5/include/tbb/parallel_for.h>
#include </usr/local/Cellar/tbb/2018_U5/include/tbb/task_scheduler_init.h>

using namespace tbb;

struct Point
	{
		float x, y;
		unsigned char r, g, b, a;
	};

std::vector<Particle> points;
std::vector<Particle> points1;
std::vector<Particle> points2;
MainApp* mapp;
mutex mtx;

int one = 0;
int two = 0;
int size = 0;

void init(void) 
{
   glClearColor (0.0, 0.0, 0.0, 0.0);
   
}

double xx = 5;
double yy = 5;

void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    
    //cout << "Size: " << size << endl;
    //cout << "Vector Size: " << points.size() << endl;
    
	glOrtho( 0, size, size, 0, -1, 1 );
	
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
	
    glEnableClientState( GL_VERTEX_ARRAY );
    glEnableClientState( GL_COLOR_ARRAY );
    glVertexPointer(2, GL_DOUBLE, sizeof(Particle), &points[0].xCord );
    glColorPointer(4, GL_UNSIGNED_BYTE, sizeof(Particle), &points[0].r );
    glPointSize( 1.0 );
    glDrawArrays(GL_POINTS, 0, points.size());
    glDisableClientState( GL_VERTEX_ARRAY );
    glDisableClientState( GL_COLOR_ARRAY );

    
    /*glEnableClientState( GL_VERTEX_ARRAY );
    glEnableClientState( GL_COLOR_ARRAY );
    glVertexPointer(2, GL_DOUBLE, sizeof(Particle), &points1[0].xCord );
    glColorPointer(4, GL_UNSIGNED_BYTE, sizeof(Particle), &points1[0].r );
    glPointSize( 1.0 );
    glDrawArrays(GL_POINTS, 0, points1.size());
    glDisableClientState( GL_VERTEX_ARRAY );
    glDisableClientState( GL_COLOR_ARRAY );*/
    
    glFinish();
    
    glutSwapBuffers();
    
}

void BuildT(MainApp &mapp)
{
    for(int i=0; i<mapp.Particles.size();i++)
    {
        mapp.Root->InsertToNode(*mapp.Particles[i]);
        //cout << i << " " << endl;
    }

}

void BuildT1(MainApp &mapp)
{
    for(int i=0; i<mapp.Particles1.size();i++)
    {
        mapp.Root1->InsertToNode(*mapp.Particles1[i]);
        //cout << i << " " << endl;
    }
    
}

void BuildT2(MainApp &mapp)
{
    for(int i=0; i<mapp.Particles2.size();i++)
    {
        mapp.Root2->InsertToNode(*mapp.Particles2[i]);
        //cout << i << " " << endl;
    }
    
}

void Construct_Array_Tree(MainApp &mapp)
{
    
    ArrNode an;
    int size = 6 + mapp.Particles.size()*4;
    
    
    //cout << "SIZZEE " << size << endl;
    //cout <<
    
    ArrNode* arr = NULL;
    arr = new ArrNode[size]();
    
    //ArrNode arr[size];
    
    int st = 0;
    int* ind = &st;
    
    an.toArr(*mapp.Root, arr,0,ind);
    
    if(*ind > 0)
    {
        mapp.An_size = *ind + 1;
        mapp.An = arr;
    }
    else
    {
        mapp.An_size = 0;
    }
    //cout << "An size " << mapp.An_size << endl;
    //mapp.printAnTree();
    
    delete [] arr;
    
}

void Construct_Array_Tree1(MainApp &mapp)
{
    
    ArrNode an;
    int size = 6 + mapp.Particles1.size()*4;
    
    
    //cout << "SIZZEE " << size << endl;
    //cout <<
    
    ArrNode* arr = NULL;
    arr = new ArrNode[size]();
    
    //ArrNode arr[size];
    
    int st = 0;
    int* ind = &st;
    
    an.toArr(*mapp.Root1, arr,0,ind);
    
    if(*ind > 0)
    {
        mapp.An_size1 = *ind + 1;
        mapp.An1 = arr;
    }
    else
    {
        mapp.An_size1 = 0;
    }
    //cout << "An size " << mapp.An_size << endl;
    //mapp.printAnTree();
    
    delete [] arr;
    
}

void Construct_Array_Tree2(MainApp &mapp)
{
    
    ArrNode an;
    int size = 6 + mapp.Particles2.size()*4;
    
    
    //cout << "SIZZEE " << size << endl;
    //cout <<
    
    ArrNode* arr = NULL;
    arr = new ArrNode[size]();
    
    //ArrNode arr[size];
    
    int st = 0;
    int* ind = &st;
    
    an.toArr(*mapp.Root2, arr,0,ind);
    
    if(*ind > 0)
    {
        mapp.An_size2 = *ind + 1;
        mapp.An2 = arr;
    }
    else
    {
        mapp.An_size2 = 0;
    }
    //cout << "An size " << mapp.An_size << endl;
    //mapp.printAnTree();
    
    delete [] arr;
    
}

void Builds(MainApp &mapp)
{
    mapp.Root->P_ResetTree();
    
    BuildT(mapp);
    
    mapp.Root->ComputeMassDistribution();
    
    //mapp.Root->printTree();
    
    Construct_Array_Tree(mapp);
    
    //mapp.printAnTree();
    
    //cout << "FORCE SEQ " << mapp.An[0].CalculateForceTree(mapp.An, mapp.An_size, *mapp.Particles[0]) << endl;
    //cout << "FORCE REQ " << mapp.Root->CalculateForceTree(*mapp.Particles[0]) << endl;
    
    
}

void Builds1(MainApp &mapp)
{
    mapp.Root1->P_ResetTree();
    
    BuildT1(mapp);
    
    mapp.Root1->ComputeMassDistribution();
    
    Construct_Array_Tree1(mapp);
    
}

void Builds2(MainApp &mapp)
{
    mapp.Root2->P_ResetTree();
    
    BuildT2(mapp);
    
    mapp.Root2->ComputeMassDistribution();
    
    Construct_Array_Tree2(mapp);
    
}

void Parallel_Calc(MainApp &mapp, int n)
{
    mutex m;
    
    size_t max = n;
    parallel_for(size_t(1), max, [&](size_t i)
    //for(int i=0; i<mapp.Particles.size();i++)
    {
        Particle* part;
        part = mapp.Particles[i];
        
        //part->Force = mapp.Root->CalculateForceTree(*mapp.Particles[i]);
        //cout << "soize " << mapp.An_size << endl;
        //cout << "Index " << i << endl;
        //mapp.printAnTree();
        
        part->Force = mapp.An[0].CalculateForceTree(mapp.An, mapp.An_size, *mapp.Particles[i]);
        //cout << "Before force " << mapp.Particles[i]->Position << endl;
        
        
        part->PartForceCalc(part->Position, part->Force);
        
        //cout << "After force " << mapp.Particles[i]->Position << endl;
        
        //cout << mapp.Root->quad->Size << endl;
        
        
        {
            lock_guard<mutex> lock(m);
            
            //cout << mapp.Particles[i]->Position << endl;
            
             if(mapp.Particles[i]->xCord > mapp.Root->quad->Size || mapp.Particles[i]->xCord < 0)
             {
                 //printf("X OUT OF BOUNDS");
                 delete mapp.Particles[i];
                 mapp.Particles.erase(mapp.Particles.begin()+i);
                 
                 //mapp.Particles[i]->xCord = mapp.Particles[i]->xCord*0.5;
             }
            
             if(mapp.Particles[i]->yCord > mapp.Root->quad->Size || mapp.Particles[i]->yCord < 0)
             {
                 //printf("Y OUT OF BOUNDS");
                 delete mapp.Particles[i];
                 mapp.Particles.erase(mapp.Particles.begin()+i);
                 
                 //mapp.Particles[i]->yCord = mapp.Particles[i]->yCord*0.5;
             }
            
       
            Particle pt = *mapp.Particles[i];
            points.push_back(pt);
    
        }
        
     });
    
}

void Parallel_Calc11(MainApp &mapp, int n)
{
    mutex m;
    
    size_t max = n;
    
    parallel_for(size_t(1), max, [&](size_t i)
    //for(int i=0; i<mapp.Particles1.size();i++)
    {
        //cout << "Particles 11" << mapp.Particles1[i] << endl;
        Particle* part;
        part = mapp.Particles1[i];
         
        //part->Force = mapp.Root->CalculateForceTree(*mapp.Particles[i]);
        part->Force = mapp.An[0].CalculateForceTree(mapp.An1, mapp.An_size1, *mapp.Particles1[i]);

        part->PartForceCalc(part->Position, part->Force);
         
        {
            lock_guard<mutex> lock(m);
            
            if(mapp.Particles1[i]->xCord > mapp.Root->quad->Size || mapp.Particles1[i]->xCord < 0)
            {
                //printf("X OUT OF BOUNDS");
                delete mapp.Particles1[i];
                mapp.Particles1.erase(mapp.Particles1.begin()+i);
            }
             
            if(mapp.Particles1[i]->yCord > mapp.Root->quad->Size || mapp.Particles1[i]->yCord < 0)
            {
                //printf("Y OUT OF BOUNDS");
                delete mapp.Particles1[i];
                mapp.Particles1.erase(mapp.Particles1.begin()+i);
                 
                //mapp.Particles[i]->yCord = mapp.Particles[i]->yCord*0.5;
            }
        }
    });
}

void Parallel_Calc12(MainApp &mapp, int n)
{
    mutex m;
    
    size_t max = n;
    
    parallel_for(size_t(1), max, [&](size_t i)
    //for(int i=0; i<mapp.Particles.size();i++)
    {
        Particle* part;
        part = mapp.Particles2[i];
         
        //part->Force = mapp.Root->CalculateForceTree(*mapp.Particles[i]);
        part->Force = mapp.An[0].CalculateForceTree(mapp.An1, mapp.An_size1, *mapp.Particles2[i]);
         
        part->PartForceCalc(part->Position, part->Force);
         
        {
            lock_guard<mutex> lock(m);
             
            if(mapp.Particles2[i]->xCord > mapp.Root->quad->Size || mapp.Particles2[i]->xCord < 0)
            {
                //printf("X OUT OF BOUNDS");
                delete mapp.Particles2[i];
                mapp.Particles2.erase(mapp.Particles2.begin()+i);
            }
             
            if(mapp.Particles2[i]->yCord > mapp.Root->quad->Size || mapp.Particles2[i]->yCord < 0)
            {
                //printf("Y OUT OF BOUNDS");
                delete mapp.Particles2[i];
                mapp.Particles2.erase(mapp.Particles2.begin()+i);
                 
                //mapp.Particles[i]->yCord = mapp.Particles[i]->yCord*0.5;
            }
        }
    });
}

void Parallel_Calc21(MainApp &mapp, int n)
{
    mutex m;
    
    size_t max = n;
    
    parallel_for(size_t(1), max, [&](size_t i)
    //for(int i=0; i<mapp.Particles.size();i++)
    {
        Particle* part;
        part = mapp.Particles1[i];
         
        //part->Force = mapp.Root->CalculateForceTree(*mapp.Particles[i]);
        part->Force = mapp.An[0].CalculateForceTree(mapp.An2, mapp.An_size2, *mapp.Particles1[i]);
         
        part->PartForceCalc(part->Position, part->Force);
         
        {
            lock_guard<mutex> lock(m);
             
            if(mapp.Particles1[i]->xCord > mapp.Root->quad->Size || mapp.Particles1[i]->xCord < 0)
            {
                //printf("X OUT OF BOUNDS");
                delete mapp.Particles1[i];
                mapp.Particles1.erase(mapp.Particles1.begin()+i);
            }
             
            if(mapp.Particles1[i]->yCord > mapp.Root->quad->Size || mapp.Particles1[i]->yCord < 0)
            {
                //printf("Y OUT OF BOUNDS");
                delete mapp.Particles1[i];
                mapp.Particles1.erase(mapp.Particles1.begin()+i);
                 
                //mapp.Particles[i]->yCord = mapp.Particles[i]->yCord*0.5;
            }
        }
    });
}

void Parallel_Calc22(MainApp &mapp, int n)
{
    mutex m;
    
    size_t max = n;
    
    parallel_for(size_t(1), max, [&](size_t i)
    //for(int i=0; i<mapp.Particles2.size();i++)
    {
        Particle* part;
        part = mapp.Particles2[i];
        
        //part->Force = mapp.Root->CalculateForceTree(*mapp.Particles[i]);
        part->Force = mapp.An[0].CalculateForceTree(mapp.An2, mapp.An_size2, *mapp.Particles2[i]);
        
        part->PartForceCalc(part->Position, part->Force);
        
        {
            lock_guard<mutex> lock(m);
             
            if(mapp.Particles2[i]->xCord > mapp.Root->quad->Size || mapp.Particles2[i]->xCord < 0)
            {
                //printf("X OUT OF BOUNDS");
                delete mapp.Particles2[i];
                mapp.Particles2.erase(mapp.Particles2.begin()+i);
            }
             
            if(mapp.Particles2[i]->yCord > mapp.Root->quad->Size || mapp.Particles2[i]->yCord < 0)
            {
                //printf("Y OUT OF BOUNDS");
                delete mapp.Particles2[i];
                mapp.Particles2.erase(mapp.Particles2.begin()+i);
                 
                //mapp.Particles[i]->yCord = mapp.Particles[i]->yCord*0.5;
            }
        }
    });
}

void Fill_Vec1(MainApp &mapp, int n)
{
    size_t max = n;
    mutex m;
    
    parallel_for(size_t(1), max, [&](size_t i)
    {
        {
            lock_guard<mutex> lock(m);
            Particle pt = *mapp.Particles1[i];
            points.push_back(pt);
        }
    });
}

void Fill_Vec2(MainApp &mapp, int n)
{
    size_t max = n;
    mutex m;
    
    parallel_for(size_t(1), max, [&](size_t i)
                 {
                     {
                         lock_guard<mutex> lock(m);
                         Particle pt = *mapp.Particles2[i];
                         points.push_back(pt);
                     }
                 });
}

void Calcs(MainApp &mapp)
{
    points.clear();
    
    
    //Parallel_Calc(mapp, mapp.Particles.size());
    
    
    thread pc11(Parallel_Calc11,ref(mapp),mapp.Particles1.size());
    thread pc22(Parallel_Calc22,ref(mapp),mapp.Particles2.size());
    
    pc11.join();
    pc22.join();
    
    thread pc12(Parallel_Calc12,ref(mapp),mapp.Particles2.size());
    thread pc21(Parallel_Calc21,ref(mapp),mapp.Particles1.size());
    
    pc12.join();
    pc21.join();
    
    thread fv1(Fill_Vec1,ref(mapp),mapp.Particles1.size());
    fv1.join();
    thread fv2(Fill_Vec2,ref(mapp),mapp.Particles2.size());
    fv2.join();
    
	//cout << "POSITION MOD " << points[mapp.Particles.size()-1].Position <<endl;
	//cout << points[mapp.Particles.size()-1].xCord << ":";
	//cout << points[mapp.Particles.size()-1].yCord << endl;
	//cout << "size " << points.size() << endl;
}

void BuildAll(MainApp &mapp)
{
    thread b1(Builds1,ref(mapp));
    thread b2(Builds2,ref(mapp));
    
    b1.join();
    b2.join();
}


void Task_Parallel(MainApp& mapp)
{
    //Builds(mapp);
    BuildAll(mapp);
    Calcs(mapp);
    
}

void glutTimer_(int value)
{
    
    Task_Parallel(*mapp);
    
    //cout << "TIMER" <<endl;
    glutPostRedisplay();
    glutTimerFunc(30, glutTimer_,1);
    
}

int main(int argc, char** argv)
{
	int ScreenSize = 0;
	
	one = 2000;
	two = 3000;
	size = 100;
	
	
	MainApp mapp2(one,two);
	
	mapp = &mapp2;
    
    BuildAll(*mapp);
    
    Calcs(*mapp);
	
	ScreenSize = size*100;
	
	glutInit(&argc, argv);
	glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize (ScreenSize, ScreenSize); 
	glutInitWindowPosition (100, 100);
	glutCreateWindow ("hello");
	

	glutDisplayFunc(display); 
	
	glutTimerFunc( 30, glutTimer_, 1);
	
	glutMainLoop();
	
	return 0;
}





