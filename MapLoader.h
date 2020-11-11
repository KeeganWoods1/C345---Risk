#pragma once
#include "map.h"
#include <string>
#include <vector>
#pragma once
using namespace std;

class Territory;

class MapLoader {
    public:
        //Default constructor
        MapLoader();

        //Parameterized constructor
        MapLoader(string);

        //Destructor
        ~MapLoader();

        //Getter
        Map* getMap();

        bool getStatus();

        //Copy constructor
        MapLoader(const MapLoader&);

        //Assignment operator
        MapLoader& operator = (const MapLoader&);

        //Stream insertion operator (toString method)
        friend std::ostream& operator<<(std::ostream&, const MapLoader&);

        //to load a map file
        void loadMap(fstream&);

        //to return a map object
        Map* CreateMap(vector<string*>, vector<string*>, vector<string*>);

        //to print out a vector content
        void printVector(vector<std::string*>);


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