#ifndef CWILD_ANIMAL_H
#define CWILD_ANIMAL_H

#include "CBehavior.h"

class CWild_animal :   public CBehavior
{
public:
	CWild_animal();
	CWild_animal(CSimulation* simulation);
	virtual ~CWild_animal();
	virtual void generate_map(CSimulation* simulation);
	virtual void choose_direction(CActor* actor);
};

extern CBehavior* g_pWild_animal;

#endif
