#ifndef CANIMAL_H
#define CANIMAL_H

#include "CBehavior.h"

class CAnimal : public CBehavior
{
public:
	CAnimal();
	CAnimal(CSimulation* simulation);
	virtual ~CAnimal();
	virtual void generate_map(CSimulation* simulation);
	virtual void choose_direction(CActor* actor);
};

extern CBehavior* g_pAnimal;

#endif CANIMAL_H
