#pragma once
#include "Player.h"
#include <iostream>
#include <vector>
using namespace std;

/*manually create territories, and the adjacency between territories,
* and a way to verify that the map is connected (how?)
*manually create continents, and check whether they are defined, and create sub-graphs, and each countries belongs to one continent.
*territories or countries node [territories]
* 1 Alaska 1 44 83 <~~ the first number is the number of the country (they do have to be in order)
* the next one is what continent it belongs to. the other two numbers are the x and y co-ordinates
* of the circle that will be put on that country
*/

class Player;

/*
 * manually creating territories, and using the 2d array adjacency array to find whether connected or not.
 *
 */

//declaration of Territory class
class Territory {
private:
    //continent id of the territory
    int territory_continent;
    //name of a territory
    string territory_name;
    //the owner of a territory
    Player* territory_owner;
    //the amount of army in a territory
    int territory_armycount;

public:
    //default constructor
    Territory();
    //Parameterized constructor
    Territory(int, string, Player*, int);
    //copy constructor
    Territory(const Territory*);

    //assignment operator
    Territory& operator = (const Territory&);

    //insertion operator
    friend ostream& operator << (ostream& out, const Territory& t);

    //setters
    void setterritory_name(string);
    void setterritory_continent(int);
    void setterritory_owner(Player*);
    void setterritory_armycount(int a);

    //getters
    string getterritory_name();
    int getterritory_continent();
    Player* getterritory_owner();
    int getterritory_armycount();

    //destructor
    ~Territory();
};

class Continent {
private:
    string name;
    //continent id
    int id;
    //continent bonus
    int bonus;
    //territories in continent
    vector<Territory*> territoriesInContinent;

public:
    Continent();
    Continent(string, int, int, vector<Territory*>);

    //copy constructor
    Continent(const Continent*);

    //assignment operator
    Continent& operator = (const Continent&);

    //insertion operator
    friend ostream& operator << (ostream& out, const Continent& t);

    //getters and setters
    void setName(string name);
    void setId(int i);
    void setBonus(int b);
    int getId();
    int getBonus();
    string getName();
    bool ownedByOnePlayer(Player* aPlayer);
    ~Continent();
};

//declaration of Map class with its members
class Map {
private:
    //2D boolean matrix to represent Adjancency Matrix
    bool** adjacent_matrix;
    //int to store number of vertices (territories)
    int vertices;
    //int to store number of vertices (continents)
    int continentVertices;
    vector<Territory*>* territoryListPtr;
    vector<Continent*>* continentListPtr;

public:
    //constructors
    Map();
    Map(int);
    Map(int vertices, vector<Territory*>* territoryList, vector<Continent*>* continentListPtr);

    //copy constructor
    Map(const Map*);

    //assignment operator
    Map& operator = (const Map&);

    //destructor
    ~Map();

    //add an edge between two vertices
    void addBorder(int, int);

    //display the Adjancency Matrix
    void toString();

    //traverse the passed graph
    void transverse(int, bool*);

    //verify a graph whether connected or not
    bool Validate();

    //Get territories list
    vector<Territory*>* getTerritories();
    //Get continents list
    vector<Continent*>* getContinents();

    //Get adjacent method
    bool isAdjacent(Territory a, Territory b);

};
