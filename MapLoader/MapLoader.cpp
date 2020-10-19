#pragma once
#include "MapLoader.h"
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

//Default constructor
MapLoader::MapLoader() {
    map= nullptr;
}

//Parameterized constructor
MapLoader::MapLoader(string mapName) {
    map= new string(mapName);

    fstream map_stream;
    map_stream.open(*map, std::fstream::in | std::fstream::out);
    //if map file was found
    if (map_stream.is_open()) {
        std::cout << "Map file was opened successfully" << std::endl;
        loadMap(map_stream);

        //closes the stream
        map_stream.close();
    }
        //if map file was not opened successfully
    else
        cout << "Unable to open the map file!" << endl;
}

//Destructor
MapLoader::~MapLoader(){
    delete map;
    delete validMap;
    map = nullptr;
    validMap = nullptr;
    cout << "End of main(). Deleting members...";
}

//getter
std::string MapLoader::getMap() {
    return *map;
}

//Copy constructor
MapLoader::MapLoader(const MapLoader &anotherMap) {
    cout << "Using copy constructor";
    map= anotherMap.map;
    validMap= anotherMap.validMap;
}

//Assignment operator
MapLoader& MapLoader::operator = (const MapLoader& map) {
    cout << "Using assignment operator";
    return *this;
}

//Stream insertion operator (toString method)
std::ostream &operator<<(ostream &out, const MapLoader &map) {
    out << "Map is: " << *map.map << endl;
    return out;
}

//to load a map and store its contents in vectors
void MapLoader::loadMap(fstream& map_stream) {

    string line;
    int counter;
    string* str;
    int totalContinents;
    int totalCountries;
    int totalBorders;
    bool continentsFound= false;
    bool countriesFound= false;
    bool bordersFound= false;

    //while file has a line
    while (!map_stream.eof()){
        //read line
        getline(map_stream,line);

        //until reaching "[continents]"
        if (line.find("[continents]") != -1){
            cout << "Found [continents]" << endl;
            continentsFound= true;
            counter= 0;

            //reading until end of continents
            while (line.find("[countries]") == -1){
                getline(map_stream,line, '\n');
                if (line.empty()){
                    break;
                }
                str = new string (line);
                continents.push_back(str);
//                    cout << counter+1 << " - " << line << endl;

                //next continent index
                counter++;

            }//end of while loop for continents
            totalContinents= counter;
            cout << "Printing out continents:" << endl;
            cout << "Total number of continents is: " << totalContinents << endl;
            printVector(continents);
        }//end of if for continents

        counter =-1;
        //until reaching "[countries]"
        if (line.find("[countries]") != -1){
            cout << "found [countries]" << endl;
            countriesFound= true;
            counter= 0;

            //reading until end of countries
            while (line.find("[borders]") == -1){
                getline(map_stream,line, '\n');
                if (line.empty()){
                    break;
                }
                str = new string (line);
                countries.push_back(str);
//                    cout << counter+1 << " - " << line << endl;

                //next country index
                counter++;

            }//end of while loop for countries
            totalCountries= counter;
            cout << "Printing out countries:" << endl;
            cout << "Total number of countries is: " << totalCountries << endl;
            printVector(countries);
        }//end of if for countries

        counter =-1;
        //until reaching "[borders]"
        if (line.find("[borders]") != -1){
            cout << "found [borders]" << endl;
            bordersFound= true;
            counter= 0;
            //reading until end of borders
            while (!map_stream.eof()){
                getline(map_stream,line, '\n');
                if (line.empty()){
                    break;
                }
                str = new string (line);
                borders.push_back(str);
//                    cout << counter+1 << " - " << line << endl;

                //next border index
                counter++;

            }//end of while loop for borders
            totalBorders= counter;
            cout << "Printing out borders:" << endl;
            cout << "Total number of borders is: " << totalBorders << endl;
            printVector(borders);

        }//end of if for borders

    }//end of while for all map file
    if (continentsFound & countriesFound & bordersFound & totalCountries == totalBorders){
        cout << "Map is valid. Creating a map object..." << endl;
        CreateMap(continents, countries, borders);
    } else {
        cout << "Map file was loaded successfully, however, it's an invalid map" << endl;
    }

    //to avoid memory leak
    delete (str);
    str = nullptr;
}//end of load map

//to print out a vector content
void MapLoader::printVector(vector<std::string*> aVector) {
    for (auto& vector : aVector){
        std::cout << *vector << ' ' << endl;
    }
}

//to return a map object
Map MapLoader::CreateMap(vector<string *> continents, vector<string *> countries, vector<string *> borders) {
    validMap = new Map();
    return *validMap;
}