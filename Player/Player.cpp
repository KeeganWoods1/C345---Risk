#include "Player.h"
#include <iostream>
#include <string>
#include <vector>
using namespace std;


int playerCount = 0;
string name;
vector<Territory*> territories;
Hand* playerCards;
Orderlist* playerOlist;

// default constructor definition
Player::Player()
{
    name = "";

    // each player owns a hand of cards
    playerCards = new Hand();
    
    // minimal number of armies for any player is 3
    const int MINARMIES = 3;

    // number of territories at the start is 4
    Territory* terr1 = new Territory();
    Territory* terr2 = new Territory();
    Territory* terr3 = new Territory();
    Territory* terr4 = new Territory();
    territories.push_back(terr1);
    territories.push_back(terr2);
    territories.push_back(terr3);
    territories.push_back(terr4);

    // increase number of players
    playerCount = playerCount + 1;
}

// destructor definition
// Player::~Player()
// {
   // avoid memory leaks
    // delete playerCards;
    // delete terr1;
    // delete terr2;
    // delete terr3;
    // delete terr4;
    // avoid dangling pointers
    // playerCards = NULL;
    // terr1 = NULL;
    // terr2 = NULL;
    // terr3 = NULL;
    // terr4 = NULL;
// }

// copy constructor definition
Player::Player(const Player& copyPlayer) 
{
    this->name = copyPlayer.name;
}

// assignment operator
Player& Player::operator = (const Player& o)
{
    return *this;
}

// stream insertion operator
ostream &operator << (ostream &output, const Player &o)
{
    output << "Player name: " << o.name;
    return output;
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

// definition of method to return player count
int Player::getPlayerCount()
{
    return playerCount;
}

// definition of method to get number of 
// territories owned by the player
int Player::getNumTerrOwned()
{
    return territories.size();
}

// definition of method toDefend
// returning a list of territories to defend
vector<Territory*> Territory::toDefend()
{
    Territory* ob1 = new Territory();
    Territory* ob2 = new Territory();
    for(int i = 0; i < 2; i++)
    {
        ob1->territory_name = "Canada";
        ob2->territory_name = "Mexico";
        territories.push_back(ob1);
        territories.push_back(ob2);
    }   
    return territories;
   // delete objects to prevent memory leaks
   for(int j = 0; j < 2; j++){
       delete territories.at(j);
   }
   territories.clear();
}

// definition of method toAttack
// returning a list of territories to attack
vector<Territory*> Territory::toAttack()
{
    vector<Territory*> territories;

    Territory* ob3 = new Territory();
    Territory* ob4 = new Territory();
    for(int i =0; i < 2; i++)
    {
        ob3->territory_name = "France";
        ob4->territory_name = "Italy";
        territories.push_back(ob3);
        territories.push_back(ob4);
    }   
    return territories;
   // delete objects to prevent memory leaks
   for(int j = 0; j <2; j++){
       delete territories.at(j);
       territories.at(j) = NULL;
   }
   territories.clear();
}

// definition of issueOrder which creates an Order 
// object and adds it to the player's list of orders
void Player::issueOrder()
{
    Order* newOrder;
    newOrder = new Order;
    playerOlist->add(*newOrder);
}
