#include "map.h"
#include <iostream>
//#include <crtdbg.h>
#ifdef _DEBUG
#define DBG_NEW new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
// Replace _NORMAL_BLOCK with _CLIENT_BLOCK if you want the
// allocations to be of _CLIENT_BLOCK type
#else
#define DBG_NEW new
#endif

//Class Territory
//constructors
Territory::Territory() {
    territory_name = "default territory";
    territory_continent = 0;
    territory_owner = DBG_NEW Player();
    territory_armycount = 0;
}

//Parameterized constructor
Territory::Territory(int continent,string name, Player* player, int army) {
    territory_continent = continent;
    territory_name = name;
    territory_owner = player;
    territory_armycount= army;
}

//Copy constructor
Territory::Territory(const Territory* territory) {
    territory_continent = territory->territory_continent;
    territory_name = territory->territory_name;
    territory_owner = territory->territory_owner;
    territory_armycount = territory->territory_armycount;
}

//assignment operator
Territory& Territory::operator=(const Territory& territory) {
    this->territory_continent = territory.territory_continent;
    this->territory_name = territory.territory_name;
    this->territory_owner = territory.territory_owner;
    this->territory_armycount = territory.territory_armycount;
    return *this;
}

//Stream insertion operator overload to output a territory
ostream& operator << (ostream& out, const Territory& t) {
    out << "Territory of " << t.territory_name << " Owned by: " << *t.territory_owner <<
    +", Occupied by: " << t.territory_armycount << " troops" << endl;
    return out;
}

//getters
string Territory::getterritory_name() {
    return territory_name;
}
int Territory::getterritory_continent() {
    return territory_continent;
}
Player* Territory::getterritory_owner() {
    return territory_owner;
}
int Territory::getterritory_armycount() {
    return territory_armycount;
}
void Territory::setterritory_armycount(int a) {
    territory_armycount = a;
}

//setters
void Territory::setterritory_name(string s) {
    territory_name = s;
}
void Territory::setterritory_owner(Player* p) {
    territory_owner = p;
}

//destructor
Territory::~Territory() {
    territory_owner = NULL;
}

//Class Continent
Continent::Continent() {
    name = "";
    id = 0;
    bonus = 0;
}

Continent::Continent(string n, int i, int b, vector<Territory*> terr) {
    name = n;
    id = i;
    bonus = b;
    for (int i=0; i<terr.size(); i++) {
        territoriesInContinent.push_back(terr[i]);
    }
}

//getters and setters
void Continent::setName(string n) {
    name = n;
}
void Continent::setId(int i) {
    id = i;
}
void Continent::setBonus(int b) {
    id = b;
}

string Continent::getName() {
    return name;
}
int Continent::getId() {
    return id;
}
int Continent::getBonus() {
    return bonus;
}

//insertion operator (toString)
ostream& operator << (ostream& out, const Continent& c) {
    out << c.id <<" Continent " << c.name << ", has bonus armies of " << c.bonus
    << "\nList of territories ("<< c.territoriesInContinent.size() <<")\n[\n";
    for(auto T : c.territoriesInContinent){
        out << T->getterritory_name() << "\n";
    }
    out << "]\n" << endl;
    return out;
}

Continent::~Continent() {
    territoriesInContinent.clear();
    for (int i = 0; i < territoriesInContinent.size(); i++) {
        delete territoriesInContinent.at(i);
    }  
}

//Class Map
//constructors
Map::Map() {
    this->adjacent_matrix = 0;
    this->vertices = 0;
}

Map::Map(const Map *map) {
    this->vertices = map->vertices;
    this->adjacent_matrix = DBG_NEW bool* [this->vertices];
    for (int i = 0; i < vertices; i++) {
        this->adjacent_matrix[i] = DBG_NEW bool [this->vertices];
        for (int j = 0; j < vertices; j++)
            adjacent_matrix[i][j] = map->adjacent_matrix[i][j];
    }
    this->territoryListPtr = DBG_NEW vector<Territory*>;
    for (int i = 0; i < map->territoryListPtr->size(); i++) {
        territoryListPtr->push_back(DBG_NEW Territory(map->territoryListPtr->at(i)));
    }

}

Map::Map(int vertices, vector<Territory*>* territoryList) {
    this->vertices = vertices;
    adjacent_matrix = DBG_NEW bool* [vertices];
    //initialize the 2d array with false
    for (int i = 0; i < vertices; i++) {
        adjacent_matrix[i] = DBG_NEW bool[vertices];
        for (int j = 0; j < vertices; j++)
            adjacent_matrix[i][j] = false;
    }
    //Set the territories list from loaded map file
    territoryListPtr = DBG_NEW vector<Territory*>;
    for (int i = 0; i < territoryList->size(); i++) {
        territoryListPtr->push_back(territoryList->at(i));
    }
}
//destructor
Map::~Map() {
    for (int i = 0; i < vertices; i++) {
        if(adjacent_matrix[i]!= NULL)delete[] adjacent_matrix[i];
        adjacent_matrix[i] = NULL;
    }
    delete[] adjacent_matrix;
    adjacent_matrix = NULL;
    for (int i = 0; i < territoryListPtr->size(); i++) {
        delete territoryListPtr->at(i);
    }
    territoryListPtr->clear();
    delete territoryListPtr;
}

//assignment operator
Map& Map::operator=(const Map& map)
{
    this->adjacent_matrix = map.adjacent_matrix;
    this->vertices = map.vertices;
    return *this;
}

vector<Territory*>* Map::getTerritories()
{
    return territoryListPtr;
}

//add an border between two v's
void Map::addBorder(int i, int j) {
    adjacent_matrix[i][j] = true;
    adjacent_matrix[j][i] = true;
}

//to display the matrix
void Map::toString() {
    std::cout << "Output Matrix: " << std::endl;
    std::cout << "     ";
    for (int x = 0; x < vertices; x++) {
        std::cout << x << "   ";
    }
    std::cout << std::endl;
    for (int i = 0; i < vertices; i++) {
        if (i>=10){
            std::cout << " " << i << "   ";
            for (int j = 0; j < vertices; j++)
                std::cout << adjacent_matrix[i][j] << "   ";
            std::cout << "\n";
        }
        else{
            std::cout << "  "<< i << "   ";
            for (int j = 0; j < vertices; j++)
                std::cout << adjacent_matrix[i][j] << "   ";
            std::cout << "\n";
        }
    }
}

//transvering matrix
void Map::transverse(int u, bool visited[]) {
    visited[u] = true;
    for (int v = 0; v < vertices; v++) {
        if (adjacent_matrix[u][v]) {
            if (!visited[v])
                transverse(v, visited);
        }
    }
}

//This method verifies whether the map is connected or not
//checks whether the nodes (transversal) are visible -> true
//not visible -> false

bool Map::Validate() {
    //Check that territories form a connected graph
    bool* visited = new bool[vertices];
    for (int u = 0; u < vertices; u++) {
        for (int i = 0; i < vertices; i++)
            visited[i] = false;
        transverse(u, visited);
        for (int i = 0; i < vertices; i++) {
            if (!visited[i]) //if there is a node, not visited by transversal, graph is not connected
                return false;
        }
    }
    //TODO:check that continents form a connected sub-graph
    

    return true;
}

bool Map::isAdjacent(Territory a, Territory b) {
    int indexa;
    int indexb;
    for (int i=0; i<territoryListPtr->size(); i++){
        if (territoryListPtr->at(i)->getterritory_name().compare(a.getterritory_name())==0)indexa = i;
        if (territoryListPtr->at(i)->getterritory_name().compare(b.getterritory_name())==0)indexb = i;
    }
    return(adjacent_matrix[indexa][indexb]);

}
