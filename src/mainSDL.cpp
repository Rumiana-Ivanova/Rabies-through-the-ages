#include <iostream>
#include <Windows.h>
#include <ctime>
using namespace std;

#include "SDL2/SDL.h"

#include "CSimulation.h"



int main(int argc, char* argv[]) {

    SDL_Init(SDL_INIT_EVERYTHING);

    const char* config = "config\\simulation_source1.txt";
    if (argc > 1)
    {
        config = argv[1];
    }
    //int simulation_number=10;
    CSimulation simulation[180];

    for (int simulation_number = 0; simulation_number < 50; simulation_number++) {

        simulation[simulation_number].load(config);
        SDL_Window* pWindow = NULL;
        SDL_Renderer* pRendered = NULL;
        SDL_Surface* pTmp = NULL;
        SDL_Texture* pBGR = NULL;
        /// create window + rendered
        pWindow = SDL_CreateWindow("Simulation", 0, 0, simulation[simulation_number].size_horizontal * 10, simulation[simulation_number].size_vertical * 10, 0);
        pRendered = SDL_CreateRenderer(pWindow, 0, SDL_RENDERER_ACCELERATED);

        string img_tga;;

        switch (simulation[simulation_number].era)
        {
        case CSimulation::Era::Antiquity:
            pTmp = SDL_LoadBMP("img\\babylon_102x102.bmp");
            img_tga = "img\\babylon_102x102.tga";
            break;
        case CSimulation::Era::ClassicalAntiquity:
            pTmp = SDL_LoadBMP("img\\athina_102x102.bmp");
            img_tga = "img\\athina_102x102.tga";
            break;
        case CSimulation::Era::ModernDay:
            pTmp = SDL_LoadBMP("img\\dole_102x102.bmp");
            img_tga = "img\\dole_102x102.tga";
            break;
        }

        ///load background image
        pBGR = SDL_CreateTextureFromSurface(pRendered, pTmp);
        SDL_FreeSurface(pTmp);

        srand(time(NULL));
        simulation[simulation_number].load_map(img_tga);
        simulation[simulation_number].initialization(pRendered);
        simulation[simulation_number].draw(pRendered, pBGR);


        while (true) {
            bool quit = false;
            SDL_Event e;
            //Handle events on queue
            while (SDL_PollEvent(&e) != 0)
            {
                //User requests quit
                if (e.type == SDL_QUIT)
                {
                    quit = true;
                }
            }
            simulation[simulation_number].update();
            simulation[simulation_number].draw(pRendered, pBGR);
            if (GetAsyncKeyState(VK_F1)) {
                system("cls");
                simulation[simulation_number].print(cout);
            }
            if (simulation[simulation_number].end()) {
                fstream save;
                save.open("config\\save_exel_v3.txt", std::fstream::app);
                simulation[simulation_number].save(save);
                break;
            }
            simulation[simulation_number].time++;
            simulation[simulation_number].ticks_per_day = simulation_number / 10 + 1;
            if (quit)
                break;
            SDL_Delay(200);
        }
        cout << simulation_number << " ended" << endl;
        SDL_Quit();
    }

    return 0;
}
