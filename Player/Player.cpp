#include "Player.h"
#include "Map.h"
#include <iostream>
#include <string>
#include <vector>
using namespace std;


// default constructor definition
Player::Player()
{
    name = "";
    playerCount = 0;
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
Player::~Player()
{
    // avoid memory leaks
    delete playerHand;
    delete playerOlist;

    for(int i = 0; i < territories.size(); i++)
    {
        delete territories.at(i);
        // avoid dangling pointers
        territories.at(i) = NULL;
    }
    territories.clear();
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
vector<Territory*> Player::toDefend()
{
    territories.at(0)->territory_name = "Canada";
    territories.at(1)->territory_name = "Mexico";
    territories.at(2)->territory_name = "Argentina";
    territories.at(3)->territory_name = "Brazil";
    
    return territories;
}

// definition of method toAttack
// returning a list of territories to attack
vector<Territory*> Player::toAttack()
{
    for(int i = 4; i < 8; i++)
    {
        Territory* oi = new Territory();
        territories.push_back(oi);
    }
    territories.at(4)->territory_name = "France";
    territories.at(5)->territory_name = "Italy";
    territories.at(6)->territory_name = "Greece";
    territories.at(7)->territory_name = "Australia";
    
    return territories;
}

// definition of issueOrder which creates a specific Order 
// object and adds it to the player's list of orders
void Player::issueOrder()
{
    playerOlist = new Orderlist();
    Territory* t1 = new Territory("t1");
    Territory* t2 = new Territory("t2");
    Advanceorder* o1 = new Advanceorder(1, *t1, *t2);
    playerOlist->add(*o1);
    cout << endl << "After adding an order to the orderlist, the size of the list is: " 
    << playerOlist->getPlayerolist()->size() << endl;
    Territory* t3 = new Territory("t3");
    Deployorder* o2 = new Deployorder(1, *t3);
    playerOlist->add(*o2);
    cout << "After adding a 2nd order to the orderlist, the size of the list is: " 
    << playerOlist->getPlayerolist()->size() << endl << endl;
    
    // Avoid memory leaks
    delete t1;
    delete t2;
    delete o1;
    delete t3;
    delete o2;
    // avoid dangling pointers
    t1 = NULL;
    t2 = NULL;
    o1 = NULL;
    t3 = NULL;
    o2 = NULL;
}
