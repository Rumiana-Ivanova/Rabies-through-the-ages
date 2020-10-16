#ifndef CHUMAN_H
#define CHUMAN_H

#include "CBehavior.h"

class CHuman : public CBehavior
{
    public:
        CHuman();
        virtual ~CHuman();
        CHuman(CSimulation* simulation);
        virtual void generate_map(CSimulation* simulation);
        virtual void choose_direction(CActor* actor);
        //virtual void update(vector<CHuman*>& actors) {};
};

extern CBehavior* g_pHuman;
#endif // CHUMAN_H
