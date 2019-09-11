#ifndef TREENODE_H
#define TREENODE_H

#include "Quadrant.h"
#include"Opperator.h"
#include </usr/local/Cellar/tbb/2018_U5/include/tbb/task_group.h>

class TreeNode
{
	public:
	
	//Constructor
	TreeNode();
	TreeNode(int size);
	TreeNode(TreeNode const &parent);
	
	//Destructor
	~TreeNode();
	
	//Methods
	void createSubNode(int quad);
	TreeNode* SubNode(int quad); 
	void P_ResetTree();
	void ResetTree();
	int getQuadrant(Particle n_particle);
	void setQuadrant(int sector);
	void InsertToNode(Particle &n_Particle);
	void ComputeMassDistribution();
	string CalculateForceTree(Particle &particle);
	void printTree();
	
	TreeNode* Parent;
	TreeNode* NW;
	TreeNode* NO;
	TreeNode* SW;
	TreeNode* SO;
	Quadrant* quad;
	Particle* part;
	int height;
	int tot_particles;	
	int child_particles;
	int Mass;
    int below;
	string CenterOfMass;
		

};

#endif
