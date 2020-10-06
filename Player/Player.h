#pragma once
#include <iostream>
#include <string>
#include <vector>
#include "Map.h"
using namespace std;

class Player 
{
    private:
    // the number of players playing the game
    int* playerCount;
    
    // name of player
    std::string name;

    // Collection of territories
    vector<Territory*> territories;

    public:
    // default constructor
    Player();

    //copy constructor
    Player(const Player& copyPlayer);
     
    // stream insertion operator
    friend std::ostream& operator<<(std::ostream&, const Player&);

    // method to set the name of player
    void setName(string name); 
    
    // method to return name of player
    string getName();
    
    // get number of players playing the game
    int getPlayerCount(); 

    // method toDefend
    vector<Territory*> toDefend();
   
    // method to toAttack
    vector<Territory*> toAttack();
  
    // method 
    // Order issueOrder();
};


