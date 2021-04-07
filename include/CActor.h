#ifndef CACTOR_H
#define CACTOR_H

#include <vector>
#include <cstdlib>
#include <time.h>
#include <string>
#include "SDL2/SDL.h"
using namespace std;

class CBehavior;
class CSimulation;
class CMovement;


class CActor
{
    public:
        CActor();
        virtual ~CActor();
        virtual void update(vector<CActor*>& actors);
        ///връща актьорите които са на разстояние distance
        virtual vector <CActor*> find_actors_in_set_distance(int distance, vector<CActor*>& vector_of_actors);
        ///валидни ли са за преместване бъдещите координати?
        virtual bool can_move_to(vector<CActor*>& actors);
        virtual void init(SDL_Renderer* pRenderer, int x, int y, CBehavior* behavior, bool infected, CSimulation* simulation);
        virtual void draw(int i);

        int get_x_current();
        int get_y_current();




        CSimulation* m_simulation;
        int m_x_current;
        int m_y_current;
        int m_x_next;
        int m_y_next;
        bool m_alive = true;
        bool m_infected = false;

        int m_time_of_infection = 0;
        int m_incubation_period;
        int m_symptoms_period;
        int m_illness_period;
        int m_afk_count = 0;

        CBehavior* m_behavior;

        int m_red = 255;
        int m_green = 255;
        int m_blue = 255;

    protected:
        SDL_Renderer*   m_pRenderer;
        SDL_Texture*    m_pTexture;
        SDL_Rect        m_rPosition;
        SDL_Rect        m_rAnimation;

        int m_img_height = 10;
        int m_img_width = 10;

};

#endif // CACTOR_H
