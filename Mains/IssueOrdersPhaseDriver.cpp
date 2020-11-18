#include "GameEngine.h"
#include <iostream>
#include <fstream>
#include <filesystem>
#include <string>

using namespace std;

int main() {
  //  _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
    //Initialize the map directory and get user's selected map
    MapDirectoryInit* mdiPtr = new MapDirectoryInit();
    //Initialize player list and get number of players
   //
    PlayerListInit* pliPtr = new PlayerListInit();
    //Initialize game start phase
    GameInit* giPtr = new GameInit(pliPtr->getPlayerList(), mdiPtr->getGameMap(), pliPtr->getDeckPtr());

    for (int i=0; i<mdiPtr->getGameMap()->getTerritories()->size(); i++)
    {
      mdiPtr->getGameMap()->getTerritories()->at(i)->setterritory_armycount(6);
    }
    cout << "" << endl;

    WarzoneGame* g = new WarzoneGame(giPtr);
    
    StatsScreen* statsView = new StatsScreen(g);
    GameScreen* view = new GameScreen(g);
    
    g->Detach(statsView);
    g->Detach(view);

    GameController* controller = new GameController(view, statsView, g);

    controller->controlGame();

    delete giPtr;
    delete mdiPtr;
    delete pliPtr;
    delete g;
    return 0;
}