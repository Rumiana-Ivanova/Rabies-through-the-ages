#include <iostream>
#include <fstream>
#include <vector>
#include <cstdlib>
#include <time.h>
#include <ctime>
#include <Windows.h>
#include "SDL2/SDL.h"
using namespace std;

#include "CSimulation.h"
#include "CActor.h"
#include "CHuman.h"
#include "CAnimal.h"
#include "CWild_animals.h"
#include "CInfected_human.h"
#include "CInfected_animal.h"
#include "CInfected_wild_animal.h"
#include "CMovement.h"
#include "CTargeted_movement.h"
#include "CIdle_movement.h"

CSimulation::CSimulation(){
    vActors.resize(0);
    //ctor
}
CSimulation::~CSimulation(){
    int sz = vActors.size();
    for(int i=0; i<sz; i++){
        delete vActors[i];
        vActors[i] = NULL;
    }
}

bool CSimulation::end() {
    if ((infected_animals_number == 0) && (infected_humans_number == 0)&& (infected_wild_animals_number == 0)) {
        return true;
    }
    return false;
}

void CSimulation::load(string file_name) {
    ///load -> parameters

    ifstream file (file_name.c_str());
    char temp_name[100];

    file >> temp_name;
    file >> size_vertical;
    file >> temp_name;
    file >> size_horizontal;
    file >> temp_name;
    file >> population_density;
    file >> temp_name;
    file >> infected_humans_percentage;
    file >> temp_name;
    file >> animals_density;
    file >> temp_name;
    file >> infected_animal_percentage;
    file >> temp_name;
    file >> animals_wild_density;
    file >> temp_name;
    file >> infected_wild_animal_percentage;
    file >> temp_name;
    file >> fatality_rate;
    file >> temp_name; 
    file>> ticks_per_day;
    file >> temp_name; 
    file>> human_incubation_period;
    file >> temp_name; 
    file>> human_incubation_period_fluctuation;
    file >> temp_name; 
    file>> human_first_simptoms;
    file >> temp_name; 
    file>> human_first_simptoms_fluctuation;
    file >> temp_name; 
    file>> human_death_time;
    file >> temp_name; 
    file>> human_death_time_fluctuation;
    file >> temp_name; 
    file >> human_infection_rate;
    file >> temp_name;
    file>> animals_wild_incubation_period;
    file >> temp_name; 
    file>> animals_wild_incubation_period_fluctuation;
    file >> temp_name; 
    file>> animals_wild_first_symptoms;
    file >> temp_name; 
    file>> animals_wild_first_symptoms_fluctuation;
    file >> temp_name; 
    file>> animals_wild_death_time;
    file >> temp_name; 
    file>> animals_wild_death_time_fluctuation;
    file >> temp_name;
    file >> animals_wild_infection_rate;
    file >> temp_name; 
    file>> animals_incubation_period;
    file >> temp_name; 
    file>> animals_incubation_period_fluctuation;
    file >> temp_name; 
    file>> animals_first_symptoms;
    file >> temp_name; 
    file>> animals_first_symptoms_fluctuation;
    file >> temp_name; 
    file>> animals_death_time;
    file >> temp_name; 
    file>> animals_death_time_fluctuation;
    file >> temp_name;
    file >> animals_infection_rate;
    file >> temp_name;
    file >> infection_range;
    file >> temp_name;
    file >> era;
    file >> temp_name;
    file >> file_map;
    file >> temp_name;
    file >> pictures;
    file >> temp_name;
    file >> hydrophobia;

    size = size_horizontal * size_vertical;

}

void CSimulation::load_map() {

    ifstream file(("img\\" + file_map + ".tga"), std::ifstream::binary);
    if (!file.is_open()) { 
        cout << "Can't open the file: " << file_map;
    }
  
    char header[18];
    file.seekg(0, ios::beg);
    file.read(header, 18);
    
    file.seekg(12, ios::beg);

    uint16_t width = 0, height = 0;

    file.read((char*)&width, sizeof(width));
    file.read((char*)&height, sizeof(height));

    //cout << width << endl << height << endl;

    char pixel[3];
    unsigned char upixel[3];
    file.seekg(18, ios::beg);

    map.clear();
    map.resize(size, 'o');
    
    int br=0;
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            file.read(pixel, 3);
            upixel[0] = 256 + pixel[0];
            upixel[1] = 256 + pixel[1];
            upixel[2] = 256 + pixel[2];
            br++;
            
            int r = x + y * size_horizontal;
            if ((upixel[2] == 255) && (upixel[1] == 248) && (upixel[0] == 209)) {
                map[r] = 'c';
            }
            else if ((upixel[2] == 128) && (upixel[1] == 128) && (upixel[0] == 128)) {
                map[r] = 'r';    //road
            }
            else if ((upixel[2] == 0) && (upixel[1] == 38) && (upixel[0] == 255)) {
                map[r] = 'w';     //water
            }
            else if ((upixel[2] == 255) && (upixel[1] == 0) && (upixel[0] == 0)) {
                map[r] = 't';;      //temple
            }
            else if ((upixel[2] == 156) && (upixel[1] == 255) && (upixel[0] == 63)) {
                map[r] = 'f';     //forest
            }
            else if ((upixel[2] == 210) && (upixel[1] == 255) && (upixel[0] == 170)) {
                map[r] = 'g';;     //garden
            }

           
        }
       // cout << endl;
    }

    file.close();

}

void CSimulation::print(ostream& file) {
    ///print -> parameters
    /// 
    file << "TIME: " << time << endl << endl;
    file << "infected_humans_number ";
    file << infected_humans_number << endl;
    file << "healthy_humans_number ";
    file << healthy_humans_number << endl;
    file << "infected_humans_percentage ";
    file << infected_humans_percentage << "%" << endl;
    file << "dead_humans_number ";
    file << dead_humans_number << endl;

    file << endl;

    file << "infected_animals_number ";
    file << infected_animals_number << endl;
    file << "healthy_animals_number ";
    file << healthy_animals_number << endl;
    file << "infected_animal_percentage ";
    file << infected_animal_percentage <<"%" << endl;
    file << "dead_animals_number ";
    file << dead_animals_number << endl;

    file << endl;

    file << "infected_wild_animals_number ";
    file << infected_wild_animals_number << endl;
    file << "healthy_wild_animals_number ";
    file << healthy_wild_animals_number << endl;
    file << "infected_wild_animal_percentage ";
    file << infected_wild_animal_percentage << "%" << endl;
    file << "dead_wild_animals_number ";
    file << dead_wild_animals_number << endl;
}

void CSimulation::initialization(SDL_Renderer* pRendered){

    infected_humans_number = ((population_density*size)/1000000)*infected_humans_percentage/100;
    infected_animals_number = ((animals_density*size)/1000000)*infected_animal_percentage/100;
    infected_wild_animals_number = ((animals_wild_density * size) / 1000000) * infected_wild_animal_percentage / 100;
    healthy_humans_number = (population_density*size)/1000000 - infected_humans_number;
    healthy_animals_number = (animals_density*size)/1000000 - infected_animals_number;
    healthy_wild_animals_number = (animals_wild_density * size) / 1000000 - infected_wild_animals_number;
    number_of_actors = infected_animals_number+infected_humans_number+healthy_animals_number+healthy_humans_number;

    g_pAnimal = new CAnimal(this);
    g_pWild_animal = new CWild_animal(this);
    g_pHuman = new CHuman(this);
    g_pInfected_animal = new CInfected_animal(this);
    g_pInfected_wild_animal = new CInfected_wild_animal(this);
    g_pInfected_human = new CInfected_human(this);

    CActor* tmp_actor = NULL;
    int r;
    bool infect = false;

    g_pHuman->generate_map(this);
    g_pInfected_human->generate_map(this);
    g_pAnimal->generate_map(this);
    g_pInfected_animal->generate_map(this);
    g_pWild_animal->generate_map(this);
    g_pInfected_wild_animal->generate_map(this);
    


    for (int i = 0; i < healthy_humans_number; i++) {
        do {
            r = rand() % size;
        } while (!((map[r] != 'w') && (map[r] != 'f') && (map[r] != 'g') && (map[r] != 'o')));

        tmp_actor = new CActor();
        tmp_actor->init(pRendered, r % (size_horizontal), r / (size_horizontal), g_pHuman, false, this);
        vActors.push_back(tmp_actor);

    }

    for (int i = 0; i < infected_humans_number; i++) {
        do {
            r = rand() % size;
        } while (!((map[r] != 'w') && (map[r] != 'f') && (map[r] != 'g') && (map[r] != 'o')));

        tmp_actor = new CActor();
        tmp_actor->init(pRendered, r % (size_horizontal), r / (size_horizontal), g_pInfected_human, true, this);
        vActors.push_back(tmp_actor);

    }
    for (int i = 0; i < healthy_animals_number; i++) {
        do {
            r = rand() % size;
        } while (map[r] != 'g');

        tmp_actor = new CActor();
        tmp_actor->init(pRendered, r % (size_horizontal), r / (size_horizontal), g_pAnimal, false, this);
        vActors.push_back(tmp_actor);

    }

    for (int i = 0; i < infected_animals_number; i++) {
        do {
            r = rand() % size;
        } while (map[r] != 'g');

        tmp_actor = new CActor();
        tmp_actor->init(pRendered, r % (size_horizontal), r / (size_horizontal), g_pInfected_animal, true, this);
        vActors.push_back(tmp_actor);

    }

    for (int i = 0; i < healthy_wild_animals_number; i++) {
        do {
            r = rand() % size;
        } while (map[r] != 'f');

        tmp_actor = new CActor();
        tmp_actor->init(pRendered, r % (size_horizontal), r / (size_horizontal), g_pWild_animal, false, this);
        vActors.push_back(tmp_actor);

    }

    for (int i = 0; i < infected_wild_animals_number; i++) {
        do {
            r = rand() % size;
        } while (map[r] != 'f');

        tmp_actor = new CActor();
        tmp_actor->init(pRendered, r % (size_horizontal), r / (size_horizontal), g_pInfected_wild_animal, true, this);
        vActors.push_back(tmp_actor);

    }


    g_pTargeted_movement = new CTargeted_movement();
    g_pIdle_movement = new CIdle_movement();
    g_pTargeted_movement->wave(this, g_pHuman);
    
}

void CSimulation::update(){
    infected_wild_animals_number = 0;
    infected_animals_number = 0;
    infected_humans_number = 0;
    healthy_wild_animals_number = 0;
    healthy_animals_number = 0;
    healthy_humans_number = 0;
    dead_wild_animals_number = 0;
    dead_animals_number = 0;
    dead_humans_number = 0;
   


    int vas=vActors.size();
    for(int i =0; i<vas; i++){
        if (vActors[i] != NULL) {
            if (vActors[i]->m_alive) {
                vActors[i]->update(vActors);
                    if (vActors[i]->m_behavior == g_pHuman) {
                        healthy_humans_number++;
                    }
                    else if (vActors[i]->m_behavior == g_pAnimal) {
                        healthy_animals_number++;
                    }
                    else if (vActors[i]->m_behavior == g_pWild_animal) {
                        healthy_wild_animals_number++;
                    }
                    else if (vActors[i]->m_behavior == g_pInfected_wild_animal) {
                        infected_wild_animals_number++;
                    }
                    else if (vActors[i]->m_behavior == g_pInfected_animal) {
                        infected_animals_number++;
                    }
                    else if (vActors[i]->m_behavior == g_pInfected_human) {
                        infected_humans_number++;
                    }

            }
            else {
                //cout <<i<<"->"<< vActors[i]->m_alive<<endl;
                if (vActors[i]->m_behavior == g_pInfected_human) {
                    dead_humans_number++;
                }
                else if (vActors[i]->m_behavior == g_pInfected_animal) {
                    dead_animals_number++;
                }
                else if (vActors[i]->m_behavior == g_pInfected_wild_animal) {
                    dead_wild_animals_number++;
                }
            }
        }
    }
    infected_animal_percentage = (100 * infected_animals_number / (infected_animals_number + healthy_animals_number));
    infected_wild_animal_percentage = (100 * infected_wild_animals_number / (infected_wild_animals_number + healthy_wild_animals_number));
    infected_humans_percentage = (100 * infected_humans_number / (infected_humans_number + healthy_humans_number));
}

void CSimulation::draw(SDL_Renderer* pRendered, SDL_Texture* pBGR){

    SDL_RenderClear(pRendered);
    SDL_RenderCopy(pRendered, pBGR, NULL, NULL);

    int sz = vActors.size();
    for(int i=0; i<sz; i++){
        if (vActors[i]->m_alive) {
            vActors[i]->draw(i);
        }
        
    }

    SDL_RenderPresent(pRendered);
}

vector<CActor*> CSimulation::get_vActors(){

    return vActors;

}

void CSimulation::save(ostream& file) {
    file << ticks_per_day<<"    ";
    //file << "Time: ";
    file << time << "   ";
    //file << "Dead_humans_number ";
    file << dead_humans_number << "   ";
    //file << "Dead_humans_number ";
    file << dead_animals_number << "    ";
    //file << "Dead_humans_number ";
    file << dead_wild_animals_number << endl;



}

