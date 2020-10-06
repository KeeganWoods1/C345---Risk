#include "Player.h"
#include <iostream>
#include <string>
using namespace std;

int counter = 0;
std::string name;

// default constructor definition
Player::Player()
{
    playerCount = new int;
    counter = counter+1;
    // increase number of players
    playerCount = &counter;	
}

// copy constructor definition
Player::Player(const Player& copyPlayer) 
{
    this->name = copyPlayer.name;
}

// stream insertion operator
std::ostream& operator<<(std::ostream&, const Player&){
}

// method to set the name of player
// void setName(std::string playerName){
    // 
    // name = playerName;
// }

// definition of method to return player count
int Player::getPlayerCount(){
    return *playerCount;
}

// definition of method toDefend
// returning a list of territories to defend
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
   // delete objects to prevent memory leaks
   for(int j = 0; j <2; j++){
       delete territories.at(j);
   }
   territories.clear();
}

// definition of method toAttack
// returning a list of territories to attack
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
   // delete objects to prevent memory leaks
   for(int j = 0; j <2; j++){
       delete territories.at(j);
   }
   territories.clear();
}

