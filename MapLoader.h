#pragma once
#include "map.h"
#include <string>
#include <vector>

using namespace std;
class Territory;
class Continent;

//Class that reads Warzone game maps
class MapLoader
{
public:
    //Constructor
    MapLoader();
    MapLoader(string);

    //Destructor
    ~MapLoader();

    //Getters
    Map* getMap();
    bool getStatus();

    //Copy constructor
    MapLoader(const MapLoader&);
    //Assignment operator
    MapLoader& operator = (const MapLoader&);
    //Stream insertion operator (toString method)
    friend std::ostream& operator<<(std::ostream&, const MapLoader&);

    //to load a map file
    virtual void loadMap(fstream&);
    //to return a map object
    Map* CreateMap(vector<string*>, vector<string*>, vector<string*>);

    //to print out a vector content
    void printVector(vector<std::string*>);
    void printTerritories(vector<Territory*>*);
    void printContinents(vector<Continent*>*);

private:
    //map file
    string* map;
    //map object
    Map* validMap;
    //map load status
    bool isLoaded = false;

    //to store the contents from the map file
    vector<std::string*> continents;
    vector<std::string*> countries;
    vector<std::string*> borders;
};

//Class that reads Conquest game maps
class ConquestFileReader
{
public:
    //Constructor
    ConquestFileReader();
    ConquestFileReader(string);

    //Destructor
    ~ConquestFileReader();

    //Getters
    Map* getMap();
    bool getStatus();

    //Copy constructor
    ConquestFileReader(const ConquestFileReader&);
    //Assignment operato
    ConquestFileReader& operator = (const ConquestFileReader&);
    //Stream insertion operator (toString method)
    friend std::ostream& operator<<(std::ostream&, const ConquestFileReader&);

    //to load a map file
    void loadMap(stream&);
    //to return a map object
    Map* CreateMap(vector<string*>, vector<string*>, vector<string*>);

private:
    //map file
    string* conquest_map;
    //map object
    Map* validConquestMap;
    //map load status
    bool isLoaded = false;

    //to store the contents from the map file
    vector<std::string*> continents;
    vector<std::string*> countries;
    vector<std::string*> borders;
};

//Class that is subclass of ConquestFileReader
class ConquestFileReaderAdapter : MapLoader
{
public:
    ConquestFileReaderAdapter(ConquestFileReader conquest_map_reader);
    //overriding the load map method from MapLoader class
    void loadMap(fstream&);

private:
    ConquestFileReader* conquest_map;

};