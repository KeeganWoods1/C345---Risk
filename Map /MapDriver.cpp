#include <iostream>
#include "map.h"
using namespace std;

//create new objects (continent, territories)
int main() {

    std::cout << "creating the map" << std::endl;

    Continent* Ontario_and_Quebec = new Continent(1,"Ontario_and_Quebec", 1-1);

    std::cout << * Ontario_and_Quebec << std::endl;

    Territory* Quebec_North = new Territory(0,"Quebec-North", 1-1);

    Map* map = new Map(1);
    map->addContinent(Ontario_and_Quebec);

    cout << "Countries in Continents" << endl;

    /*TODO need to print out vector lists continents and territories, loop through? */
    /* TODO enable user input, print map elements*/
}
