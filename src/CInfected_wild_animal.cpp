#include "CInfected_wild_animal.h"
#include "CActor.h"
#include "CSimulation.h"
#include "CMovement.h"
#include "CTargeted_movement.h"
#include "CIdle_movement.h"
#include <vector>
#include <iostream>

CBehavior* g_pInfected_wild_animal;


CInfected_wild_animal::~CInfected_wild_animal()
{
    //dtor
}

CInfected_wild_animal::CInfected_wild_animal(CSimulation* simulation) :CBehavior(simulation)
{
    if (pictures) {
        m_img_file = "img\\fox.bmp";
    }
    else {
        m_img_file = "img\\wild_animal.bmp";
    }
}

void CInfected_wild_animal::generate_map(CSimulation* simulation) {


    for (int i = 0; i < simulation->size; i++) {
        if (simulation->map[i] == 'r') {
            cost_map[i] = 10;
        }
        else if (simulation->map[i] == 'c') {
            cost_map[i] = 20;
        }
        else if (simulation->map[i] == 'g') {
            cost_map[i] = 2;
        }
        else if (simulation->map[i] == 'f') {
            cost_map[i] = 1;
        }
        else if (simulation->map[i] == 'w') {
            cost_map[i] = -2;
        }
        else if (simulation->map[i] == 't') {
            cost_map[i] = -2;
        }
        else {
            cost_map[i] = -2;
        }

    }
}

void CInfected_wild_animal::generate_time_distribution(CActor* actor, CSimulation* simulation) {
    actor->m_time_of_infection = simulation->time;
    actor->m_incubation_period  = actor->m_time_of_infection   + (simulation->animals_wild_incubation_period   + rand() % simulation->animals_wild_incubation_period_fluctuation) * simulation->ticks_per_day;
    actor->m_symptoms_period    = actor->m_incubation_period   + (simulation->animals_wild_first_symptoms      + rand() % simulation->animals_wild_first_symptoms_fluctuation)    * simulation->ticks_per_day;
    actor->m_illness_period     = actor->m_symptoms_period     + (simulation->animals_wild_death_time          + rand() % simulation->animals_wild_death_time_fluctuation)        * simulation->ticks_per_day;
}
int CInfected_wild_animal::illness_stage(CActor* actor, CSimulation* simulation) {

    int time_passed = simulation->time - actor->m_time_of_infection;

    if (time_passed <= simulation->animals_incubation_period) {
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

void CInfected_wild_animal::choose_direction(CActor* actor) {
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

    g_pIdle_movement->move(actor);

}

void CInfected_wild_animal::infection(CActor* this_actor, vector<CActor*>& actors, CSimulation* simulation) {

    vector <CActor*> actors_in_infection_distance = this_actor->find_actors_in_set_distance(simulation->infection_range, actors);

    int infection_rate = 1;
    int sz = actors_in_infection_distance.size();

    for (int i = 0; i < sz; i++) {
        CActor* other = actors_in_infection_distance[i];
        if (other->m_behavior == g_pAnimal) {
            infection_rate = simulation->animals_infection_rate;
        }
        else if (other->m_behavior == g_pHuman) {
            infection_rate = simulation->human_infection_rate;
        }
        else if (other->m_behavior == g_pWild_animal) {
            infection_rate = simulation->animals_wild_infection_rate;
        }

        if ((rand() % 100) < infection_rate) {

            other->m_infected = true;
            if (other->m_behavior == g_pHuman) {
                other->m_behavior = g_pInfected_human;
            }
            else if (other->m_behavior == g_pAnimal) {
                other->m_behavior = g_pInfected_animal;
            }
            else if (other->m_behavior == g_pWild_animal) {
                other->m_behavior = g_pInfected_wild_animal;
            }

            generate_time_distribution(other, simulation);
        }

    }

}


