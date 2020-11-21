#include "Player.h"
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#ifdef _DEBUG
#define DBG_NEW new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
// Replace _NORMAL_BLOCK with _CLIENT_BLOCK if you want the
// allocations to be of _CLIENT_BLOCK type
#else
#define DBG_NEW new
#endif
using namespace std;


// default constructor definition
Player::Player()
{
    name = "";
    capturedTerritory = DBG_NEW bool(false);
    negotiatedFriends = NULL;
    playerHand = NULL;
    playerOlist = NULL;
    territoriesToDefend = NULL;
    territoriesToAttack = NULL;
    surroundingterr = NULL;
}

// parametrized constructor definition
Player::Player(string playerName)
{
    // player's name is set to passed argument
    name = playerName;

    negotiatedFriends = DBG_NEW vector<string*>();
    // each player owns a hand of cards
    playerHand = DBG_NEW Hand();

    capturedTerritory = DBG_NEW bool(false);
    // minimal number of armies for any player is 3
    const int MINARMIES = 3;


    //initialize player orderlist
    playerOlist = DBG_NEW Orderlist();
    territoriesToDefend = DBG_NEW vector<Territory*>;
    territoriesToAttack = DBG_NEW vector<Territory*>;
    surroundingterr = DBG_NEW vector<Territory*>;
}

// destructor definition
Player::~Player()
{
    // avoid memory leaks

    if (playerHand !=NULL)delete playerHand;
    if (playerOlist != NULL)delete playerOlist;
    if (capturedTerritory != NULL)delete capturedTerritory;
    capturedTerritory = NULL;
    if (negotiatedFriends!=NULL)
        for (int i=0; i<negotiatedFriends->size(); i++){
            delete negotiatedFriends->at(i);
            negotiatedFriends->at(i) = NULL;
        }
    delete negotiatedFriends;
    negotiatedFriends = NULL;
    territoriesToDefend->clear();
    delete territoriesToDefend;
    territoriesToAttack->clear();
    delete territoriesToAttack;
    surroundingterr->clear();
    delete surroundingterr;

}

// copy constructor definition
Player::Player(const Player &player)
{
    name = player.name;
    reinforcementPool = player.reinforcementPool;
    capturedTerritory = DBG_NEW bool();
    *capturedTerritory = *player.capturedTerritory;
    negotiatedFriends = DBG_NEW vector<string*>;
    for (int i = 0; i < player.negotiatedFriends->size(); i++) {
        negotiatedFriends->push_back(DBG_NEW string(*player.negotiatedFriends->at(i)));
    }
    territoriesToDefend = DBG_NEW vector<Territory*>;
    for (int i = 0; i < player.territoriesToDefend->size(); i++) {
        territoriesToDefend->push_back(DBG_NEW Territory(*player.territoriesToDefend->at(i)));
    }
    territoriesToAttack = DBG_NEW vector<Territory*>;
    for (int i = 0; i < player.territoriesToAttack->size(); i++) {
        territoriesToAttack->push_back(DBG_NEW Territory(*player.territoriesToAttack->at(i)));
    }
    surroundingterr = DBG_NEW vector<Territory*>;
    for (int i = 0; i < player.surroundingterr->size(); i++) {
        surroundingterr->push_back(DBG_NEW Territory(*player.surroundingterr->at(i)));
    }
    playerHand = DBG_NEW Hand(*player.playerHand);
    playerOlist = DBG_NEW Orderlist(*player.playerOlist);

}

// assignment operator
Player& Player::operator = (const Player& o)
{
    return *this;
}

// stream insertion operator
ostream &operator << (ostream &output, const Player &o)
{
    output << o.name;
    return output;
}

void Player::addReinforcements(int r)
{
    reinforcementPool += r;
}

int Player::getCurrentReinforcements()
{
    return reinforcementPool;
}

void Player::setCurrentReinforcements(int i){
    reinforcementPool = i;
}

//stream insertion operator overload for printing a vector list of territory references
string Player::toString(vector<Territory*>* t)
{
    string list = "Territories: \n";

    if(t->size() > 0)
    {
        for(int i=0; i<t->size(); i++)
        {
            list.append(t->at(i)->getterritory_name() + "\n");
        }
    }

    return list;
}


// method to set the name of player
void Player::setName(string playerName)
{
    name = playerName;
}

// method to return name of player
string Player::getName()
{
    return name;
}

// definition of method to get number of
// territories owned by the player
int Player::getNumTerrOwned()
{
    return territoriesToDefend->size();
}

// definition of method to get hand
// owned by player
Hand* Player::getHand()
{
    return playerHand;
}

// definition of method to get
// player's orderlist
Orderlist* Player::getPlayerlist()
{
    return playerOlist;
}
void Player::clear() {
    *capturedTerritory = false;
    for (int i = 0; i < negotiatedFriends->size(); i++) {
        delete negotiatedFriends->at(i);
    }
    negotiatedFriends->clear();
}

vector<Territory*>* Player::gettoDefend(Map& m)
{
    updatetoDefend( m);
    return territoriesToDefend;
}
//new method updates the todefend list with all new territories
void Player::updatetoDefend(Map &m){
    territoriesToDefend->clear();
    delete territoriesToDefend;
    vector<Territory*>* terr2def = DBG_NEW vector<Territory*>;
        vector<Territory*>* terrall = m.getTerritories();
    for (int i =0; i < terrall->size(); i++){
        if (terrall->at(i)->getterritory_owner()->getName().compare(name)==0)terr2def->push_back(terrall->at(i));
    }
    territoriesToDefend = terr2def;
    terr2def = NULL;
}
// definition of method toDefend
// returning a list of territories to defend
vector<Territory*>* Player::toDefend(Map &m)
{
    updatetoDefend(m);
    vector<Territory *> *terr2 = DBG_NEW vector<Territory *>;
    for (int j =0; j<territoriesToDefend->size(); j++) {
        Territory t = territoriesToDefend->at(j);
        vector<Territory *> *terr = surroundingterritories(m, t);
        for (int i = 0; i < terr->size(); i++) {
            if (terr->at(i)->getterritory_owner()->getName().compare(t.getterritory_owner()->getName()) != 0) {
                terr2->push_back(territoriesToDefend->at(j));
                break;
            }
        }
        terr->clear();
        delete terr;
    }
    vector<Territory *>* terr = DBG_NEW vector<Territory*>();
    int initialsize = terr2->size();
    for (int k = 0; k<initialsize; k++) {
        int min = 100000;
        int index = -1;
        for (int i = 0; i < terr2->size(); i++) {
            if (terr2->at(i)->getterritory_armycount() < min) {
                min = terr2->at(i)->getterritory_armycount();
                index = i;
            }
        }
        terr->push_back(terr2->at(index));
        terr2->erase(terr2->cbegin() + index);

    }
    terr2->clear();
    delete terr2;
    surroundingterr->clear();
    for (int i = 0; i < terr->size(); i++) {
        surroundingterr->push_back(terr->at(i));
    }
    terr->clear();
    delete terr;
    return  surroundingterr;
}

// definition of method toAttack
// returning a list of territories to attack
vector<Territory*>* Player::toAttack(Map &m,Territory &t)
{
    updatetoDefend(m);
    territoriesToAttack->clear();
    vector<Territory*>* terr = surroundingterritories(m,t);
    vector<Territory*>* terr2 = DBG_NEW vector<Territory*>;
    for (int i=0; i <terr->size(); i++){
        if (terr->at(i)->getterritory_owner()->getName().compare(t.getterritory_owner()->getName())!=0)terr2->push_back(terr->at(i));
    }
    terr->clear();
    delete terr;
    terr = DBG_NEW vector<Territory*>();
    int initialsize = terr2->size();
    for (int k = 0; k<initialsize; k++) {
        int min = 100000;
        int index = -1;
        for (int i = 0; i < terr2->size(); i++) {
            if (terr2->at(i)->getterritory_armycount() < min) {
                min = terr2->at(i)->getterritory_armycount();
                index = i;
            }
        }
        if (index == -1)cout<<"error here";
        terr->push_back(terr2->at(index));
        terr2->erase(terr2->cbegin() + index);

    }
    terr2->clear();
    delete terr2;
    for (int i = 0; i < terr->size(); i++) {
        territoriesToAttack->push_back(terr->at(i));
    }
    terr->clear();
    delete terr;
    return  territoriesToAttack;
}
vector<Territory*>* Player::toAttack(Map &m){

    updatetoDefend(m);
    territoriesToAttack->clear();
    vector<Territory*>* result = DBG_NEW vector<Territory*>();
    for (int i=0; i<territoriesToDefend->size(); i++) {
        vector<Territory *> *terr = surroundingterritories(m, *territoriesToDefend->at(i));
        for (int j = 0; j < terr->size(); j++) {
            if (terr->at(j)->getterritory_owner()->getName().compare(territoriesToDefend->at(i)->getterritory_owner()->getName()) != 0) {
                bool exists = false;
                for (int k = 0; k < result->size(); k++) {
                    if (terr->at(j)->getterritory_name().compare(result->at(k)->getterritory_name()) == 0)exists = true;
                }
                if (!exists) {
                    result->push_back(terr->at(j));
                    break;
                }
            }
        }
        terr->clear();
        delete terr;
    }
    for (int k = 0; k<result->size(); k++) {
        int max = -1;
        int index = -1;
        int i = k;
        for ( ;i < result->size(); i++) {
            if (result->at(i)->getterritory_armycount() > max) {
                max = result->at(i)->getterritory_armycount();
                index = i;
            }
        }
        if (index!= k){
            iter_swap(result->begin()+index,result->begin()+k);
        }
    }
    for (int i = 0; i < result->size(); i++) {
        territoriesToAttack->push_back(result->at(i));
    }
    result->clear();
    delete result;
    return territoriesToAttack;

}

// definition of issueOrder which creates a specific Order
// object and adds it to the player's list of orders
void Player::issueOrder(Order* order)
{
    playerOlist->add(order);
}
//returns the Boolean value fi the players has captured a territory
bool Player::getcaptureTerritory() {return *capturedTerritory;}
//setter method for boolean value of capture territory
void Player::setcaptureTerritory(bool b) {*capturedTerritory = b;}
//adds a friend to the negotiated list
void Player::addnegotiateFriends(string s) {negotiatedFriends->push_back(DBG_NEW string(s));}
//clears the list (used at the end of each round)
void  Player::clearnegotiateFriends() {
    for (int i=0; i<negotiatedFriends->size(); i++){
        delete negotiatedFriends->at(i);
        negotiatedFriends->at(i) = NULL;
    }
    negotiatedFriends->clear();}
//Check if a player is in the list
bool Player::isNegotiatedFriend(string s) {
    for (int i =0 ;i< negotiatedFriends->size(); i++){
        if (negotiatedFriends->at(i)->compare(s)==0)return true;
    }
    return false;

}
//For a given territory on a map returns all surrounding territories
vector<Territory*>* Player::surroundingterritories(Map& m, Territory &l) {
    vector<Territory*>* terr = DBG_NEW vector<Territory*>;
    for (int i=0; i<m.getTerritories()->size(); i++){
        if(m.isAdjacent(m.getTerritories()->at(i),l)) terr->push_back(m.getTerritories()->at(i));
    }
    return terr;
}
vector<Order*>* Player::getOrderList(){
   return(playerOlist->retirevelist());
}
vector<Territory*>* Player::allnonFriendlies(Map &m){
    vector<Territory*>* result = DBG_NEW vector<Territory*>;
    vector<Territory*>* terr = m.getTerritories();
    for (int i=0; i<terr->size(); i++){
        if (terr->at(i)->getterritory_owner()->getName().compare(name)!=0) result->push_back(terr->at(i));
    }
    return result;
}
int Player::getContinentBonus(Map* m)
{
    int bonus = 0;
    for (auto continent : *m->getContinents()){
        if (continent->ownedByOnePlayer(this, m))
        {
            bonus += continent->getBonus();
        } 
    }
    return bonus;
}

