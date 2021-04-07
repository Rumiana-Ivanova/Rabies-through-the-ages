#ifndef CINFECTED_ANIMAL_H
#define CINFECTED_ANIMAL_H

#include "CBehavior.h"
class CInfected_animal : public CBehavior
{
public:
	CInfected_animal();
	CInfected_animal(CSimulation* simulation);
	virtual ~CInfected_animal();
	virtual void choose_direction(CActor* actor);
	virtual void infection(CActor* this_actor, vector<CActor*>& actors, CSimulation* simulation);
	virtual void generate_time_distribution(CActor* actor, CSimulation* simulation);
	virtual int illness_stage(CActor* actor, CSimulation* simulation);
	virtual void generate_map(CSimulation* simulation);

};

extern CBehavior* g_pInfected_animal;

#endif
