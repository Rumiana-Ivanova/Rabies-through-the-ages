#include "CBehavior.h"
#include"CActor.h"
#include<CSimulation.h>

CBehavior::CBehavior(CSimulation* simulation)
{
	pictures = simulation->pictures;
    
}

CBehavior::~CBehavior()
{
    //dtor
}
void CBehavior::choose_direction(CActor* actor) {

}

void CBehavior::color_change(CActor* actor, int c) {

    actor->m_red = c;
    actor->m_green = c;
    actor->m_blue = c;

}

void CBehavior::stage_to_color(CActor* actor, IllnessStage stage) {

	switch (stage)
	{
	case CBehavior::uninfected:		 actor->m_behavior->color_change(actor, 255);
		break;
	case CBehavior::infected:		actor->m_behavior->color_change(actor, 232);
		break;
	case CBehavior::incubation:		actor->m_behavior->color_change(actor, 191);
		break;
	case CBehavior::shedding:       actor->m_behavior->color_change(actor, 159);
		break;
	case CBehavior::symptoms:		 actor->m_behavior->color_change(actor, 127);
		break;
	case CBehavior::death:			 actor->m_behavior->color_change(actor, 95);
		break;
	default:						actor->m_behavior->color_change(actor, 255);
		break;
	}

}

