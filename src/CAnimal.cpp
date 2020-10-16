#include "CAnimal.h"
#include "CActor.h"
#include "CSimulation.h"
#include "CMovement.h"
#include "CTargeted_movement.h"
#include "CIdle_movement.h"

CBehavior* g_pAnimal;

CAnimal::CAnimal(CSimulation* simulation) :CBehavior(simulation)
{
    if (pictures) {
        m_img_file = "img\\pig.bmp";
    }
    else {
        m_img_file = "img\\animal.bmp";
    }

}



CAnimal::~CAnimal()
{
	
}
void CAnimal::choose_direction(CActor* actor) {

    int pos = actor->get_x_current() + actor->get_y_current() * actor->m_simulation->size_horizontal;

    g_pIdle_movement->move(actor);

}

void CAnimal:: generate_map(CSimulation* simulation) {

    for (int i = 0; i < simulation->size; i++) {
        if (simulation->map[i] == 'r'){
            cost_map[i] = 10;
        }
		else if (simulation->map[i] == 'c') {
            cost_map[i] = 20;
        }
        else if (simulation->map[i] == 'g') {
            cost_map[i] = 1;
        }
        else if (simulation->map[i ] == 'f') {
            cost_map[i] = 2;
        }
        else if (simulation->map[i] == 'w') {
            cost_map[i] = -2;
        }
        else if (simulation->map[i] == 't') {
            cost_map[i] = -2;
        }
        else  {
            cost_map[i] = -2;
        }
        
       
    }

}
