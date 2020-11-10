#include "map.h"
#include <iostream>

//Class Territory
//constructors
Territory::Territory() {
    territory_name = "default territory";
    territory_continent = 0;
    territory_owner = new Player();
    territory_armycount = 0;
}

Territory::Territory(const Territory* territory) {

    territory_continent = territory->territory_continent;
    territory_name = territory->territory_name;
    territory_owner = territory->territory_owner;
    territory_armycount = territory->territory_armycount;
}

Territory::Territory(int continent,string name, Player* player, int army) {
    territory_continent = continent;
    territory_name = name;
    territory_owner = player;
    territory_armycount= army;
}

//assignment operator
Territory& Territory::operator=(const Territory& territory)
{
    this->territory_continent = territory.territory_continent;
    this->territory_name = territory.territory_name;
    this->territory_owner = territory.territory_owner;
    this->territory_armycount = territory.territory_armycount;
    return *this;
}

//Stream insertion operator overload to output a territory
ostream& operator << (ostream& out, const Territory& t)
{
    out << "Territory of " << t.territory_name << " Owned by: " << *t.territory_owner << endl;

    return out;
}

//destructor
Territory::~Territory() {
    territory_owner = NULL;
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

void Territory::setterritory_owner(Player* p)
{
    territory_owner = p;
}

string Territory::toString()
{
    return territory_name;
}

//constructors
Map::Map() {
    this->adjacent_matrix = 0;
    this->vertices = 0;
}

Map::Map(const Map *map) {
    this->adjacent_matrix = map->adjacent_matrix;
    this->vertices = map->vertices;
}

Map::Map(int vertices, vector<Territory*>* territoryList) {
    this->vertices = vertices;
    adjacent_matrix = new bool* [vertices];
    //initialize the 2d array with false
    for (int i = 0; i < vertices; i++) {
        adjacent_matrix[i] = new bool[vertices];
        for (int j = 0; j < vertices; j++)
            adjacent_matrix[i][j] = false;
    }
    //Set the territories list from loaded map file
    territoryListPtr = territoryList;
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

//destructor
Map::~Map() {
    delete[] adjacent_matrix;
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
