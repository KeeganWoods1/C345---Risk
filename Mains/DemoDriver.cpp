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
void demoPart1()
{
    //Initialize the map directory and get user's selected map
    MapDirectoryInit* mdiPtr = DBG_NEW MapDirectoryInit();
    //Initialize player list and get number of players
    PlayerListInit* pliPtr = DBG_NEW PlayerListInit();
    cout << "Players in the game: " << endl;
    for(Player* p : *pliPtr->getPlayerList())
    {
        cout<< *p << endl;
    }
    for (int i = 0; i < mdiPtr->getGameMap()->getTerritories()->size(); i++) {
        if (mdiPtr->getGameMap()->getTerritories()->at(i)->getterritory_owner()->getName().compare("Neutral") == 0)delete mdiPtr->getGameMap()->getTerritories()->at(i)->getterritory_owner();
    }
    delete mdiPtr;
    delete pliPtr;
}
void demoPart2()
{
    //Initialize the map directory and get user's selected map
    MapDirectoryInit* mdiPtr = DBG_NEW MapDirectoryInit();
    
    //Initialize player list and get number of players
    PlayerListInit* pliPtr = DBG_NEW PlayerListInit();
    cout << *mdiPtr->getGameMap()->getContinents()->at(0) << endl;
    //Initialize game start phase
    GameInit* giPtr = DBG_NEW GameInit(pliPtr->getPlayerList(), mdiPtr->getGameMap(), pliPtr);

    cout << "Territories distributed to players: " << endl;
    for(Territory* t : *giPtr->getGameMapPtr()->getTerritories())
    {
        cout << *t << endl;
    }
    cout << "\nPlayers in order of play(shuffled): " << endl;
    for(Player* p : *giPtr->getPlayerListPtr())
    {
        cout << *p << endl;
    }
    cout << "\nPlayer initial reinforcement pools: " << endl;
    for(Player* p : *giPtr->getPlayerListPtr())
    {
        cout << "Player: " << *p << " has: " << p->getCurrentReinforcements() << " troops." << endl;
    }
    for (int i = 0; i < mdiPtr->getGameMap()->getTerritories()->size(); i++) {
        if (mdiPtr->getGameMap()->getTerritories()->at(i)->getterritory_owner()->getName().compare("Neutral") == 0)delete mdiPtr->getGameMap()->getTerritories()->at(i)->getterritory_owner();
    }
    delete giPtr;
    delete mdiPtr;
    delete pliPtr;
}
void demoPart3()
{
    //Initialize the map directory and get user's selected map
    MapDirectoryInit* mdiPtr = DBG_NEW MapDirectoryInit();
    //Initialize player list and get number of players
    PlayerListInit* pliPtr = DBG_NEW PlayerListInit();
    //Initialize game start phase
    GameInit* giPtr = DBG_NEW GameInit(pliPtr->getPlayerList(), mdiPtr->getGameMap(), pliPtr);

    WarzoneGame* warzoneGame = DBG_NEW WarzoneGame(giPtr);

    warzoneGame->mainGameLoop();


    for (int i = 0; i < mdiPtr->getGameMap()->getTerritories()->size(); i++) {
        if (mdiPtr->getGameMap()->getTerritories()->at(i)->getterritory_owner()->getName().compare("Neutral") == 0)delete mdiPtr->getGameMap()->getTerritories()->at(i)->getterritory_owner();
    }
    delete warzoneGame;
    delete giPtr;
    delete mdiPtr;
    delete pliPtr;
}

void demoPart4_5()
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
   // _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

    demoPart1();
    cout << "\nPress any key to continue to Part 2 " << flush;
    cin.get();
    cin.get();
    demoPart2();
    cout << "\nPress any key to continue to Part 3" << flush;
    cin.get();
    cin.get();
    demoPart3();
    cout << "\nPress any key to continue to Part 5" << flush;
    cin.get();
    cin.get();
    demoPart4_5();

    return 0;
}