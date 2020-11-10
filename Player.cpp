#include "Player.h"
#include <iostream>
#include <string>
#include <vector>
using namespace std;


// default constructor definition
Player::Player()
{
    name = "";
}

// parametrized constructor definition
Player::Player(string playerName)
{
    // player's name is set to passed argument
    name = playerName;
    
    // each player owns a hand of cards
    playerHand = new Hand();

    // minimal number of armies for any player is 3
    const int MINARMIES = 3;

    //initialize player orderlist
    playerOlist = new Orderlist();

    territoriesToAttack = new vector<Territory*>();
    territoriesToDefend = new vector<Territory*>();
}

// destructor definition
Player::~Player()
{
    // avoid memory leaks
    delete playerHand;
    delete playerOlist;
    
    //Clear ToAttack
    for(int i = 0; i < territoriesToAttack->size(); i++)
    {
        delete territoriesToAttack->at(i);
        // avoid dangling pointers
        territoriesToAttack->at(i) = NULL;
    }

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

//stream insertion operator overload for printing a vector list of territory references
string Player::toString(vector<Territory*> t)
{
    string list = "Territories: \n";

    if(t.size() > 0)
    {
        for(int i=0; i<t.size(); i++)
        {
            list.append(t[i]->getterritory_name() + "\n");
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

// definition of method toDefend
// returning a list of territories to defend
vector<Territory*>* Player::toDefend()
{    
    return territoriesToDefend;
}

// definition of method toAttack
// returning a list of territories to attack
vector<Territory*>* Player::toAttack()
{   
    return territoriesToAttack;
}

// definition of issueOrder which creates a specific Order 
// object and adds it to the player's list of orders
void Player::issueOrder(Order* order)
{
    playerOlist->add(order);
    cout << endl << "After adding an order to the orderlist, the list is: " << endl;
    cout << *playerOlist << endl;
}
