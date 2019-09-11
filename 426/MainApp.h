#ifndef MAINAPP_H
#define MAINAPP_H

#include "ArrNode.h"

class MainApp
{
	public:
	
	//Constructor
	MainApp(int galaxy1, int galaxy2); 
	
	//Mehtods
	void BuildTree(MainApp& mapp);
	void CalcForce(MainApp& mapp);
    void CalcMass();
	void printParticles();
	
    void printTree();
    void printTree1();
    void printTree2();
    
    void printAnTree();
    void printAnTree1();
    void printAnTree2();
	
	TreeNode* Root;
    TreeNode* Root1;
    TreeNode* Root2;
    
    ArrNode* An;
    ArrNode* An1;
    ArrNode* An2;
    
    int An_size;
    int An_size1;
    int An_size2;
    
    vector<Particle*> Particles;
    vector<Particle*> Particles1;
    vector<Particle*> Particles2;
    
    
};

#endif

