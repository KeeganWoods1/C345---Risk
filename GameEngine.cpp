#include "GameEngine.h"
#include <iostream>
#include <fstream>
#include <filesystem>
#include <string>
#include <random>

using namespace std;
namespace fs = std::filesystem;

MapDirectoryInit::MapDirectoryInit()
{
    //display map files in folder
    std::string path = "MapFiles";
    for (const auto & entry : fs::directory_iterator(path))
    {
        std::cout << entry.path().filename() << std::endl;
    }
        
    //ask user to pick
    cout << "Please enter the name of the map file you wish to load: " << endl;
    cin >> selectedMapName;
    cout << "" << endl;

    //use user input as parameter to MapLoader() constructor
    MapLoader* mapLoader = new MapLoader("MapFiles/" + selectedMapName);

    gameMap = mapLoader->getMap();

}

string MapDirectoryInit::getSelectedMapName()
{
    return selectedMapName;
}

Map* MapDirectoryInit::getGameMap()
{
    return gameMap;
}

MapDirectoryInit::~MapDirectoryInit(){}

PlayerListInit::PlayerListInit()
{
    bool validEntry = false;
    string playerName;
    playerList = new vector<Player*>;

    //set number of players
    while(!validEntry)
    {
        cout << "Please enter the number of players in the game (2-5): " << endl; 
        if((cin >> numOfPlayers) && numOfPlayers >= 2 && numOfPlayers <= 5)
        {
            cout << "" << endl;
            validEntry = true;
        }
        else
        {
            cin.clear();
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            cout << "Not a valid entry, please enter a value between 2 and 5.\n" << endl;
        }   
    }

    //Generate deck as a function of the number of players
    deckPtr = new Deck(numOfPlayers);
}

vector<Player*>* PlayerListInit::getPlayerList()
{
    return playerList;
}

int PlayerListInit::getNumOfPlayers()
{
    return numOfPlayers;
}

Deck* PlayerListInit::getDeckPtr()
{
    return deckPtr;
}

ObserverToggle::ObserverToggle(PhaseObserver* po, StatisticsObserver* so)
{
    string yesNo;
    phaseObserver = po;
    statsObserver = so;

    //set Phase Observers on or off at user's discretion
    cout << "Do you wish to display current Phase info each turn? (yes/no) " << endl;
    cin >> yesNo;
    cout << "" << endl;

    if(yesNo == "no")
    {
       this->toggle(po); 
    }

    //set Statistics Observers on or off at user's discretion
    cout << "Do you wish to display current game statistics info each turn? (yes/no)\n" << endl;
    cin >> yesNo;
    cout << "" << endl;
    
    if(yesNo == "no")
    {
       this->toggle(so); 
    }
    
}

void ObserverToggle::toggle(PhaseObserver* po)
{
    cout << "Calling toggle() method of PhaseObserver object" << endl;
    //po.remove();
}

void ObserverToggle::toggle(StatisticsObserver* so)
{
    cout << "Calling toggle() method of StatisticsObserver object" << endl;
    //so.remove();
}

GameInit::GameInit(vector<Player*>* playerList, Map* gameMap)
{
    startupPhase(playerList, gameMap);
}

void GameInit::startupPhase(vector<Player*>* playerList, Map* gameMap)
{
    //randomly determine order of play
    //rng used as seed for std::mt19337
    std::random_device rd;
    //mersenne-twister-engine to ensure high quality "shuffle"
    std::mt19937 g(rd());
    //shuffle playerList, play order will be the order in which players appear in the shuffled list
    std::shuffle(playerList->begin(), playerList->end(), g);

    //randomly assign all territories in Map object to one player (ie. dont assign 2 players to the same territory)
    

    //Give players armies A to distribute (Dont actually let them distribute just give them an initial count)
    //if players = 2, A = 40
    //if players = 3, A = 35
    //if players = 4, A = 30
    //if players = 5, A = 25


}
