#include "CMovement.h"
#include "CActor.h"
#include "CSimulation.h"
#include "CBehavior.h"

void CMovement::get_neighbors(vector<int>& neighbors, int a, CSimulation* simulation, CBehavior* behavior) {


	if (behavior->cost_map[a + 1] >= 0) {
		neighbors.push_back(a + 1);
	}
	if (behavior->cost_map[a - 1] >= 0) {
		neighbors.push_back(a - 1);
	}
	if (behavior->cost_map[a + simulation->size_horizontal] >= 0) {
		neighbors.push_back(a + simulation->size_horizontal);
	}
	if (behavior->cost_map[a + simulation->size_horizontal + 1] >= 0) {
		neighbors.push_back(a + simulation->size_horizontal + 1);
	}
	if (behavior->cost_map[a + simulation->size_horizontal - 1] >= 0) {
		neighbors.push_back(a + simulation->size_horizontal - 1);
	}
	if (behavior->cost_map[a - simulation->size_horizontal] >= 0) {
		neighbors.push_back(a - simulation->size_horizontal);
	}
	if (behavior->cost_map[a - simulation->size_horizontal + 1] >= 0) {
		neighbors.push_back(a - simulation->size_horizontal + 1);
	}
	if (behavior->cost_map[a - simulation->size_horizontal - 1] >= 0) {
		neighbors.push_back(a - simulation->size_horizontal - 1);
	}

}

