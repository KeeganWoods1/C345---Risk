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

    // name of player
    string name;

    //Player's reinforcement armies pool
    int reinforcementPool = 0;

    // minimum number of armies for a player
    static const int MINARMIES;

    // captured a territory boolean (for card distribution after teh round);
    bool* capturedTerritory;

    vector<string*>* negotiatedFriends;

    // player owns a collection of territories
    vector<Territory*>* territoriesToDefend;
    vector<Territory*>* territoriesToAttack;

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

    //Add reinforcements to pool
    void addReinforcements(int);

    //get current amount of reinforcements owned by player
    int getCurrentReinforcements();
    //set Current amount of reinforcements owned by player
    void setCurrentReinforcements(int i);

    // method to set the name of player
    void setName(string name);

    // method to return name of player
    string getName();

    // get number of territories owned by the player
    int getNumTerrOwned();

    // get hand owned by player
    Hand* getHand();

    // get player's orderlist
    Orderlist* getPlayerlist();

    // method toDefend which returns a list
    // of territories to defend
    vector<Territory*>* toDefend();

    // method toAttack which returns a list
    // of territories to attack
    vector<Territory*>* toAttack();

    string toString(vector<Territory*> t);

    // method issueOrder which creates an Order
    // object and puts it in the player’s list
    // of orders
    void issueOrder(Order* order);
    //Getter method for boolean capture territory
    bool getcaptureTerritory();
    //setter method for capture territory
    void setcaptureTerritory(bool b);
//adds a player to the negotiated friends list
    void addnegotiateFriends(string s);
    //clears the list
    void clearnegotiateFriends();
    //checks if a name is in the list
    bool isNegotiatedFriend(string s);
//method that updates the list of territories that the player owns UNTESTED
    void updateToDefend(Map m);
    //method that updates the list of territories that the player can attack UNTESTED
    void updateToAttack(Map m);
    //For a given territory on a map returns all surrounding territories
    vector<Territory*>* surroundingterritories(Map& m,Territory l);

};
