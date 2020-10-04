#pragma once
#include <vector>
#include <string>
using namespace std;
/*manually create territories, and the adjacency between territories,
* and a way to verify that the map is connected (how?)
*manually create continents, and check whether they are defined, and create sub-graphs, and each countries belongs to one continent.
*territories or countries node [territories]
* 1 Alaska 1 44 83 <~~ the first number is the number of the country (they do have to be in order)
* the next one is what continent it belongs to. the other two numbers are the x and y co-ordinates
* of the circle that will be put on that country
*/
class Territory {
private:
    Territory(string territory_name, string cont, int pl, int ar);

    //Territory id
    int territory_id = 0;

    //Territory name
    string territory_name;

    //Territory continent
    int territory_continent = 0;

    //Territory's number of armies
    int territory_armycount = 0;

    //Adjacent territories
    std::vector<Territory *> neighboring_countries;

    /* TODO must have a player (who owns the territory) pointer of type player? */
    //int territory_player{
    //};

public:
    Territory();    //default constructor
    Territory(int territory_id, string territory_name, int territory_continent);
    Territory(int,string, int, vector<Territory*>);
    Territory& operator=(const Territory&); //Assignment operator
    //NEED PLAYER

    /*TODO need player */
    //bool   setOwner(Player*);
    int    getArmies();
    bool   setArmies(int);
    int    getContinent();
    int    getId();

    /*TODO need player */
    //Player getOwner();
    vector<Territory*> getAdjacent();
    string getTerritoryName();

    //This method is used to add a link to a specific territory
    bool addBorder(Territory*);
    friend ostream& operator<< (ostream&, const Territory&);
};
ostream& operator<< (ostream& stream, const Territory& territory);

//continent node [continents]
//North-America 6 yellow <~~ name of the continent (try keep them in that order if you are doing a map of the
// "real world" as then the missions work. The number is the army value, and the color does totally nothing

class Continent {
private:
    //Continent id
    int continent_id = 0;

    //Continent name
    int continent_name = 0;

    //Adjacent Territories of the same continent
    std::vector<Territory*> territories;
    std::vector<Continent*> neighboring_countries;

public:
    Continent();
    Continent (int continent_number,  string continent_name, Continent* neighboring_countries);
    Continent(const Continent&); //copy constructor
    Continent& operator=(const Continent&); //assignment operator

    //Continent(int,int);
    //Continent(int,int, vector<Territory*>);
    //Continent(int,string);
    Continent(int,string, int);
    //Continent(int,string, int, vector<Territory*>);
    friend ostream& operator<<(ostream&, const Continent&);

    int  territoriesSize();
    int  getId();
    bool addTerritory(Territory*);
    vector<Territory> getTerritories();

};
ostream& operator<<(ostream& stream, const Continent& continent);


class Map {
private:
    int numberOfContinents;    //number of continents
    vector<Continent*> continents; //vector list containing the continents
    vector<Territory*> territories;//vector list containing the territories

public:
    Map(); //default constructor
    explicit Map(int i);
    Map(const Map&); //copy constructor

    Map& operator=(const Map&); //Assignment operator

    bool addContinent(Continent*); //adds elements to the end of the vector list, then gets a copy of list
    vector<Continent> getContinents();

    bool addTerritory(Territory*); //adds elements to the end of the vector list, then gets a copy of list
    vector<Territory> getTerritories();

    //map validation needs to validate if
    bool validate();
    bool isConnected();
    bool checkTerritories();

    int getTerritoriesSize();
    int getContinentsSize();
    void DFS(Territory* start, vector<bool>& visited);
};