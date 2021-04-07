#ifndef CINFECTED_HUMAN_H
#define CINFECTED_HUMAN_H

#include "CBehavior.h"

class CInfected_human : public CBehavior
{
	public:
		CInfected_human();
		CInfected_human(CSimulation* simulation);
		virtual ~CInfected_human();
		virtual void choose_direction(CActor* actor);
		virtual void generate_time_distribution(CActor* actor, CSimulation* simulation);
		virtual int illness_stage(CActor* actor, CSimulation* simulation);
		virtual void generate_map(CSimulation* simulation);
};

extern CBehavior* g_pInfected_human;

#endif
