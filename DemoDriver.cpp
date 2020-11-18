#include "GameEngine.h"
#include "GameObservers.h"
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
    //Initialize game start phase
    GameInit* giPtr = new GameInit(pliPtr->getPlayerList(), mdiPtr->getGameMap(), pliPtr->getDeckPtr());
 
    WarzoneGame* model = new WarzoneGame(giPtr);
    
    StatsScreen* statsView = new StatsScreen(model);
    GameScreen* view = new GameScreen(model);
    
    GameController* controller = new GameController(view, statsView, model);

    controller->controlGame();

    return 0;
}