//
// The Map loader should:
// 1- read and load any map file
// 2- Store the map as a graph data structure (Part 1)
// 3- read any text file (even the ones that do not constitute a valid map)
//--------------------
// All data members of user-defined class type must be of pointer type
// All classes must implement a correct copy constructor, assignment operator,
// and stream insertion operator
// memory leaks must be avoided
//
#include "MapLoader.h"
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

string map;

// default constructor definition
MapLoader::MapLoader() {
    map = nullptr;
}

// constructor definition
MapLoader::MapLoader(string map_name) {
    map = map_name;
}

// copy constructor definition
MapLoader::MapLoader(const MapLoader& copyMapLoader) {
    map = copyMapLoader.map;
}