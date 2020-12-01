#include "GameEngine.h"
#include "GameObservers.h"
#include <iostream>
#include <fstream>
#include <filesystem>
#include <string>
//#include <crtdbg.h>

using namespace std;
#ifdef _DEBUG
#define DBG_NEW new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
// Replace _NORMAL_BLOCK with _CLIENT_BLOCK if you want the
// allocations to be of _CLIENT_BLOCK type
#else
#define DBG_NEW new
#endif

void demoPart1_2()
{
    //Initialize the map directory and get user's selected map
    MapDirectoryInit* mdiPtr = DBG_NEW MapDirectoryInit();
    //Initialize player list and get number of players
    PlayerListInit* pliPtr = DBG_NEW PlayerListInit();
    //Initialize game start phase
    GameInit* giPtr = DBG_NEW GameInit(pliPtr->getPlayerList(), mdiPtr->getGameMap(), pliPtr);

    WarzoneGame* model = DBG_NEW WarzoneGame(giPtr);
    
    StatsScreen* statsView = DBG_NEW StatsScreen(model);
    GameScreen* view = DBG_NEW GameScreen(model);
    
    GameController* controller = DBG_NEW GameController(view, statsView, model);

    controller->controlGame();

    for (int i = 0; i < mdiPtr->getGameMap()->getTerritories()->size(); i++) {
        if (mdiPtr->getGameMap()->getTerritories()->at(i)->getterritory_owner()->getName().compare("Neutral") == 0)delete mdiPtr->getGameMap()->getTerritories()->at(i)->getterritory_owner();
    }
    delete statsView;
    delete view;
    delete controller;
    delete model;
    delete giPtr;
    delete mdiPtr;
    delete pliPtr;
}

int main() {
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
    demoPart1_2();

    return 0;
}
