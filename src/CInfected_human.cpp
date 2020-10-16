#include "CInfected_human.h"
#include "CActor.h"
#include "CSimulation.h"
#include "CMovement.h"
#include "CTargeted_movement.h"
#include "CIdle_movement.h"
#include <vector>
#include <iostream>

using namespace std;

CBehavior* g_pInfected_human;


CInfected_human::CInfected_human(CSimulation* simulation) :CBehavior(simulation)
{
    if (pictures) {
        m_img_file = "img\\boy.bmp";
    }
    else {
        m_img_file = "img\\human.bmp";
    }
}

CInfected_human::~CInfected_human()
{
    //dtor
}


void CInfected_human:: generate_map(CSimulation* simulation) {

    for (int i = 0; i < simulation->size; i++) {
        if (simulation->map[i] == 'r'){
            cost_map[i] = 1;
        }
		else if (simulation->map[i] == 'c') {
            cost_map[i] = 2;
        }
        else if (simulation->map[i] == 'g') {
            cost_map[i] = 10;
        }
        else if (simulation->map[i ] == 'f') {
            cost_map[i] = 20;
        }
        else if (simulation->map[i] == 'w') {
            cost_map[i] = -2;
			///add close to whater pixels!!!
        }
        else if (simulation->map[i] == 't') {
            cost_map[i] = 30;
        }
        else  {
            cost_map[i] = -2;
        }    
       
    }
}

void CInfected_human::choose_direction(CActor* actor) {
    int tile;

    if (illness_stage(actor, actor->m_simulation) >= symptoms) {
         
        for (int i = -1; i < 2; i++) {
            for (int j = -1; j < 2; j++) {
                tile = actor->get_x_current() + i + (actor->get_y_current() + j) * actor->m_simulation->size_horizontal;
                if (actor->m_simulation->map[tile] == 'w') {
                    return;
                }
            }
        }

    }

    int pos = actor->get_x_current() + actor->get_y_current() * actor->m_simulation->size_horizontal;

    ///if(actor->m_behavior->illness_stage(actor, actor->m_simulation) > shedding){

        if (g_pTargeted_movement->field[pos] != 0) {
            g_pTargeted_movement->move(actor);
        }
        else {
            g_pTargeted_movement->in_destination(actor);
        }

    ///}
    ///else {g_pIdle_movement->move(actor);}
  

}

void CInfected_human::generate_time_distribution(CActor* actor, CSimulation* simulation) {

    actor->m_time_of_infection = simulation->time;
    actor->m_incubation_period = actor->m_time_of_infection + (simulation->human_incubation_period + rand() % simulation->human_incubation_period_fluctuation) * simulation->ticks_per_day;
    actor->m_symptoms_period   = actor->m_incubation_period + (simulation->human_first_simptoms    + rand() % simulation->human_first_simptoms_fluctuation)    * simulation->ticks_per_day;
    actor->m_illness_period    = actor->m_symptoms_period   + (simulation->human_death_time        + rand() % simulation->human_death_time_fluctuation)        * simulation->ticks_per_day;

}
int CInfected_human::illness_stage(CActor* actor, CSimulation* simulation) {

    int time_passed = simulation->time - actor->m_time_of_infection;

    if (time_passed <= simulation->human_incubation_period) {
        return infected;
    }
    else if (time_passed <= actor->m_incubation_period) {
        return incubation;
    }
    else if (time_passed <= actor->m_symptoms_period) {
        return shedding;
    }
    else if (time_passed <= actor->m_illness_period) {
        return symptoms;
    }
    else {
        return death;
    }
    return uninfected;
}


