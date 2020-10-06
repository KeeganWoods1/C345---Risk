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
#ifndef A1_MAPLOADER_H
#define A1_MAPLOADER_H
#endif //A1_MAPLOADER_H

#include <iostream>
#include <fstream>
#include <string>
using namespace std;

class MapLoader {
    public:
        //default constructor
        MapLoader();

        //constructor
        MapLoader(string);

        //copy constructor
        MapLoader(const MapLoader& copyMapLoader);

    private:
        //stream insertion operator
        friend std::ostream& operator<<(std::ostream&, const MapLoader&);
        std::string map;

};