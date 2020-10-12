//
// The Map loader should:
// 1- read and load any map file
// 2- Store the map as a graph data structure (Part 1)
// 3- read any text file (even the ones that do not constitute a valid map)
//
#ifndef A1_MAPLOADER_H
#define A1_MAPLOADER_H
#endif //A1_MAPLOADER_H
#include "map.h"
#include <string>
#include <vector>
#pragma once
using namespace std;

class MapLoader {
    public:
        //Default constructor
        MapLoader();

        //Parameterized constructor
        MapLoader(string);

        //Destructor
        ~MapLoader();

        //Getter
        string getMap();

        //Copy constructor
        MapLoader(const MapLoader&);

        //Assignment operator
        MapLoader& operator = (const MapLoader&);

        //Stream insertion operator (toString method)
        friend std::ostream& operator<<(std::ostream&, const MapLoader&);

        //to load a map file
        void loadMap(fstream&);

        //to return a map object
        Map CreateMap(vector<string*>, vector<string*>, vector<string*>);

        //to print out a vector content
        void printVector(vector<std::string*>);

    private:
        //map file
        string* map;
        //map object
        Map* validMap;//map file

        //to store the contents from the map file
        vector<std::string*> continents;
        vector<std::string*> countries;
        vector<std::string*> borders;
};