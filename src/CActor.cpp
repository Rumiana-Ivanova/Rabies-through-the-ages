#include <cmath>
#include <iostream>
using namespace std;

#include "CActor.h"
#include "CBehavior.h"
#include "CSimulation.h"
#include "CMovement.h"
#include "CTargeted_movement.h"


CActor::CActor()
{
    //ctor
}

CActor::~CActor()
{
    //dtor
}

vector<CActor*> CActor::find_actors_in_set_distance(int distance, vector<CActor*>& vector_of_actors){

    vector<CActor*> actors_in_the_distance;
    int sz = vector_of_actors.size();
    for (int i=0; i<sz; i++){
        double d = hypot(vector_of_actors[i]->m_x_current - m_x_current, vector_of_actors[i]->m_y_current - m_y_current);
        if(d > 0.01 && d <= distance){
            actors_in_the_distance.push_back(vector_of_actors[i]);
        }
    }

    return actors_in_the_distance;

}

void CActor::init (SDL_Renderer* pRenderer, int x, int y, CBehavior* behavior, bool infected, CSimulation* simulation){

    m_pRenderer = pRenderer;
    //

    SDL_Surface* pTmp = NULL;

    pTmp = SDL_LoadBMP(behavior->m_img_file.c_str());
    m_pTexture = SDL_CreateTextureFromSurface(m_pRenderer, pTmp);
    SDL_SetTextureColorMod(m_pTexture, m_red, m_green, m_blue);
    SDL_FreeSurface(pTmp);

    m_simulation = simulation;
    m_behavior = behavior;
    m_infected = infected;
    if (m_infected) {
        m_time_of_infection = simulation->time;
        m_behavior->generate_time_distribution(this, m_simulation);
    }

    m_x_current = x;
    m_y_current = y;
    m_x_next = m_x_current;
    m_y_next = m_y_current;

    m_rPosition.x = m_x_current * m_img_width;
    m_rPosition.y = m_y_current * m_img_height;
    m_rPosition.h = m_img_height;
    m_rPosition.w = m_img_width;

    char tile = m_simulation->map[x + m_simulation->size_horizontal * y];   

}


bool CActor::can_move_to(vector<CActor*>& actors){

    m_behavior->choose_direction(this);


    if ((m_x_next >= m_simulation->size_horizontal) || (m_y_next >= m_simulation->size_vertical) || (m_x_next < 0) || (m_y_next < 0)) {
        return false;
    }

    int sz = actors.size();
    for (int i=0; i<sz; i++){
        if((m_x_next==actors[i]->m_x_current)&&(m_y_next==actors[i]->m_y_current)){
            return false;
        }
    }   
    return true;

}

int CActor::get_x_current(){
    return m_x_current;
}
int CActor::get_y_current(){
    return m_y_current;
}

void CActor::update(vector<CActor*>& actors){


    if (m_behavior->illness_stage(this, m_simulation) > 1) {
        m_behavior->infection(this, actors, m_simulation);
    }

    if (m_infected) {

        m_behavior->illness_stage(this, m_simulation);

        if (m_behavior->illness_stage(this, this->m_simulation) == 4) {
            m_alive = false;
        }
    }

    if(can_move_to(actors)){
        m_afk_count = 0;
        m_x_current=m_x_next;
        m_y_current=m_y_next;
    }else{
        m_afk_count++;
        m_x_next=m_x_current;
        m_y_next=m_y_current;
    }


}
void CActor::draw(int i) {

    if (m_infected) {
        m_behavior->stage_to_color(this, (CBehavior::IllnessStage)(m_behavior->illness_stage(this, m_simulation)));
    }

    if (m_alive) {

        SDL_Surface* pTmp = NULL;

        int r = m_x_current + m_y_current * m_simulation->size_horizontal;

        SDL_SetTextureColorMod(m_pTexture, m_red, m_green, m_blue);

        //if (i != 13) return;
        m_rPosition.x = (m_x_current)*m_img_width;
        m_rPosition.y = (m_y_current)*m_img_height;
        SDL_RenderCopy(m_pRenderer, m_pTexture, NULL, &m_rPosition);
    }
}