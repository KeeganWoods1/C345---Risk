#include "Player.h"
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;


// default constructor definition
Player::Player()
{
    name = "";
    capturedTerritory = new bool(false);
}

// parametrized constructor definition
Player::Player(string playerName)
{
    // player's name is set to passed argument
    name = playerName;

    negotiatedFriends = new vector<string*>();
    // each player owns a hand of cards
    playerHand = new Hand();

    capturedTerritory = new bool(false);
    // minimal number of armies for any player is 3
    const int MINARMIES = 3;


    //initialize player orderlist
    playerOlist = new Orderlist();
    territoriesToDefend = new vector<Territory*>;
}

// destructor definition
Player::~Player()
{
    // avoid memory leaks
    delete playerHand;
    delete playerOlist;
    delete capturedTerritory;
    capturedTerritory = NULL;

    for (int i=0; i<negotiatedFriends->size(); i++){
        delete negotiatedFriends->at(i);
        negotiatedFriends->at(i) = NULL;
    }
    delete negotiatedFriends;
    negotiatedFriends = NULL;


    //Clear ToDefend
    for(int i = 0; i < territoriesToDefend->size(); i++)
    {
        delete territoriesToDefend->at(i);
        // avoid dangling pointers
        territoriesToDefend->at(i) = NULL;
    }
}

// copy constructor definition
Player::Player(const Player &player)
{
    name = player.name;
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

vector<Territory*>* Player::gettoDefend() 
{
    return territoriesToDefend;
}

//new method updates the todefend list with all new territories
void Player::updatetoDefend(Map &m){
    vector<Territory*>* terr2def = new vector<Territory*>;
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
    vector<Territory *> *terr2 = new vector<Territory *>;

    for (int j =0; j<territoriesToDefend->size(); j++) {
        Territory t = territoriesToDefend->at(j);
        vector<Territory *> *terr = surroundingterritories(m, t);
        for (int i = 0; i < terr->size(); i++) {
            if (terr->at(i)->getterritory_owner()->getName().compare(t.getterritory_owner()->getName()) != 0)
                terr2->push_back(territoriesToDefend->at(j));
        }
    }
    vector<Territory *>* terr = new vector<Territory*>();
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
    return  terr;
}

// definition of method toAttack
// returning a list of territories to attack
vector<Territory*>* Player::toAttack(Map &m,Territory &t)
{
    vector<Territory*>* terr = surroundingterritories(m,t);
    vector<Territory*>* terr2 = new vector<Territory*>;
    for (int i=0; i <terr->size(); i++){
        if (terr->at(i)->getterritory_owner()->getName().compare(t.getterritory_owner()->getName())!=0)terr2->push_back(terr->at(i));
    }
    terr = new vector<Territory*>();
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
    return  terr;
}
vector<Territory*>* Player::toAttack(Map &m){
    vector<Territory*>* result = new vector<Territory*>();
    for (int i=0; i<territoriesToDefend->size(); i++) {
        vector<Territory *> *terr = surroundingterritories(m, *territoriesToDefend->at(i));
        for (int j = 0; j < terr->size(); j++) {
            if (terr->at(j)->getterritory_owner()->getName().compare(territoriesToDefend->at(i)->getterritory_owner()->getName()) != 0) {
                bool exists = false;
                for (int k = 0; k < result->size(); k++) {
                    if (terr->at(j)->getterritory_name().compare(result->at(k)->getterritory_name()) == 0)exists = true;
                }
                if (!exists)result->push_back(terr->at(j));
            }
        }
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
    return result;

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
void Player::addnegotiateFriends(string s) {negotiatedFriends->push_back(new string(s));}
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
    vector<Territory*>* terr = new vector<Territory*>;
    for (int i=0; i<m.getTerritories()->size(); i++){
        if(m.isAdjacent(m.getTerritories()->at(i),l)) terr->push_back(m.getTerritories()->at(i));
    }
    return terr;
}
vector<Order*>* Player::getOrderList(){
   return(playerOlist->retirevelist());
}
vector<Territory*>* Player::allnonFriendlies(Map &m){
    vector<Territory*>* result = new vector<Territory*>;
    vector<Territory*>* terr = m.getTerritories();
    for (int i=0; i<terr->size(); i++){
        if (terr->at(i)->getterritory_owner()->getName().compare(name)!=0) result->push_back(terr->at(i));
    }
    return result;
}

void Player::remove(Territory* t)
{
    vector<Territory*>::iterator it = territoriesToDefend->begin();
    for (; it!=territoriesToDefend->end(); it++)
    {
        if((*it)->getterritory_name() == t->getterritory_name())
        {
            territoriesToDefend->erase(it);
        }
    }
}
