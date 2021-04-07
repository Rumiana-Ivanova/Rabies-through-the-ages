#ifndef CINFECTED_WILD_ANIMAL_H
#define CINFECTED_WILD_ANIMAL_H

#include "CBehavior.h"


class CInfected_wild_animal :
    public CBehavior
{
public:
	CInfected_wild_animal();
	virtual ~CInfected_wild_animal();
	CInfected_wild_animal(CSimulation* simulation);
	virtual void choose_direction(CActor* actor);
	virtual void infection(CActor* this_actor, vector<CActor*>& actors, CSimulation* simulation);
	virtual void generate_time_distribution(CActor* actor, CSimulation* simulation);
	virtual int illness_stage(CActor* actor, CSimulation* simulation);
	virtual void generate_map(CSimulation* simulation);



};

extern CBehavior* g_pInfected_wild_animal;



#endif
