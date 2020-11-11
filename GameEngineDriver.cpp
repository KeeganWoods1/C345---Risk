/*#include "GameEngine.h"
#include <iostream>
#include <fstream>
#include <filesystem>
#include <string>
using namespace std;

int main() {

    //Initialize the map directory and get user's selected map
    MapDirectoryInit* mdiPtr = new MapDirectoryInit();
    //Initialize player list and get number of players
    PlayerListInit* pliPtr = new PlayerListInit();
    //Initialize phase observers and ask user if they wish to turn either one off
    PhaseObserver* poPtr = new PhaseObserver();
    StatisticsObserver* soPtr = new StatisticsObserver();
    ObserverToggle* otPtr = new ObserverToggle(poPtr, soPtr);
    //Initialize game start phase
    GameInit* giPtr = new GameInit(pliPtr->getPlayerList(), mdiPtr->getGameMap());

    for (int i=0; i<mdiPtr->getGameMap()->getTerritories()->size(); i++)
    {
      cout << *mdiPtr->getGameMap()->getTerritories()->at(i) << endl;  
    }
    //pliPtr->getPlayerList()->at(0)->issueOrder(new Deployorder())
 
    return 0;
}*/