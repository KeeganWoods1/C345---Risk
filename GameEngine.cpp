#include "GameEngine.h"
#include <iostream>
#include <fstream>
#include <filesystem>
#include <string>
#include <random>
#include <algorithm>

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
            gameMapPtr = mapLoader->getMap();
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
    return gameMapPtr;
}

MapDirectoryInit::~MapDirectoryInit(){}

PlayerListInit::PlayerListInit()
{
    bool validEntry = false;
    string playerName;
    playerListPtr = new vector<Player*>;

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

        playerListPtr->push_back(player); 
    }

    //Generate deck as a function of the number of players
    deckPtr = new Deck(numOfPlayers);
    cout << "Displaying Deck: " << endl;
    cout << "\n" << *deckPtr;
}

vector<Player*>* PlayerListInit::getPlayerList()
{
    return playerListPtr;
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

GameInit::GameInit(vector<Player*>* plPtr, Map* gmPtr)
{
    playerListPtr = plPtr;
    gameMapPtr = gmPtr;
    startupPhase(playerListPtr, gameMapPtr);
}

void GameInit::startupPhase(vector<Player*>* playerListPtr, Map* gameMapPtr)
{
    //randomly determine order of play
    //rng used as seed for std::mt19337
    std::random_device rd;
    //mersenne-twister-engine to ensure high quality "shuffle"
    std::mt19937 g(rd());
    //shuffle playerList, play order will be the order in which players appear in the shuffled list
    std::shuffle(playerListPtr->begin(), playerListPtr->end(), g);

    //display player turn order
    cout << "\nPrinting Player order: " << endl;
    for(int i=0; i< playerListPtr->size(); i++)
    {
        cout << i+1 << ". " << *playerListPtr->at(i) << endl;
    }

    //randomly assign all territories in Map object to one player (ie. dont assign 2 players to the same territory)
    vector<int> territoryIndices;
    vector<int> playerListIndices;
    vector<Territory*>* territoriesPtr = gameMapPtr->getTerritories();

    for(int i=0; i<gameMapPtr->getTerritories()->size(); i++)
    {
        territoryIndices.push_back(i);
        //lists of indices to shuffle, of same size as territoryList
    }
    //list of indices for the playerList
    for(int i=0; i<playerListPtr->size(); i++)
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
                //set territory owner
                territoriesPtr->at(territoryIndices.at(j+k))->setterritory_owner(playerListPtr->at(k)); 
                //add territory to player's toDefend list
                playerListPtr->at(k)->gettoDefend()->push_back(territoriesPtr->at(territoryIndices.at(j+k)));
            }
        }     
    }
    
    //Give players armies A to distribute (Dont actually let them distribute just give them an initial count)
    const int n = playerListPtr->size();

    switch(n)
    {
        case 2:
        {
            for(auto player : *playerListPtr)
            {
                player->addReinforcements(40);
            }
            break;
        }
        case 3:
        {
            for(auto player : *playerListPtr)
            {
                player->addReinforcements(35);
            }
            break;
        }
        case 4:
        {
            for(auto player : *playerListPtr)
            {
                player->addReinforcements(30);
            }
            break;
        }
        case 5:
        {
            for(auto player : *playerListPtr)
            {
                player->addReinforcements(25);
            }
            break;
        }
    }

    //display player reinforcement pools
    cout << "\nPrinting player reinforcement pools: " << endl;
    for(int i=0; i< playerListPtr->size(); i++)
    {
        cout << *playerListPtr->at(i) << ": Available reinforcements: " 
        << playerListPtr->at(i)->getCurrentReinforcements() << endl;
    }
}

vector<Player*>* GameInit::getPlayerListPtr()
{
    return playerListPtr;
}

Map* GameInit::getGameMapPtr()
{
    return gameMapPtr;
}

WarzoneGame::WarzoneGame(GameInit* gi)
{
    playerListPtr = gi->getPlayerListPtr();
    gameMapPtr = gi->getGameMapPtr();
    mainGameLoop();

}

bool WarzoneGame::ordersRemain()
{
    for(Player* player : *playerListPtr)
    {
        if(!player->getOrderList()->empty())
        {
            return false;
            break;
        }
    }
    return true;
}

void WarzoneGame::reinforcementPhase()
{
    cout << "\n****************************************************************************************************" << endl;
    cout << "Beginning reinforcement phase.\n" << endl;
}

void WarzoneGame::issueOrdersPhase(Player* player)
{
    cout << "\n****************************************************************************************************" << endl;
    cout << "Beginning issue orders phase.\n" << endl;

    //**NOTE: This is for testing part 3: Execute orders Only! Remove this and implement full issue orders method**
    Player* player2;
    for(Player* pl : *playerListPtr)
    {
        if(player->getName() != pl->getName())
        {
            player2 = pl;
            break;
        }
    }

    player->issueOrder(new Deployorder(player,new int (3),player->gettoDefend()->at(0)));
    player->issueOrder(new Deployorder(player,new int (3),player->gettoDefend()->at(1)));
    Territory *attack = player->toAttack(*gameMapPtr, *player->gettoDefend()->at(0))->at(0);
    Territory *defend = player->toDefend(*gameMapPtr)->at(0);
    player->issueOrder(new Advanceorder(new int(1),player,attack,defend,gameMapPtr));
    player->issueOrder(new Airliftorder(new int (1),player->gettoDefend()->at(1),player->gettoDefend()->at(0),player));
    player->issueOrder(new Bomborder(player,player2->gettoDefend()->at(0)));
    player->issueOrder(new Blockadeorder(player,player->gettoDefend()->at(0)));
    player->issueOrder(new Negotiateorder(player,player2));
    player->issueOrder(new Advanceorder(new int(1),player,attack,defend,gameMapPtr));

    cout << "\nOrders Issued: \n" << endl;
    cout << *player->getPlayerlist() << endl;

}

void WarzoneGame::executeOrdersPhase()
{
    cout << "\n****************************************************************************************************" << endl;
    cout << "Beginning execute orders phase.\n" << endl;

    while(!this->ordersRemain())
    {
        for (int k = 0; k< playerListPtr->size(); k++){
            vector<Order*>* ol = playerListPtr->at(k)->getOrderList();
            int priority = 99;
            int index = -1;

            for (int i = 0; i < ol->size(); i++){
                Deployorder* o  = dynamic_cast<Deployorder*> (ol->at(i));
                Advanceorder* o1  = dynamic_cast<Advanceorder*> (ol->at(i));
                Airliftorder* o2  = dynamic_cast<Airliftorder*> (ol->at(i));
                Blockadeorder* o3  = dynamic_cast<Blockadeorder*> (ol->at(i));
                Bomborder* o4  = dynamic_cast<Bomborder*> (ol->at(i));
                Negotiateorder* o5  = dynamic_cast<Negotiateorder*> (ol->at(i));
                Reinforcementorder* o6  = dynamic_cast<Reinforcementorder*> (ol->at(i));
                if (o!=NULL){
                    priority = 1;
                    index = i;
                    break;
                }
                if (o1!=NULL && priority >4){
                    priority = 4;
                    index = i;
                }
                if (o2!=NULL && priority >2){
                    priority = 2;
                    index = i;
                }
                if (o3!=NULL && priority >3){
                    priority = 3;
                    index = i;
                }
                if (o4!=NULL && priority >4){
                    priority = 4;
                    index = i;
                }
                if (o5!=NULL && priority >4){
                    priority = 4;
                    index = i;
                }
                if (o6!=NULL && priority >4){
                    priority = 4;
                    index = i;
                }
            }
            if (ol->empty())continue;
            ol->at(index)->execute();
            ol->erase(ol->cbegin()+index);
        }    
    }


}

void WarzoneGame::mainGameLoop()
{
    while(playerListPtr->size()>1)
    {
        //Remove players who own no territories
        for(int i=0; i<playerListPtr->size(); i++)
        {
            if(playerListPtr->at(i)->getNumTerrOwned()<=0)
            {
                playerListPtr->erase(playerListPtr->begin()+i);
                cout << *playerListPtr->at(i) << " has been eliminated!";
            }
        }
        //Each player gets their turn according to the playerList order (from startup phase)
        for(Player* player : *playerListPtr)
        {
            //Players Assign Reinforcements and Issue Orders
            cout << *player << "'s Turn, Terrirtories owned: " << player->getNumTerrOwned() << endl;
            reinforcementPhase();
            issueOrdersPhase(player);
            //Pause the loop. For debug purposes only
            int a;
            cin >> a;
            cin.clear();
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
        //All players are done issuing orders, execution of orders can begin
        executeOrdersPhase();

        cout << "\n****************************************************************************************************" << endl;
        cout << "\n\nEND OF TURN\n" << endl;

        int a;
        cin >> a;
        cin.clear();
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
}
