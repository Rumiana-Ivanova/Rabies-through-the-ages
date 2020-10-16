#ifndef CBEHAVIOR_H
#define CBEHAVIOR_H
#include <string>
#include <vector>
using namespace std;

class CActor;
class CSimulation;
class CMovement;

class CBehavior
{
public:
	enum IllnessStage {
		uninfected = -1,
		infected = 0,
		incubation = 1,
		shedding = 2,
		symptoms = 3,
		death = 4,
	};

	CBehavior() {}
	CBehavior(CSimulation* simulation);
	virtual ~CBehavior();
	virtual void choose_direction(CActor* actor);
	virtual void can_move_to() {};
	virtual void infection(CActor* this_actor, vector<CActor*>& actors, CSimulation* simulation) {};
	virtual void generate_time_distribution(CActor* actor, CSimulation* simulation) {};
	virtual int illness_stage(CActor* actor, CSimulation* simulation) { return uninfected;}
	virtual void color_change(CActor* actor, int c);
	virtual void generate_map(CSimulation* simulation) = 0;
	void stage_to_color(CActor* actor, IllnessStage stage);
	
	string m_img_file;	
	//bool infected = false;
	int cost_map[102*102];
	bool pictures = false;

protected:
	int m_speed = 1;
};

#endif 