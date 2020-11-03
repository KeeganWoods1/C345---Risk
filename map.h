#pragma once
#include "Player.h"
#include <iostream>
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
    //continent name of the territory
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

    //copy constructor
    Territory(const Territory*);

    Territory(int, string, Player*, int);

    //assignment operator
    Territory& operator = (const Territory&);

    //insertion operator
    friend ostream& operator << (ostream& out, const Territory& t);

    //destructor
    ~Territory();

    //territory name getter
    string getterritory_name();

    //territory name setter
    void setterritory_name(string);

    //continent name getter
    int getterritory_continent();

    //setter
    void setterritory_continent(int);

    //territory owner getter
    Player* getterritory_owner();

    //setter
    void setterritory_owner(Player*);

    //army count getter
    int getterritory_armycount();

    //army count setter
    void setterritory_armycount(int);

    string toString();

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

    vector<Territory>* territoryListPtr;

public:
    //default constructor
    Map();

    //one int parameter constructor
    Map(int);

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
};
