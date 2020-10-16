#include <iostream>
using namespace std;

#include "CSimulation.h"

int main(){

     int simulation_number=0;
    CSimulation simulation[1];


    simulation[simulation_number].load("config\\simulation_source1.txt");
    simulation[simulation_number].initialization();
    ///simulation[simulation_number].print(cout);
    while(true){
        simulation[simulation_number].update();
        simulation[simulation_number].draw();
        Sleep(200);
    }

}
