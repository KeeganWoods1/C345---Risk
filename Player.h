#pragma once
#include "map.h"
#include "Orders.h"
#include "Cards.h"
#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Territory;
class Order;
class Orderlist;
class Advanceorder;
class Deck;
class Hand;

class Player
{
    private:
    // the number of players playing the game
    int playerCount;
    
    // name of player
    string name;
    
    // minimum number of armies for a player
    static const int MINARMIES;

    // player owns a collection of territories
    vector<Territory*> territoriesToDefend;
    vector<Territory*> territoriesToAttack;

    // player owns a hand of cards
    Hand* playerHand;

    // player's orderlist
    Orderlist* playerOlist;

    public:
    // default constructor
    Player();

    // parametrized constructor
    Player(string);

    // destructor
    ~Player();

    //copy constructor
    Player(const Player&);

    // assignment operator
    Player& operator = (const Player& o);
     
    // stream insertion operator
    friend ostream &operator << (ostream &output, const Player &o);

    //stream insertion operator overload for printing a vector list of territory references
    friend ostream& operator << (ostream& out, const vector<Territory*>& t);

    // method to set the name of player
    void setName(string name); 
    
    // method to return name of player
    string getName();
    
    // get number of players playing the game
    int getPlayerCount(); 

    // get number of territories owned by the player
    int getNumTerrOwned();

    // get hand owned by player
    Hand* getHand();

    // get player's orderlist
    Orderlist* getPlayerlist();

    // method toDefend which returns a list 
    // of territories to defend
    vector<Territory*> toDefend();
   
    // method toAttack which returns a list 
    // of territories to attack
    vector<Territory*> toAttack();

    string toString(vector<Territory*> t);
  
    // method issueOrder which creates an Order 
    // object and puts it in the player’s list 
    // of orders
    void issueOrder(Order* order);
};


