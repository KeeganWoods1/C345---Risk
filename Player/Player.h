#pragma once
#include <iostream>
#include <string>
#include <vector>
#include "Map.h"
#include "Map.cpp"


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

    // method to set the name of player
    void setName(string name); 
    
    // method to return name of player
    string getName();
    
    // get number of players playing the game
    int getPlayerCount(); 

    // method toDefend
    vector<Territory*> toDefend();
   
    // method to toAttack
    //  attackterr* toAttack();
  
    // method 
    // Order issueOrder();
};


