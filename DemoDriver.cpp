#include "GameEngine.h"
#include "GameObservers.h"
#include <iostream>
#include <fstream>
#include <filesystem>
#include <string>
using namespace std;

void demoPart1()
{
    //Initialize the map directory and get user's selected map
    MapDirectoryInit* mdiPtr = new MapDirectoryInit();
    //Initialize player list and get number of players
    PlayerListInit* pliPtr = new PlayerListInit(); 

    cout << "Players in the game: " << endl;
    for(Player* p : *pliPtr->getPlayerList())
    {
        cout<< *p << endl;
    }
}
void demoPart2()
{
    //Initialize the map directory and get user's selected map
    MapDirectoryInit* mdiPtr = new MapDirectoryInit();
    
    //Initialize player list and get number of players
    PlayerListInit* pliPtr = new PlayerListInit();
    cout << *mdiPtr->getGameMap()->getContinents()->at(0) << endl;
    //Initialize game start phase
    GameInit* giPtr = new GameInit(pliPtr->getPlayerList(), mdiPtr->getGameMap(), pliPtr);

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
}
void demoPart3()
{
    //Initialize the map directory and get user's selected map
    MapDirectoryInit* mdiPtr = new MapDirectoryInit();
    //Initialize player list and get number of players
    PlayerListInit* pliPtr = new PlayerListInit();
    //Initialize game start phase
    GameInit* giPtr = new GameInit(pliPtr->getPlayerList(), mdiPtr->getGameMap(), pliPtr);

    WarzoneGame* warzoneGame = new WarzoneGame(giPtr);

    warzoneGame->mainGameLoop();
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
    GameInit* giPtr = new GameInit(pliPtr->getPlayerList(), mdiPtr->getGameMap(), pliPtr);

    WarzoneGame* model = new WarzoneGame(giPtr);
    
    StatsScreen* statsView = new StatsScreen(model);
    GameScreen* view = new GameScreen(model);
    
    GameController* controller = new GameController(view, statsView, model);

    controller->controlGame();
}

int main() {

    //demoPart1();
    cout << "\nPress any key to continue to Part 2 " << flush;
    cin.get();
    cin.get();
    demoPart2();
    cout << "\nPress any key to continue to Part 3" << flush;
    cin.get();
    cin.get();
    demoPart3();
    cout << "\nPress any key to continue to Part 4" << flush;
    cin.get();
    cin.get();
    demoPart4();
    cout << "\nPress any key to continue to Part 5" << flush;
    cin.get();
    cin.get();
    demoPart5();

    return 0;
}