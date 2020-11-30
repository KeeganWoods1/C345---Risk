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
    ConquestFileReader* conMapLoader;

    for (const auto & entry : fs::recursive_directory_iterator(path))
    {
        std::cout << entry.path().filename() << std::endl;
    }

    while(1)
    {
        int fileType;
        //ask user to pick
        cout << "\nPlease enter the name of the map file you wish to load: " << endl;
        cin >> selectedMapName;
        cout << "" << endl;
        cin.clear();
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        cout << "Is this\n1. A Warzone Map File\n2. A Conquest Map File" << endl;
        cin >> fileType;
        cout << "" << endl;
        cin.clear();
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        if(fileType == 1)
        {
            //use user input as parameter to MapLoader() constructor
            mapLoader = DBG_NEW MapLoader(selectedMapName);
            if(mapLoader->getStatus())
            {
                if(mapLoader->getMap() != NULL)
                {
                    gameMapPtr = mapLoader->getMap();
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
        else
        {
            conMapLoader =  DBG_NEW ConquestFileReader(selectedMapName);
            if (conMapLoader->getStatus()){
                ConquestFileReaderAdapter* conquestFileReaderAdapter = new ConquestFileReaderAdapter(conMapLoader);
                conquestFileReaderAdapter->loadMap(selectedMapName);
                gameMapPtr = conMapLoader->getMap();
                delete conquestFileReaderAdapter;   
                break;
            }   
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

//copy constructor
MapDirectoryInit::MapDirectoryInit(const MapDirectoryInit& c) : 
selectedMapName(c.selectedMapName), 
gameMapPtr(new Map(*c.gameMapPtr)) {}

//assignmnet operator overload
MapDirectoryInit &MapDirectoryInit::operator = (const MapDirectoryInit& o) 
{
    selectedMapName = o.selectedMapName;
    gameMapPtr = o.gameMapPtr;
    return *this;
}

//stream i/o overloads
istream &operator >> (istream &stream, MapDirectoryInit &o)
{
    stream >> o.selectedMapName;
    return stream;
}

ostream &operator << (ostream &out, const MapDirectoryInit &o)
{
    out << o.selectedMapName;
    return out;
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
        bool b = true;
        Player* player;
        while (b) {
            cout << "please input the number corresponding to the player type\n1: Human ai\n2: Aggresive ai\n3: benevolent ai\n4: neutral ai\n";
            int i = -1;
            cin >> i;
            switch (i) {
            case 1: {
                player = DBG_NEW Player(playerName, new HumanPlayerStrategy());
                b = false;
                break;
            }
            case 2: {
                player = DBG_NEW Player(playerName, new AggressivePlayerStrategy());
                b = false;
                break;
            }
            case 3: {
                player = DBG_NEW Player(playerName, new BenevolentPlayerStrategy());
                b = false;
                break;
            }
            case 4: {
                player = DBG_NEW Player(playerName, new NeutralPlayerStrategy());
                b = false;
                break;
            }
            default:
                cout << "inccorrect number please try again";
            }
            cin.clear();
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
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
//copy constructor
PlayerListInit::PlayerListInit(const PlayerListInit& c) : 
    numOfPlayers(c.numOfPlayers), 
    playerListPtr(new vector<Player*>(*c.playerListPtr)), 
    deckPtr(new Deck(*c.deckPtr)), 
    phaseObservers(c.phaseObservers), 
    statsObservers(c.statsObservers) {}

//assignmnet operator overload
PlayerListInit &PlayerListInit::operator = (const PlayerListInit& o) 
{
    numOfPlayers = o.numOfPlayers;
    playerListPtr = o.playerListPtr;
    deckPtr = o.deckPtr;
    phaseObservers = o.phaseObservers;
    statsObservers = o.statsObservers;
    return *this;
}

ostream &operator << (ostream &out, const PlayerListInit &o)
{
    out << "This is a PlayerInit Object";
    return out;
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
//copy constructor
GameInit::GameInit(const GameInit& c) : 
    pliPtr(new PlayerListInit(*c.pliPtr)),
    playerListPtr(new vector<Player*>(*c.playerListPtr)),
    gameMapPtr(new Map(*c.gameMapPtr)),
    gameDeckPtr(c.gameDeckPtr) {}

//assignmnet operator overload
GameInit &GameInit::operator = (const GameInit& o) 
{
    pliPtr = o.pliPtr;
    playerListPtr = o.playerListPtr;
    gameMapPtr = o.gameMapPtr;
    gameDeckPtr = o.gameDeckPtr;

    return *this;
}
ostream &operator << (ostream &out, const GameInit &o)
{
    out << "This is a GameInit Object";
    return out;
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
    int continentBonus = player->getContinentBonus(gameMapPtr);

    reinforcement += player->getNumTerrOwned() / 3;
    reinforcement += continentBonus;

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
    cout << "Player receives " << continentBonus << " continent bonus troops" << endl;
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
    player->issueOrder(gameMapPtr, playerListPtr,gameDeckPtr);
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
               // Notify();
            }   
        }
        else
        {
            order->execute();
        }
    }
    cout << "----------------------------------------------" << endl;

    Notify();    
    for (int i = 0; i < executionQueue.size(); i++) {
        delete executionQueue.at(i);
    }
    executionQueue.clear();

}

void WarzoneGame::mainGameLoop()
{
    //Game loop runs until only the winner remains
    int counter = 0;
    while(playerListPtr->size()>1)
    {
        //Remove players who own no territories
        for(int i=0; i<playerListPtr->size(); i++)
        {
            if(playerListPtr->at(i)->getNumTerrOwned()<=0)
            {
                cout << "Player: " << *playerListPtr->at(i) << " has been eliminated" << endl;
                delete playerListPtr->at(i);
                playerListPtr->erase(playerListPtr->begin()+i); 
                //update the observers with new playerlist  
                Notify();
            }
        }
        //Each player gets their turn according to the playerList order (from startup phase)
        if (playerListPtr->size() > 1) {
            for (Player* player : *playerListPtr)
            {
                setCurrentPlayer(player);
                //Draw a card regardless of previous turn (for demonstration only)
                gameDeckPtr->draw(player->getHand());
                //Player draws a card only if they conquered a territory in the previous turn
                if (player->getName().compare("Neutral") != 0 && player->getcaptureTerritory()) {
                    gameDeckPtr->draw(player->getHand());
                    player->setcaptureTerritory(false);
                }
                reinforcementPhase(player, player->getNumTerrOwned());
                player->clear();
                issueOrdersPhase(player);
            }
            //All players are done issuing orders, execution of orders can begin
            executeOrdersPhase();
        }
        counter++;
        if (counter > 70) break;
        //End the game for domonstrative purposes
    }
    //Only one player remains in the playerList, declare a winner
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

//copy constructor
WarzoneGame::WarzoneGame(const WarzoneGame& c) : 
    playerListPtr(new vector<Player*>(*c.playerListPtr)),
    gameMapPtr(new Map(*c.gameMapPtr)),
    gameDeckPtr(new Deck(*c.gameDeckPtr)),
    currentPlayer(new Player(*c.currentPlayer)),
    executionQueue(c.executionQueue),
    currentPhase(c.currentPhase),
    hasWon(c.hasWon),
    gameInitPtr(new GameInit(*c.gameInitPtr)) {}

//assignmnet operator overload
WarzoneGame &WarzoneGame::operator = (const WarzoneGame& o) 
{
    playerListPtr = o.playerListPtr;
    gameMapPtr = o.gameMapPtr;
    gameDeckPtr = o.gameDeckPtr;
    currentPlayer = o.currentPlayer;
    executionQueue = o.executionQueue;
    currentPhase = o.currentPhase;
    hasWon = o.hasWon;
    gameInitPtr = o.gameInitPtr;

    return *this;
}
ostream &operator << (ostream &out, const WarzoneGame &o)
{
    out << "This is a WarzoneGame Object";
    return out;
}
