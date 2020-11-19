#include "GameEngine.h"
#include "GameObservers.h"
#include <iostream>
#include <fstream>
#include <filesystem>
#include <string>
#include <random>
#include <algorithm>
#ifdef _DEBUG
#define DBG_NEW new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
// Replace _NORMAL_BLOCK with _CLIENT_BLOCK if you want the
// allocations to be of _CLIENT_BLOCK type
#else
#define DBG_NEW new
#endif
using namespace std;
namespace fs = std::filesystem;

MapDirectoryInit::MapDirectoryInit()
{
    //display map files in folder
    std::string path = "MapFiles";
    MapLoader* mapLoader;
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
        mapLoader = DBG_NEW MapLoader(selectedMapName);
        if(mapLoader->getStatus())
        {
            if(mapLoader->getMap() != NULL)
            {
                gameMapPtr = new Map(mapLoader->getMap());
                delete mapLoader;
                break; 
            }
        }
        else
        {
            cin.clear();
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            delete mapLoader;
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

MapDirectoryInit::~MapDirectoryInit(){
    delete gameMapPtr;
}

PlayerListInit::PlayerListInit()
{
    bool validEntry = false;
    string playerName;
    playerListPtr = DBG_NEW vector<Player*>;

    //set number of players
    while(!validEntry)
    {
        cout << "Please enter the number of players in the game (2-5): " << endl;
        if((cin >> numOfPlayers) && numOfPlayers >= 2 && numOfPlayers <= 5)
        {
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
        Player* player = DBG_NEW Player(playerName);

        playerListPtr->push_back(player); 
    }

    //Generate deck as a function of the number of players
    deckPtr = DBG_NEW Deck(numOfPlayers);
    cout << "Displaying Deck: " << endl;
    cout << "\n" << *deckPtr;

    string yesNo;
    cout << "Do you wish to have phase information displayed on screen?(Yes/No) "<< endl;
    cin >> yesNo;
    if(yesNo == "No")
    {
        setDisplayPhaseInfo(false);
    }  
    else
    {
        setDisplayPhaseInfo(true);
    }
    
    cout << "\nDo you wish to have game statistics information displayed on screen?(Yes/No) "<< endl;
    cin >> yesNo;
    if(yesNo == "No")
    {
        setDisplayStatsInfo(false);
    } 
    else
    {
        setDisplayStatsInfo(true);
    }    
}
PlayerListInit::~PlayerListInit() {
    delete deckPtr;
    for (int i = 0; i < playerListPtr->size(); i++) {
        delete playerListPtr->at(i);
    }
    delete playerListPtr;
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

bool PlayerListInit::getDisplayPhaseInfo()
{
    return phaseObservers;
}
void PlayerListInit::setDisplayPhaseInfo(bool b)
{
    phaseObservers = b;
}
bool PlayerListInit::getDisplayStatsInfo()
{
    return statsObservers;
}
void PlayerListInit::setDisplayStatsInfo(bool b)
{
    statsObservers = b;
}

GameInit::GameInit(vector<Player*>* plPtr, Map* gmPtr, PlayerListInit* pli)
{
    if(gmPtr == NULL)
    {
        cout << "Map is null" << endl;
    }
    pliPtr = pli;
    playerListPtr = plPtr;
    gameMapPtr = gmPtr;
    gameDeckPtr = pli->getDeckPtr();
    startupPhase(playerListPtr, gameMapPtr);
}
GameInit::~GameInit() {
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
            if((j+playerListIndices.size())<=territoryIndices.size())
            {
                //set territory owner
                delete territoriesPtr->at(territoryIndices.at(j + k))->getterritory_owner();
                territoriesPtr->at(territoryIndices.at(j + k))->setterritory_owner(playerListPtr->at(k));
                //add territory to player's toDefend list
                playerListPtr->at(k)->gettoDefend(*gameMapPtr)->push_back(territoriesPtr->at(territoryIndices.at(j+k)));
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
}

vector<Player*>* GameInit::getPlayerListPtr()
{
    return playerListPtr;
}

Map* GameInit::getGameMapPtr()
{
    return gameMapPtr;
}

Deck* GameInit::getGameDeckPtr()
{
    return gameDeckPtr;
}

PlayerListInit* GameInit::getpliPtr()
{
    return pliPtr;
}

WarzoneGame::WarzoneGame(GameInit* gi)
{
    playerListPtr = gi->getPlayerListPtr();
    gameMapPtr = gi->getGameMapPtr();
    gameDeckPtr = gi->getGameDeckPtr();
    hasWon = false;
    gameInitPtr = gi;
}

bool WarzoneGame::ordersRemain()
{
    for(Player* player : *playerListPtr)
    {
        if(!player->getOrderList()->empty())
        {
            return false;
        }
    }
    return true;
}

WarzoneGame::~WarzoneGame() {
}

void WarzoneGame::reinforcementPhase(Player *player, int numTerrOwned)
{
    setCurrentPhase(0);
    const int MIN_REINFORCEMENT = 3;
    int reinforcement = 0;

    reinforcement += player->getNumTerrOwned() / 3;

    //to make sure that the player has the minimum reinforcement
    if (reinforcement < MIN_REINFORCEMENT) {
        reinforcement = MIN_REINFORCEMENT;
    }
    //Place the reinforcements in the players' pools.
    player->addReinforcements(reinforcement);
    //denstration of part 3
    cout << "----------------------------------------------" << endl;
    cout << "Demonstrating REINFORCEMENTS PHASE for " << *player << endl;
    cout << "player owns " << player->getNumTerrOwned() << " territories." << endl;
    cout << "Player owns 0 continents" << endl;
    cout << "Added " << reinforcement << " troops to reinforcement pool" << endl;
    cout << "----------------------------------------------" << endl;    
    
    //notify subscribers of change of phase to display the troops that were added on turn start.
    
    Notify();
}

void WarzoneGame::issueOrdersPhase(Player* player)
{
    setCurrentPhase(1);
    cout << "----------------------------------------------" << endl;
    cout << "Demonstrating ISSUE ORDERS PHASE for " << *player << endl;

    int reinforcementCounter = player->getCurrentReinforcements();
    // Player issues deploy orders
    cout << "Issuing deploy orders." << endl;
    cout << "Armies to deploy: " << reinforcementCounter << endl << endl;

    for(int i = 0; i<player->gettoDefend(*gameMapPtr)->size(); i++)
    {
        if(reinforcementCounter >= 10)
        {
            //order added to player's orderlist
            Deployorder *deployorder1 = DBG_NEW Deployorder(player, DBG_NEW int(10), player->gettoDefend(*gameMapPtr)->at(i));
            cout << deployorder1->print() << endl;
            player->issueOrder(deployorder1);
            
            reinforcementCounter -= 10;
        }
        else if(reinforcementCounter > 0)
        {
            //order added to player's orderlist
            Deployorder *deployorder1 = DBG_NEW Deployorder(player, DBG_NEW int(reinforcementCounter), player->gettoDefend(*gameMapPtr)->at(i));
            cout << deployorder1->print() << endl;
            player->issueOrder(deployorder1);
            
            reinforcementCounter = 0;
        }
        else break;
    }

    // player chooses to move armies from one of its own territory to the other
    // in order to defend them
    Advanceorder *advanceorder1 = DBG_NEW Advanceorder(DBG_NEW int (4), player, player->gettoDefend(*gameMapPtr)->at(3),
                                                player->gettoDefend(*gameMapPtr)->at(2), gameMapPtr);
    player->issueOrder(advanceorder1);

    Advanceorder *advanceorder2 = DBG_NEW Advanceorder(DBG_NEW int (7), player, player->gettoDefend(*gameMapPtr)->at(1),
                                                player->gettoDefend(*gameMapPtr)->at(3), gameMapPtr);
    player->issueOrder(advanceorder2);

    // player chooses to move armies from one of its territories to a neighboring
    // enemy territory to attack them
    Territory *attack3;
    Territory *defend3;
    Advanceorder *advanceorder3;
    if(player->gettoDefend(*gameMapPtr)->size() > 0 && player->toAttack(*gameMapPtr, *player->gettoDefend(*gameMapPtr)->at(0))->size() > 0)
    {
        attack3 = player->toAttack(*gameMapPtr, *player->gettoDefend(*gameMapPtr)->at(0))->at(0);
        defend3 = player->toDefend(*gameMapPtr)->at(0);    
        advanceorder3 = DBG_NEW Advanceorder(DBG_NEW int (2), player, attack3, defend3, gameMapPtr);
        player->issueOrder(advanceorder3);
    }
    Territory *attack4;
    Territory *defend4;
    if(player->gettoDefend(*gameMapPtr)->size() > 1 && player->toAttack(*gameMapPtr, *player->gettoDefend(*gameMapPtr)->at(1))->size() > 0)
    {
        attack4 = player->toAttack(*gameMapPtr, *player->gettoDefend(*gameMapPtr)->at(1))->at(0);
        defend4 = player->toDefend(*gameMapPtr)->at(1);
        Advanceorder *advanceorder4 = DBG_NEW Advanceorder(DBG_NEW int (6), player, attack4, defend4, gameMapPtr);
        player->issueOrder(advanceorder4);
    }
    Player* player2 = NULL;
    for(Player* pl : *playerListPtr)
    {
        if(player->getName() != pl->getName())
        {
            player2 = pl;
            break;
        }
    }

    // getting cards from the player's hand
    Card* card = player->getHand()->getHandContainer().at(0);
    if((card->getName()) == "Bomb Card"){
        Territory *attack = player->toAttack(*gameMapPtr)->at(0);
        // the play method adds the order to the player's orderlist
        dynamic_cast<BombCard *>(card)->play(gameDeckPtr, player, attack);
    }
    else if(card->getName() == "Reinforcement Card")
    {
        // the play method adds the order to the player's orderlist
        dynamic_cast<ReinforcementCard *>(card)->play(gameDeckPtr, player);
    }
    else if(card->getName() == "Blockade Card")
    {
        // the play method adds the order to the player's orderlist
        dynamic_cast<BlockadeCard*>(card)->play(gameDeckPtr, player, player->gettoDefend(*gameMapPtr)->at(0));
    }
    else if(card->getName() == "Airlift Card")
    {
        // the play method adds the order to the player's orderlist
        dynamic_cast<AirliftCard*>(card)->play(gameDeckPtr, player, player->gettoDefend(*gameMapPtr)->at(1),player->gettoDefend(*gameMapPtr)->at(0), DBG_NEW int(1));
    }
    else if(card->getName() == "Diplomacy Card")
    {
        // the play method adds the order to the player's orderlist
        dynamic_cast<DiplomacyCard*>(card)->play(gameDeckPtr, player, player2);
    }
    cout << "\nOrders Issued: " << endl;
    cout << *player->getPlayerlist() << endl;
    cout << "----------------------------------------------" << endl;

    Notify();
}

void WarzoneGame::executeOrdersPhase()
{
    setCurrentPhase(2);
    setExecutionQueue();

    cout << "----------------------------------------------" << endl;
    cout << "Demonstrating EXECUTE ORDERS PHASE\n" << endl;

    for(Order* order : executionQueue)
    {
        cout << "Executing " << *order << endl;

        if(dynamic_cast<Advanceorder*>(order))
        {
            if(order->execute())
            {
                //Notify as soon as a territory is conquered
                Notify();
            }   
        }
        else
        {
            order->execute();    
        }
        delete order;
    }
    executionQueue.clear();
    cout << "----------------------------------------------" << endl;

    Notify();    
    for (int i = 0; i < executionQueue.size(); i++) {
        delete executionQueue.at(i);
    }
}

void WarzoneGame::mainGameLoop()
{
    int turnCounter = 0;
    while(playerListPtr->size()>1)
    {
        //Remove players who own no territories
        for(int i=0; i<playerListPtr->size(); i++)
        {
            if(playerListPtr->at(i)->getNumTerrOwned()<=0)
            {
                cout << "Player: " << *playerListPtr->at(i) << " has been eliminated" << endl;
                playerListPtr->erase(playerListPtr->begin()+i); 
                //update the observers with new playerlist  
                Notify();
            }
        }
        //Each player gets their turn according to the playerList order (from startup phase)
        for(Player* player : *playerListPtr)
        {
            setCurrentPlayer(player);
            //Draw a card
            gameDeckPtr->draw(player->getHand());

            if (player->getName().compare("Neutral")!=0 && player->getcaptureTerritory()){
                gameDeckPtr->draw(player->getHand());
                player->setcaptureTerritory(false);
            }

            reinforcementPhase(player, player->getNumTerrOwned());
            issueOrdersPhase(player);
        }

        //All players are done issuing orders, execution of orders can begin
        executeOrdersPhase();
        //playerListPtr->at(0)->gettoDefend(*gameMapPtr)->clear();
        break;
    }
    cout << *playerListPtr->at(0) << " Wins!" << endl;
    setHasWon(true);
    Notify();
}

Player* WarzoneGame::getCurrentPlayer()
{
    return currentPlayer;
}

void WarzoneGame::setCurrentPlayer(Player* p)
{
    currentPlayer = p;
}

Map* WarzoneGame::getGameMap()
{
    return gameMapPtr;
}

void WarzoneGame::setExecutionQueue()
{
    vector<Order*> executionVector;

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
            executionVector.push_back(ol->at(index));
            ol->erase(ol->cbegin()+index);
        }    
    }
    executionQueue = executionVector;
}

vector<Order*> WarzoneGame::getExecutionQueue()
{
    return executionQueue;
}

int WarzoneGame::getCurrentPhase()
{
    return currentPhase;
}

void WarzoneGame::setCurrentPhase(int n)
{
    currentPhase = n;
}

bool WarzoneGame::getHasWon()
{
    return hasWon;
}

void WarzoneGame::setHasWon(bool b)
{
    hasWon = b;
}

vector<Player*> WarzoneGame::getPlayerList()
{
    return *playerListPtr;
}

GameInit* WarzoneGame::getGameInitPtr()
{
    return gameInitPtr;
}
