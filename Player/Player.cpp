#include "Player.h"
#include <iostream>
#include <string>
using namespace std;

int counter = 0;
std::string name;

// default constructor implementation 
Player::Player()
{
    playerCount = new int;
    counter = counter+1;
    // increase number of players
    playerCount = &counter;	
}

// method to set the name of player
// void setName(std::string playerName){
    // 
    // name = playerName;
// }

// implementation of method to return player count
int Player::getPlayerCount(){
    return *playerCount;
}

// implementation of method toDefend
// returning a list of territories to defend
vector<Territory*> Territory::toDefend(){
    int territoriessize = 50;
    vector<Territory*> territories;
    Territory* p = NULL;

   // Load up the vector with territory objects
   for (int i = 0; i < territoriessize; i++) {
      p = new Territory();
      territories.push_back(p);
   }
}
