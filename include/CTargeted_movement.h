#ifndef TARGETED_MOVEMENT_H
#define TARGETED_MOVEMENT_H

#include "CMovement.h"
#include <fstream>
#include <vector>
#include <iostream>
using namespace std;


class CTargeted_movement : public CMovement
{
	public:
		virtual void wave(CSimulation* simulation, CBehavior* behavior);
		bool is_the_wave_complete(CSimulation* simulation);
		void in_destination(CActor* actor);
		void print(ostream& file);
		virtual void move(CActor* actor);

		int field[102*102];
};
extern CTargeted_movement* g_pTargeted_movement;
#endif // !TARGETED_MOVEMENT_H
