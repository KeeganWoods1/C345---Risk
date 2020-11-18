#include "GameEngine.h"
#include "GameObservers.h"
#include <iostream>
#include <fstream>
#include <filesystem>
#include <string>
using namespace std;

void demoPart1()
{
    
}
void demoPrt2()
{

}
void demoPart3()
{

}
void demoPart4()
{
    
}
void demoPart5() 
{
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
}

int main() {

    demoPart5();

    return 0;
}

