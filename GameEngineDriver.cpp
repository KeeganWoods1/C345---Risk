#include "GameEngine.h"
#include <iostream>
#include <fstream>
#include <filesystem>
#include <string>
#include <crtdbg.h>

using namespace std;

int main() {
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
    //Initialize the map directory and get user's selected map
    MapDirectoryInit* mdiPtr = new MapDirectoryInit();
    //Initialize player list and get number of players
   //
    PlayerListInit* pliPtr = new PlayerListInit();
    //Initialize game start phase
    GameInit* giPtr = new GameInit(pliPtr->getPlayerList(), mdiPtr->getGameMap(), pliPtr->getDeckPtr());

    for (int i=0; i<mdiPtr->getGameMap()->getTerritories()->size(); i++)
    {
      cout << *mdiPtr->getGameMap()->getTerritories()->at(i);
      mdiPtr->getGameMap()->getTerritories()->at(i)->setterritory_armycount(6);
    }
    cout << "" << endl;

    WarzoneGame* g = new WarzoneGame(giPtr);
    for (int i = 0; i < mdiPtr->getGameMap()->getTerritories()->size(); i++) {
        if (mdiPtr->getGameMap()->getTerritories()->at(i)->getterritory_owner()->getName().compare("Neutral") == 0) {
            delete mdiPtr->getGameMap()->getTerritories()->at(i)->getterritory_owner();
            break;
        }
    }
    delete giPtr;
    delete mdiPtr;
    delete pliPtr;
    delete g;
    return 0;
}