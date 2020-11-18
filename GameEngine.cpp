#include "GameEngine.h"
#include "GameObservers.h"
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
        mapLoader = new MapLoader(selectedMapName);
        if(mapLoader->getStatus())
        {
            gameMapPtr = new Map(mapLoader->getMap());
            delete mapLoader;
            break;
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
    playerListPtr = new vector<Player*>;

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
        Player* player = new Player(playerName);

        playerListPtr->push_back(player); 
    }

    //Generate deck as a function of the number of players
    deckPtr = new Deck(numOfPlayers);
    cout << "Displaying Deck: " << endl;
    cout << "\n" << *deckPtr;
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

GameInit::GameInit(vector<Player*>* plPtr, Map* gmPtr, Deck* gdPtr)
{
    playerListPtr = new vector<Player*>;
    for (int i = 0; i < plPtr->size(); i++) {
        playerListPtr->push_back(new Player(*plPtr->at(i)));
    }
    gameMapPtr = new Map(gmPtr);
    gameDeckPtr = new Deck(*gdPtr);
    startupPhase(playerListPtr, gameMapPtr);
}
GameInit::~GameInit() {
    for (int i = 0; i < playerListPtr->size(); i++) {
        delete playerListPtr->at(i);
    }
    delete playerListPtr;
    delete gameMapPtr;
    delete gameDeckPtr;
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
            if((j+playerListIndices.size())<=territoryIndices.size())
            {
                //set territory owner
                territoriesPtr->at(territoryIndices.at(j + k))->setterritory_owner(playerListPtr->at(k));
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
    cout << "" << endl;
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

WarzoneGame::WarzoneGame(GameInit* gi)
{
    playerListPtr = gi->getPlayerListPtr();
    gameMapPtr = gi->getGameMapPtr();
    gameDeckPtr = gi->getGameDeckPtr();
    hasWon = false;
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

    //notify subscribers of change of phase to display the troops that were added on turn start.
    Notify();

}

void WarzoneGame::issueOrdersPhase(Player* player)
{
    setCurrentPhase(1);
    // player decides which territories are to be attacked in priority
    cout << "The list of territories to be attacked: " << endl;
    cout << player->toString(player->toAttack(*gameMapPtr)) << endl;

    // player decides which territories are to be defended in priority
    cout << "The list of territories to be defended: " << endl;
    cout << player->toString(player->gettoDefend()) << endl;

    int reinforcementCounter = player->getCurrentReinforcements();
    // Player issues deploy orders
    cout << "Issuing deploy orders only." << endl;
    cout << "Armies to deploy: " << reinforcementCounter << endl << endl;

    for(int i = 0; i<player->gettoDefend()->size(); i++)
    {
        if(reinforcementCounter >= 10)
        {
            //order added to player's orderlist
            Deployorder *deployorder1 = new Deployorder(player, new int(10), player->gettoDefend()->at(i));
            cout << deployorder1->print() << endl;
            player->issueOrder(deployorder1);
            
            reinforcementCounter -= 10;
            cout << "Armies left to deploy: " << reinforcementCounter << endl;
        }
        else if(reinforcementCounter > 0)
        {
            //order added to player's orderlist
            Deployorder *deployorder1 = new Deployorder(player, new int(reinforcementCounter), player->gettoDefend()->at(i));
            cout << deployorder1->print() << endl;
            player->issueOrder(deployorder1);
            
            reinforcementCounter = 0;
            cout << "Armies left to deploy: " << reinforcementCounter << endl;
        }
        else break;
    }

    cout << endl << "All available armies have been deployed. Proceeding with issuing advance orders." << endl;

    // player chooses to move armies from one of its own territory to the other
    // in order to defend them
    Advanceorder *advanceorder1 = new Advanceorder(new int (4), player, player->gettoDefend()->at(3),
                                                player->gettoDefend()->at(2), gameMapPtr);
    cout << advanceorder1->print() << " in order to defend" << endl;
    player->issueOrder(advanceorder1);

    Advanceorder *advanceorder2 = new Advanceorder(new int (7), player, player->gettoDefend()->at(1),
                                                player->gettoDefend()->at(3), gameMapPtr);
    cout << advanceorder2->print() << " in order to defend" << endl;
    player->issueOrder(advanceorder2);
cout << "0"<< endl;
    // player chooses to move armies from one of its territories to a neighboring
    // enemy territory to attack them
    Territory *attack3;
    Territory *defend3;
    Advanceorder *advanceorder3;

    if(player->toAttack(*gameMapPtr, *player->gettoDefend()->at(0))->at(0) && player->toDefend(*gameMapPtr)->at(0))
    {
        attack3 = player->toAttack(*gameMapPtr, *player->gettoDefend()->at(0))->at(0); 
        defend3 = player->toDefend(*gameMapPtr)->at(0);    
        advanceorder3 = new Advanceorder(new int (2), player, attack3, defend3, gameMapPtr);
        cout << endl << advanceorder3->print() << " in order to attack" << endl;
        player->issueOrder(advanceorder3);
    }

    Territory *attack4;
    Territory *defend4;
    if(player->toAttack(*gameMapPtr, *player->gettoDefend()->at(1))->at(0) && player->toDefend(*gameMapPtr)->at(1))
    {
        attack4 = player->toAttack(*gameMapPtr, *player->gettoDefend()->at(1))->at(0);
        defend4 = player->toDefend(*gameMapPtr)->at(1);
        Advanceorder *advanceorder4 = new Advanceorder(new int (6), player, attack4, defend4, gameMapPtr);
        cout << endl << advanceorder4->print() << " in order to attack" << endl;
        player->issueOrder(advanceorder4);
    }

    Player* player2;
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

    if((card->getName()) == "Bomb Card")
    {
        Territory *attack = player->toAttack(*gameMapPtr, *player->gettoDefend()->at(1))->at(0);
        // the play method adds the order to the player's orderlist
        dynamic_cast<BombCard *>(card)->play(gameDeckPtr, player, attack);
        cout << "The Bomb card was used and an order was issued successfully." << endl;
    }
    else if(card->getName() == "Reinforcement Card")
    {
        // the play method adds the order to the player's orderlist
        dynamic_cast<ReinforcementCard *>(card)->play(gameDeckPtr, player);
        cout << "The Reinforcement card was used and an order was issued successfully." << endl;
    }
    else if(card->getName() == "Blockade Card")
    {
        // the play method adds the order to the player's orderlist
        dynamic_cast<BlockadeCard*>(card)->play(gameDeckPtr, player, player->gettoDefend()->at(0));
        cout << "The Blockade card was used and an order was issued successfully." << endl;
    }
    else if(card->getName() == "Airlift Card")
    {
        // the play method adds the order to the player's orderlist
        dynamic_cast<AirliftCard*>(card)->play(gameDeckPtr, player, player->gettoDefend()->at(1),player->gettoDefend()->at(0), new int(1));
        cout << "The Airlift card was used and an order was issued successfully." << endl;
    }
    else if(card->getName() == "Diplomacy Card")
    {
        // the play method adds the order to the player's orderlist
        dynamic_cast<DiplomacyCard*>(card)->play(gameDeckPtr, player, player2);
        cout << "The Diplomacy card was used and an order was issued successfully." << endl;
    }
    
    cout << "\nOrders Issued: " << endl;
    cout << *player->getPlayerlist() << endl;
    Notify();
}

void WarzoneGame::executeOrdersPhase()
{
    setCurrentPhase(2);

    setExecutionQueue();

    for(Order* order : executionQueue)
    {
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
    }

    Notify();
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
        //playerListPtr->pop_back();
    }
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
