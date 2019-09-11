#ifndef ARRNODE_h
#define ARRNODE_h

#include "TreeNode.h"
#include <stack>
class ArrNode
{
    public:
    ArrNode();
    ArrNode(TreeNode& tn);
    
    void toArr(TreeNode& tn, ArrNode arr[], int ind, int* Gi);
    void toStack(stack<TreeNode> s, TreeNode tn);
    void cIndex(int child, int index);
    string CalculateForceTree(ArrNode* arr, int size, Particle &particle);
    void print();
    void printTree(ArrNode an[], int size);
    
    int full = 0;
    
    int index;
    int Pi;
    
    int NWi;
    int NOi;
    int SWi;
    int SOi;
    
    int height;
    int tot_particles;
    int child_particles;
    
    int Qsize;
    int QMass;
    string QCenterOfMass;
    
    int PMass;
    string PCenterOfMass;
    
};


#endif
