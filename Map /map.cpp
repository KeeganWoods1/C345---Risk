#include <iostream>
#include "map.h"
#include <list>
using namespace std;

//default constructor
Territory::Territory() :territory_id(),territory_name(), territory_continent() {
}

Territory::Territory(int territory_id, string territory_name, int territory_continent)
        : territory_id(), territory_name(territory_name), territory_continent(territory_continent){
}

Territory::Territory(int territory_id,string territory_name, int territory_continent, vector<Territory*> neighboring_countries)
        :territory_id(), territory_name(territory_name), territory_continent(territory_continent), neighboring_countries(neighboring_countries) {
}

Territory& Territory::operator=(const Territory& territory){
    return *(new Territory(territory));
}

/* TODO need player class for this */

int Territory::getArmies()
{
    return territory_armycount;
}

bool Territory::setArmies(int armies)
{
    if (armies >= 0)
    {
        territory_armycount = armies;
        return true;
    }
    return false;
}

/*TODO need player who owns the territory (copy constructor)  */

//returns continent
int Territory::getContinent()
{
    return territory_continent;
}

//returns neighbouring country
vector<Territory*> Territory::getAdjacent()
{
    return neighboring_countries;
}

//returns what is the country
int Territory::getId()
{
    return territory_id;
}

//String method for getting country name
string Territory::getTerritoryName()
{
    return string(territory_name);
}

//adds element to the end of the vector neighboring_countries to this specfic territory
bool Territory::addBorder(Territory* territory)
{
    if (territory != NULL && territory->territory_name != "")
    {
        neighboring_countries.push_back(territory);
        return true;
    }
    return false;
}

/* TODO need player */
//return territory name and how many armies do they have, and territories

Continent::Continent() :continent_name() {
}

//copy constructor
Continent::Continent(const Continent& continent) {
    this->continent_name = continent.continent_name;
    for (auto adjNode : continent.territories) {
        this->territories.push_back(new Territory(*adjNode));
    }
    for (auto adjNode : continent.neighboring_countries) {
        this->neighboring_countries.push_back(new Continent(*adjNode));
    }
}

//assignment operator
Continent& Continent::operator=(const Continent& continent)
{
    return *(new Continent(continent));
}

//returns the size of the territories
int Continent::territoriesSize()
{
    return static_cast<int>(territories.size());
}

//gets continent name
int Continent::getId()
{
    return continent_id;
}

//adds element to the end of the vector neighboring_countries to this specific continent
bool Continent::addTerritory(Territory* territory)
{
    if (territory != NULL && territory->getTerritoryName() != "")
    {
        territories.push_back(territory);
        return true;
    }
    return false;
}

//adds element to the end of the vector to this specfic continent
vector<Territory> Continent::getTerritories()
{
    vector<Territory> territories;
    territories.reserve(territories.size());
    for (int i = 0; i < territories.size(); i++) {
        territories.push_back(territories[i]);
    }
    return territories;
}




//default constructors
Map::Map() = default;

//constructor
Map::Map(int i) {
}

//copy constructor
Map::Map(const Map& map)
{
    this-> numberOfContinents = map.numberOfContinents;
    for (auto continent : map.continents) {
        this->continents.push_back(new Continent(*continent));
    }
    for (auto territory : map.territories) {
        this->territories.push_back(new Territory(*territory));
    }
}

/* Still unsure about how to implement this, but i'm trying this
 * This method checks whether the Graph is first connected, by Depth First Search
 * Do i do this for every node in this case?
 */
bool Map::validate()
{
    if (!isConnected())
    {
        return false;
    }
    return true;
}

//Assignment operator
Map& Map::operator=(const Map& map){
    return *(new Map(map));
}

//checks if continents are empty?
bool Map::checkTerritories(){
    list<int> ids;

    for (auto continent : continents) {
    }

    ids.sort();
    ids.unique();

    if (ids.size() != territories.size())
        return 0;
}

bool Map::isConnected() {
    //int continents_size = getContinentsSize();
    int territories_size = getTerritoriesSize();

    for (int i = 0; i < territories_size; ++i){
        Territory* root_node = territories[i];
        vector<bool> visited_territories(territories_size, false);
        DFS(root_node, visited_territories);
        for (bool vis : visited_territories){
            if (!vis)
            {
                cout << "territories are not connected" << endl;
                return false;
            }
        }
    }
    cout << "territories are connected" << endl;
    return true;
}

//checks whether the territory number has been visited before
void Map::DFS(Territory* startNode, vector<bool>& visited){
    int number = startNode -> getId();
    visited[number] = true;

    for (Territory* adj_node : startNode->getAdjacent()){
        int adj_id = adj_node -> getId();
        if (!visited[adj_id]){
            DFS(adj_node, visited);
        }
    }
}

//adds territory to map vector list
bool Map::addTerritory(Territory* territory) {
    if (territory != nullptr && territory->getTerritoryName() != "")
    {
        territories.push_back(territory);
        continents[territory->getContinent()]->addTerritory(territory);
        return true;
    }
    return false;
}

//adds continent to the map vector list
bool Map::addContinent(Continent* continent) {
    if (continent != nullptr)
    {
        continents.push_back(continent);
        return true;
    }
    return false;
}

//getter for vector list getTerritories
vector<Territory> Map::getTerritories() {
    vector<Territory> territories;
    for (int i = 0; i<territories.size(); i++) {
        territories.push_back(*(new Territory(territories[i])));
    }
    return territories;
}

//getter for vector list getContinents
vector<Continent> Map::getContinents() {
    vector<Continent> continents;
    for (int i = 0; i < continents.size(); i++) {
        continents.push_back(*(new Continent(continents[i])));
    }
    return continents;
}

//how many continents
int Map::getContinentsSize() {
    return static_cast<int>(continents.size());
}

//how many territories
int Map::getTerritoriesSize() {
    return static_cast<int>(territories.size());
}