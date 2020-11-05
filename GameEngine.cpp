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

    while(1)
    {
        //ask user to pick
        cout << "\nPlease enter the name of the map file you wish to load: " << endl;
        cin >> selectedMapName;
        cout << "" << endl;

        //use user input as parameter to MapLoader() constructor
        MapLoader* mapLoader = new MapLoader("MapFiles/" + selectedMapName);
        if(mapLoader->getStatus())
        {
            gameMap = mapLoader->getMap();
            break;
        }
        else
        {
            cin.clear();
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }    
    }    
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
        cout << "\nPlease enter the number of players in the game (2-5): " << endl; 
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

    //create player objects and add them to the player list
    for (int i= 0; i<numOfPlayers; i++)
    {
        string playerName;
        cout << "Please enter player " << i+1 << "'s name"<< endl;
        cin >> playerName;
        Player* player = new Player(playerName);

        playerList->push_back(player); 
    }

    //Generate deck as a function of the number of players
    deckPtr = new Deck(numOfPlayers);
    cout << "Displaying Deck: " << endl;
    cout << "\n" << *deckPtr;
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
    cout << "\nDo you wish to display current Phase info each turn? (yes/no)" << endl;
    cin >> yesNo;
    cout << "" << endl;

    if(yesNo == "no")
    {
       this->toggle(po); 
    }

    //set Statistics Observers on or off at user's discretion
    cout << "\nDo you wish to display current game statistics info each turn? (yes/no)" << endl;
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

    //display player turn order
    cout << "\nPrinting Player order: " << endl;
    for(int i=0; i< playerList->size(); i++)
    {
        cout << i+1 << ". " << *playerList->at(i) << endl;
    }

    //randomly assign all territories in Map object to one player (ie. dont assign 2 players to the same territory)
    vector<int> territoryIndices;
    vector<int> playerListIndices;
    vector<Territory*>* territoriesPtr = gameMap->getTerritories();

    //lists of indices to shuffle, of same size as territoryList
    for(int i=0; i<gameMap->getTerritories()->size(); i++)
    {
        territoryIndices.push_back(i);
    }
    //list of indices for the playerList
    for(int i=0; i<playerList->size(); i++)
    {
        playerListIndices.push_back(i);
    }

    //shuffle territory indices to randomize territory assignment
    std::shuffle(territoryIndices.begin(), territoryIndices.end(), g);

    //assign territories to players without "double booking"
    for(int j=0; j<territoryIndices.size(); j+=playerListIndices.size())
    {
        for(int k=0; k<playerListIndices.size(); k++)
        {
            //if there aren't enough remaining territories to assign one to each player, the remaining territories are neutral.
            if((j+playerListIndices.size())<territoryIndices.size())
            {
                territoriesPtr->at(territoryIndices.at(j+k))->setterritory_owner(playerList->at(k)); 
            }
        }     
    }
    
    //Give players armies A to distribute (Dont actually let them distribute just give them an initial count)
    const int n = playerList->size();

    switch(n)
    {
        case 2:
        {
            for(auto player : *playerList)
            {
                player->addReinforcements(40);
            }
            break;
        }
        case 3:
        {
            for(auto player : *playerList)
            {
                player->addReinforcements(35);
            }
            break;
        }
        case 4:
        {
            for(auto player : *playerList)
            {
                player->addReinforcements(30);
            }
            break;
        }
        case 5:
        {
            for(auto player : *playerList)
            {
                player->addReinforcements(25);
            }
            break;
        }
    }

    //display player reinforcement pools
    cout << "\nPrinting player reinforcement pools: " << endl;
    for(int i=0; i< playerList->size(); i++)
    {
        cout << *playerList->at(i) << ": Available reinforcements: " 
        << playerList->at(i)->getCurrentReinforcements() << endl;
    }
}
