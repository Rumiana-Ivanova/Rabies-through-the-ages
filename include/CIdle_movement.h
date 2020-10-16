#ifndef IDLE_MOVEMENT_H
#define IDLE_MOVEMENT_H

#include "CMovement.h"
#include <fstream>
#include <vector>
#include <iostream>
#include <cmath>
using namespace std;


class CIdle_movement : public CMovement
{
	public:
		virtual void move(CActor* actor);

		int field[102*102];
};
extern CIdle_movement* g_pIdle_movement;
#endif // !TARGETED_MOVEMENT_H
