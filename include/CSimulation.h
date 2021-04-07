#ifndef CSIMULATION_H
#define CSIMULATION_H

#include <string>
#include <fstream>
#include <vector>
using namespace std;

#include "CActor.h"
#include "CMovement.h"
#include "CHuman.h"
#include "CAnimal.h"
#include "CWild_animals.h"
#include "CInfected_animal.h"
#include "CInfected_human.h"
#include "CInfected_wild_animal.h"

const char ACTOR_CHAR = '*';
const char EMPTY = ' ';

class CSimulation
{
    public:

        enum Era {
            Antiquity = 1,
            ClassicalAntiquity = 2,
            ModernDay = 3,
        };

        CSimulation();
        virtual ~CSimulation();

        void load(string file_name);
        void load_map();
        void print(ostream& file);
        void initialization(SDL_Renderer* pRendered);  ///добави случайно генериране на начални координати
        void update();  ///преместването
        void save(ostream& file);
        void draw(SDL_Renderer* pRendered, SDL_Texture* pBGR);    ///запаза всичко в един временен масив(екрана)///печатане на екрана
        bool end();
        ///CActor abc;
        vector<CActor*> get_vActors();

        ///loaded from file
        vector<CActor* > vActors;
        int time = 0;
        int size_vertical;                      ///in meters
        int size_horizontal; 
        int size;
        vector<char> map;
        ///in meters
        int fatality_rate;                      ///the fatal cases from all contaminated in percentage
        int infection_range;                    ///the radius of the circle from witch the disease is transmittable

        int era;
        string file_map;
        bool pictures;
        bool hydrophobia;
        int ticks_per_day;
        int human_incubation_period;
        int human_incubation_period_fluctuation;
        int human_first_simptoms;
        int human_first_simptoms_fluctuation;
        int human_death_time;
        int human_death_time_fluctuation;
        int human_infection_rate;
        int animals_wild_incubation_period;
        int animals_wild_incubation_period_fluctuation;
        int animals_wild_first_symptoms;
        int animals_wild_first_symptoms_fluctuation;
        int animals_wild_death_time;
        int animals_wild_death_time_fluctuation;
        int animals_wild_infection_rate;
        int animals_incubation_period;
        int animals_incubation_period_fluctuation;
        int animals_first_symptoms;
        int animals_first_symptoms_fluctuation;
        int animals_death_time;
        int animals_death_time_fluctuation;
        int animals_infection_rate;

    private:

        int population_density;                 ///in people per km^2
        float infected_humans_percentage;       ///in the beginning of the simulation
        int animals_density;                    ///percentage in in the beginning of the simulation
        float infected_animal_percentage;       ///percentage of infected animals
        int animals_wild_density;                    
        float infected_wild_animal_percentage;

        ///auto calculated
        int number_of_actors;
        int healthy_humans_number;
        int healthy_animals_number;
        int healthy_wild_animals_number;
        int infected_humans_number;
        int infected_animals_number;
        int infected_wild_animals_number;
        int dead_humans_number;
        int dead_animals_number;
        int dead_wild_animals_number;

        ///actors


};


#endif // CSIMULATION_H
