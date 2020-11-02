#include "GameEngine.h"
#include <iostream>
#include <fstream>
#include <filesystem>
#include <string>

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
    cin >> selectedMap;
    cout << "" << endl;
}

string MapDirectoryInit::getSelectedMap()
{
    return selectedMap;
}

MapDirectoryInit::~MapDirectoryInit(){}

PlayerListInit::PlayerListInit()
{
    string playerName;
    playerList = new vector<Player*>;

    //set number of players
    cout << "Please enter the number of players in the game (2-5): " << endl;
    cin >> numOfPlayers;
    cout << "" << endl;
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
    //po.toggle()
}

void ObserverToggle::toggle(StatisticsObserver* so)
{
    cout << "Calling toggle() method of StatisticsObserver object" << endl;
    //so.toggle()
}