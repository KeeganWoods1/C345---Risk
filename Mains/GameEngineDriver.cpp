#include "GameEngine.h"
#include <iostream>
#include <fstream>
#include <filesystem>
#include <string>
#include <crtdbg.h>
using namespace std;
#ifdef _DEBUG
#define DBG_NEW new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
// Replace _NORMAL_BLOCK with _CLIENT_BLOCK if you want the
// allocations to be of _CLIENT_BLOCK type
#else
#define DBG_NEW new
#endif
int main() {
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
    //Initialize the map directory and get user's selected map
    MapDirectoryInit* mdiPtr = DBG_NEW MapDirectoryInit();
    //Initialize player list and get number of players
   //
    PlayerListInit* pliPtr = DBG_NEW PlayerListInit();
    //Initialize game start phase
    GameInit* giPtr = DBG_NEW GameInit(pliPtr->getPlayerList(), mdiPtr->getGameMap(), pliPtr->getDeckPtr());

    for (int i=0; i< giPtr->getGameMapPtr()->getTerritories()->size(); i++)
    {
      cout << *giPtr->getGameMapPtr()->getTerritories()->at(i);
      giPtr->getGameMapPtr()->getTerritories()->at(i)->setterritory_armycount(6);
    }
    cout << "" << endl;

    WarzoneGame* g = DBG_NEW WarzoneGame(giPtr);
    
    StatsScreen* statsView = DBG_NEW StatsScreen(g);
    GameScreen* view = DBG_NEW GameScreen(g);
    
  //  g->Detach(statsView);
  //  g->Detach(view);

    GameController* controller = DBG_NEW GameController(view, statsView, g);

    controller->controlGame();
    g->Detach(statsView);
    g->Detach(view);
    vector<Territory*>* terr = giPtr->getGameMapPtr()->getTerritories();
    for (int i = 0; i < terr->size(); i++) {
        if (terr->at(i)->getterritory_owner()->getName().compare("Neutral") == 0) {
            delete terr->at(i)->getterritory_owner();
        }
    }
    delete statsView;
    delete view;
    delete g;
    delete mdiPtr;
    delete pliPtr;
    delete giPtr;
    delete controller;
    return 0;
}