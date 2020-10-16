#include "CIdle_movement.h"
#include "CTargeted_movement.h"
#include "CMovement.h"
#include "CActor.h"
#include "CSimulation.h"
#include "CBehavior.h"

CIdle_movement* g_pIdle_movement;


void CIdle_movement::move(CActor* actor) {
	
	vector<int> neighbors;
	int tile = actor->m_x_current + actor->m_y_current * actor->m_simulation->size_horizontal;

	get_neighbors(neighbors, tile, actor->m_simulation, actor->m_behavior);
	int sz = neighbors.size();
	int r = rand() % sz;
	
	int chance;
	char pos_next;

	if ((actor->m_behavior == g_pHuman) &&(actor->m_behavior == g_pInfected_human)) {
		while (true) {
			r = rand() % sz;
			pos_next = actor->m_simulation->map[neighbors[r]];

			chance = rand() % 100;
			if ((pos_next != 'w') && (pos_next != 'o')) {

				if (chance < 40) {
					if (pos_next == 'r') {
						break;
					}
				}else if (chance < 60) {
					if (pos_next == 'c') {
					break;
					}
				}
				else if (chance < 80) {
					if (pos_next == 'g') {
						break;
					}
				}
				else if (chance < 90){ 
					if (pos_next == 't') {
						break;
					}
				}else if(pos_next == 'f') {
					break;
				}
			}
		}

	} else if ((actor->m_behavior == g_pAnimal) && (actor->m_behavior == g_pInfected_animal)) {
		while (true) {
			r = rand() % sz;
			pos_next = actor->m_simulation->map[neighbors[r]];

			chance = rand() % 100;
			if ((pos_next != 'w') && (pos_next != 'o')) {

				if (chance < 40) {
					if (pos_next == 'g') {
						break;
					}
				}

				else if (chance < 60) {
					if (pos_next == 'f') {
						break;
					}
				}
				else if (chance < 80) {
					if (pos_next == 'r') {
						break;
					}
				}
				else if (chance < 95) {
					if (pos_next == 'c') {
						break;
					}
				}
				else if (pos_next == 't') {
					break;

				}
			}
		}

	}
	else if ((actor->m_behavior == g_pWild_animal) && (actor->m_behavior == g_pInfected_wild_animal)) {
		while (true) {
			r = rand() % sz;
			pos_next = actor->m_simulation->map[neighbors[r]];

			chance = rand() % 100;
			if ((pos_next != 'w') && (pos_next != 'o')) {

				if (chance < 50) {
					if (pos_next == 'f') {
						break;
					}
				}
				else if (chance < 80) {
					if (pos_next == 'g') {
						break;
					}
				}
				else if (chance < 90) {
					if (pos_next == 'r') {
						break;
					}
				}
				else if (chance < 95) {
					if (pos_next == 'c') {
						break;
					}
				}
				else if (pos_next == 't') {
					break;

				}
			}
		}

	}
	

	actor->m_x_next = neighbors[r] % actor->m_simulation->size_horizontal;
	actor->m_y_next = neighbors[r] / actor->m_simulation->size_horizontal;

}