#pragma once
#include "map.h"
#include "Orders.h"
#include "Cards.h"
#include "PlayerStrategies.h"
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
class PlayerStrategy;
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
    //the paleyrs stragety
    PlayerStrategy* playerstrategy;

    vector<string*>* negotiatedFriends;
    // player owns a collection of territories
    vector<Territory*>* territoriesToDefend;
    vector<Territory*>* territoriesToAttack;
    vector<Territory*>* surroundingterr;
    // player owns a hand of cards
    Hand* playerHand;
    // player's orderlist
    Orderlist* playerOlist;
    //bonus value for continents owned
    int continentBonus;

public:
    // default constructor
    Player();
    void clear();

    // parametrized constructor
    Player(string, PlayerStrategy*);

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
    vector<Territory*>* toDefend(Map &m);
    //returns the todefend list
    vector<Territory*>* gettoDefend(Map& m);

    // method toAttack which returns a list
    // of territories to attack
    vector<Territory*>* toAttack(Map &m,Territory& t);
    //returns all possible territories to attack
    vector<Territory*>* toAttack(Map &m);
    //returns all enemy territories
    vector<Territory*>* allnonFriendlies(Map &m);

    string toString(vector<Territory*>* t);

    // method issueOrder which creates an Order
    // object and puts it in the player’s list
    // of orders
    void issueOrder(Map* m, vector<Player*>* pl);
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
    //For a given territory on a map returns all surrounding territories
    static vector<Territory*>* surroundingterritories(Map& m,Territory &l);
    //updates the lsit of territories to defend
    void updatetoDefend(Map &m);
    //returns orderlist
    vector<Order*>* getOrderList();
    //returns the bonus troops awarded for owning territories
    int getContinentBonus(Map* m);
    //adds a single order to the list
    void addOrder(Order* o);
    vector<Territory*>* getterritoriesToAttack();
};


