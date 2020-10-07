#include "Player.h"
#include <iostream>
#include <string>
using namespace std;


int* playerCount;
int counter = 0;
string* name;


// default constructor definition
Player::Player()
{
    name = new string;
    name = NULL;
    playerCount = new int;
    counter = counter+1;
    // increase number of players
    playerCount = &counter;
}

// destructor definition
// Player::~Player(){
    // delete playerCount;
    // delete name;
// }

// copy constructor definition
Player::Player(const Player& copyPlayer) 
{
    this->name = copyPlayer.name;
}

// stream insertion operator
//std::ostream& operator<<(std::ostream&, c
//}

// method to set the name of player
void Player::setName(string playerName)
{
    name = &playerName;
}

// method to return name of player
string Player::getName(){
    return *name;
}

// definition of method to return player co
int Player::getPlayerCount(){
    return *playerCount;
}

// definition of method toDefend
// returning a list of territories to defen
vector<Territory*> Territory::toDefend(){
    vector<Territory*> territories;

    Territory* ob1 = new Territory();
    Territory* ob2 = new Territory();
    for(int i =0; i < 2; i++)
    {
        ob1->territory_name = "Canada";
        ob2->territory_name = "Mexico";
        territories.push_back(ob1);
        territories.push_back(ob2);
    }   
    return territories;
   // delete objects to prevent memory leak
   for(int j = 0; j <2; j++){
       delete territories.at(j);
   }
   territories.clear();
}

// definition of method toAttack
// returning a list of territories to attac
vector<Territory*> Territory::toAttack(){
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
   // delete objects to prevent memory leak
   for(int j = 0; j <2; j++){
       delete territories.at(j);
   }
   territories.clear();
}
