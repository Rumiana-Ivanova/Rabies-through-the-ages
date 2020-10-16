#include "CHuman.h"
#include "CActor.h"
#include "CSimulation.h"
#include "CMovement.h"
#include "CTargeted_movement.h"
#include "CIdle_movement.h"
#include <vector>
#include <iostream>

#include "SDL2/SDL.h"

using namespace std;


CBehavior* g_pHuman;


CHuman::~CHuman()
{
    //dtor
}

CHuman::CHuman(CSimulation* simulation) :CBehavior(simulation)
{
    if (pictures) {
        m_img_file = "img\\boy.bmp";
    }
    else {
        m_img_file = "img\\human.bmp";
    }
}

void CHuman::generate_map(CSimulation* simulation) {

    for (int i = 0; i < simulation->size; i++) {
        if (simulation->map[i] == 'r'){
            cost_map[i] = 1;
        }else if (simulation->map[i] == 'c') {
            cost_map[i] = 3;
        }
        else if (simulation->map[i] == 'g') {
            cost_map[i] = 10;
        }
        else if (simulation->map[i] == 'f') {
            cost_map[i] = 20;
        }
        else if (simulation->map[i] == 'w') {
            cost_map[i] = -2;
        }
        else if (simulation->map[i] == 't') {
            cost_map[i] = 0;
        }
        else  {
            cost_map[i] = -2;
        }
        
       
    }

}

void CHuman::choose_direction(CActor* actor) {

    char a = actor->m_simulation->map[actor->get_y_current()*actor->m_simulation->size_horizontal + actor->get_x_current()];
    ///SDL_assert(((a != 'w') && (a != 'f') && (a != 'g') && (a != 'o')));
    
    int pos = actor->get_x_current() + actor->get_y_current() * actor->m_simulation->size_horizontal;

    g_pIdle_movement->move(actor);
    
    
}