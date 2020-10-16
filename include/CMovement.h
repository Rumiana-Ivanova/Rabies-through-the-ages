#ifndef CHMOVEMENT_H
#define CHMOVEMENT_H
#include <vector>
using namespace std;

class CActor;
class CSimulation;
class CBehavior;

class CMovement
{
public:
	virtual void move(CActor* actor) {};
	void get_neighbors(vector<int>& neighbors, int a, CSimulation* simulation, CBehavior* behavior);
};



#endif