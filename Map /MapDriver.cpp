#pragma once
#include "map.h"
#include <vector>

using namespace std;

//create new objects (continents, territories, player, armies)
int main() {
    std::cout<< "Inputting the objects, each territory belongs to one continent..." << std::endl;

    //create Player and Territory objects
    Player* Samamoun = new Player("Samamoun");
    Player* Jakelam = new Player("Jakelam");
    Player* salhanyf = new Player("salhanyf");
    Player* SalehaTrq = new Player("SalehaTrq");
    Player* KeeganWoods = new Player("salhanyf");

    //Territory(int continent, string territory_name, string territory_continent, Player* player, int territory_armycount);
    Territory* New_Brunswick = new Territory(1,"New_Brunswick", Samamoun, 15);
    Territory* Prince_Edward_Island = new Territory(1, "Prince_Edward_Island", salhanyf, 12);
    Territory* Nova_Scotia = new Territory(1,"Nova_Scotia", Jakelam, 10);
    Territory* Newfoundland = new Territory(1,"Newfoundland", SalehaTrq, 6);
    Territory* Labrador = new Territory(1,"Labrador", KeeganWoods, 3);

    //Ontario_and_Quebec
    Territory* Quebec_North = new Territory(2,"Quebec-North", new Player(), 20);
    Territory* Quebec_Central = new Territory(2,"Quebec_Central", new Player(), 30);
    Territory* Quebec_South = new Territory(2,"Quebec_South", new Player(), 5);
    Territory* Ontario_South = new Territory(2, "Ontario_South", new Player(), 2);
    Territory* Ontario_West = new Territory(2, "Ontario_West", new Player(), 5);
    Territory* Ontario_North = new Territory(2,"Ontario_North",  new Player(), 9);

    //put territory objects into an vector territories
    vector <Territory> terr ={*New_Brunswick, *Prince_Edward_Island, *Nova_Scotia,
                              *Newfoundland,*Labrador, *Quebec_North, *Quebec_Central,
                              *Quebec_South,*Ontario_South, *Ontario_West, *Ontario_North};

    std::cout << "\nPrinting all the Countries in Continents..." << std::endl;
    for (int i = 0; i < terr.size(); i++) {
        std::cout << "Continent " << terr[i].getterritory_continent()
                  << ", " << "Country " << terr[i].getterritory_name()
                  << ", Player: " << terr[i].getterritory_owner()->getName()
                  << ", Armies:" << terr[i].getterritory_armycount() << std::endl;
    }
    std::cout << "\nNow, to test the whether they are connected or not...\n" << std::endl;


    //adding the borders
    Map* map = new Map(11);
    map->addBorder(0,7); map->addBorder(0,1); map->addBorder(0,2);
    map->addBorder(1,2);
    map->addBorder(2,3);
    map->addBorder(3,4);map->addBorder(3,6);
    map->addBorder(4,6);map->addBorder(4,5);
    map->addBorder(5,6);
    map->addBorder(6,7);map->addBorder(6,10);
    map->addBorder(7,8);
    map->addBorder(8,10);map->addBorder(8,9);
    map->addBorder(9,10);
    map->toString();

    
            // TODO: change ValidateGraph() function name to validate()  //

    //testing Map object
    if (map->ValidateGraph() == true)
        std::cout << "OUTPUT:: The Map is a connected graph.\n" << std::endl;
    else
        std::cout << "OUTPUT:: The Map is NOT connected graph.\n" << std::endl;

    std::cout << "This is an example of a map graph that isn't connected.\n" << std::endl;

    //i commented out the borders, that make the map connected (same as above)
    Map NotConnected(11);
    //NotConnected.addBorder(0,7);NotConnected.addBorder(0,1); NotConnected.addBorder(0,2);
    //NotConnected.addBorder(1,2);
    NotConnected.addBorder(2,3);
    NotConnected.addBorder(3,4);NotConnected.addBorder(3,6);
    NotConnected.addBorder(4,6);NotConnected.addBorder(4,5);
    NotConnected.addBorder(5,6);
    NotConnected.addBorder(6,7);NotConnected.addBorder(6,10);
    //NotConnected->addBorder(7,8);
    //NotConnected->addBorder(8,10);map->addBorder(8,9);
    //NotConnected->addBorder(9,10);
    NotConnected.toString();
    
        // TODO: change ValidateGraph() function name to validate()  //

    if (NotConnected.ValidateGraph() == true)
        std::cout << "OUTPUT:: Continents are Connected\n" << std::endl;
    else
        std::cout << "OUTPUT:: Continents are NOT Connected\n" << std::endl;

    //to prevent memory leaks
    delete Samamoun;delete Jakelam;delete salhanyf;delete SalehaTrq;delete KeeganWoods;
    delete map;
    delete New_Brunswick;delete Prince_Edward_Island;delete Nova_Scotia;delete Newfoundland;delete Labrador;
    delete Quebec_North;delete Quebec_Central;delete Quebec_South;delete Ontario_South;delete Ontario_West;
}
