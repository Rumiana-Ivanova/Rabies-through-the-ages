#include "CTargeted_movement.h"
#include "CMovement.h"
#include "CActor.h"
#include "CSimulation.h"
#include "CBehavior.h"

CTargeted_movement* g_pTargeted_movement;

bool CTargeted_movement::is_the_wave_complete(CSimulation* simulation) {

	for (int i = 0; i < simulation->size; i++) {
		if (field[i] == -1) {
			return false;
		}
	}
	return true;

}



void CTargeted_movement::wave(CSimulation* simulation, CBehavior* behavior) {

	vector<int> front1;
	vector<int> front2;
	vector<int> tmp;

	for (int i = 0; i < simulation->size; i++) {
		if (simulation->map[i] == 't') {
			field[i] = 0;
			front1.push_back(i);
		}
		else {
			field[i] = -1;
		}
	}
	
	int sz, s;
	int price;
	bool wave = true;

	while (wave) {
		
		wave = false;
		sz = front1.size();
		//cout << endl << sz << endl;
		for (int i = 0; i < sz; i++) {
			get_neighbors(tmp, front1[i], simulation, behavior);
			s = tmp.size();
			for (int j = 0; j < s; j++) {
				SDL_assert(tmp[j] < simulation->size);
				price = field[front1[i]] + behavior->cost_map[tmp[j]];
				if (field[tmp[j]] < 0 || price < field[tmp[j]]) {
					field[tmp[j]] = price;
					front2.push_back(tmp[j]);
					wave = true;
				}
			}
			tmp.clear();

		}
		
		swap(front1, front2);
		front2.clear();

	}


}

void CTargeted_movement::print(ostream& file) {

	for (int i = 0; i < 102; i++) {
		for (int  j= 0; j < 102; j++) {
			if (field[i * 102 + j] == -1) {
				file << "-----";
			}
			else if (field[i * 102 + j] == 0) {
				file << "#####";
			}
			else {
				file << " " << int(field[i * 102 + j]);
			}
		}
		file << endl;
	}
}


void CTargeted_movement::move(CActor* actor) {

	int x = actor->get_x_current();
	int y = actor->get_y_current();
	vector<int> neighbors;
	get_neighbors(neighbors, x + actor->m_simulation->size_horizontal * y, actor->m_simulation, actor->m_behavior);

	int sz = neighbors.size();

	if (sz > 0) {
		int min = field[neighbors[0]];
		int min_index = 0;

		for (int i = 1; i < sz; i++) {
			if (field[neighbors[i]] < min) {
				min = field[neighbors[i]];
				min_index = i;
			}
		}

		actor->m_x_next = neighbors[min_index] % actor->m_simulation->size_horizontal;
		actor->m_y_next = neighbors[min_index] / actor->m_simulation->size_horizontal;

	}
	

}

void CTargeted_movement::in_destination(CActor* actor) {
	int r;
	vector<int> tmp;
	int x = actor->get_x_current();
	int y = actor->get_y_current();
	while (true) {
		get_neighbors(tmp, x+y*actor->m_simulation->size_horizontal, actor->m_simulation, actor->m_behavior);
		if (tmp.empty()) {
			return;
		}
		r = rand() % tmp.size();
		if (field[tmp[r]] == 0) {
			break;
		}
	}

	actor->m_x_next = tmp[r] % actor->m_simulation->size_horizontal;
	actor->m_y_next = tmp[r] / actor->m_simulation->size_horizontal;

	if ((actor->m_simulation->era == CSimulation::Era::ModernDay) && 
		(actor->m_behavior->illness_stage(actor, actor->m_simulation) < CBehavior::IllnessStage::symptoms)) {
		
		actor->m_infected = false;
		actor->m_behavior->stage_to_color(actor, CBehavior::IllnessStage::uninfected);
		if (actor->m_behavior == g_pInfected_human) {
			actor->m_behavior = g_pHuman;
		}
	}

	if ((actor->m_simulation->era == CSimulation::Era::ClassicalAntiquity) &&
		(actor->m_behavior->illness_stage(actor, actor->m_simulation) < CBehavior::IllnessStage::infected)) {

		actor->m_infected = false;
		actor->m_behavior->stage_to_color(actor, CBehavior::IllnessStage::uninfected);
		if ((rand() % 100 < 33) && (actor->m_behavior == g_pInfected_human)) {
			actor->m_behavior = g_pHuman;
		}
		
	}
}