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
Map* MapLoader::getMap() {
    return validMap;
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
            cout << "\nFound [continents]" << endl;
            continentsFound= true;
            counter= 0;

            //reading until end of continents
            while (line.find("[countries]") == -1){
                getline(map_stream,line, '\n');
                if (line.size() <= 1){
                    break;
                }

                str = new string (line);
                continents.push_back(str);
                //next continent index
                counter++;

            }//end of while loop for continents
            totalContinents = counter;
            cout << "\nPrinting out continents:" << endl;
            cout << "Total number of continents is: " << totalContinents << endl;
            printVector(continents);
        }//end of if for continents

        counter =-1;
        //until reaching "[countries]"
        if (line.find("[countries]") != -1){
            cout << "\nfound [countries]" << endl;
            countriesFound= true;
            counter= 0;

            //reading until end of countries
            while (line.find("[borders]") == -1){
                getline(map_stream,line, '\n');
                if (line.size() <= 1){
                    break;
                }
                
                str = new string (line);
                countries.push_back(str);
                //next country index
                counter++;

            }//end of while loop for countries
            totalCountries= counter;
            cout << "\nPrinting out countries:" << endl;
            cout << "Total number of countries is: " << totalCountries << endl;
            printVector(countries);
        }//end of if for countries

        counter =-1;
        //until reaching "[borders]"
        if (line.find("[borders]") != -1){
            cout << "\nfound [borders]" << endl;
            bordersFound= true;
            counter= 0;
            //reading until end of borders
            while (!map_stream.eof()){
                getline(map_stream,line, '\n');
                if (line.size() <= 1){
                    break;
                }
                str = new string (line);
                borders.push_back(str);
                //next border index
                counter++;

            }//end of while loop for borders
            totalBorders= counter;
            cout << "\nPrinting out borders:" << endl;
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
    for (vector<std::string*>::const_iterator i = aVector.begin(); i != aVector.end(); ++i){
        std::cout << **i << endl;
    }
}

//to return a map object
Map* MapLoader::CreateMap(vector<string *> continents, vector<string *> countries, vector<string *> borders) {

    //create territories list object
    vector<Territory*>* territoriesListPtr = new vector<Territory*>();
    //args of territory = int continent, string name, player* owner, int armies.
    for(int j=0; j<countries.size(); j++)
    {
        string name;
        int continent; 
        int wordCount = 1;
        string word = "";
        //There are 5 words(includes spaces) in every line of countries vector, we need name/continent or words 2/3
        for(auto nextWord : *countries[j])
        {
            if(nextWord == ' ' && wordCount == 2)
            {
                name = word;
                word = "";
                wordCount++;
            }
            else if(nextWord == ' ' && wordCount == 3)
            {
                continent = std::stoi(word, nullptr);
                word = "";
                wordCount++;
            }
            else if(nextWord == ' ')
            {
                word = "";
                wordCount++;
            }
            else
            {
                word = word + nextWord;
            }      
        }
        cout << "Adding territory: " << name << " Continent: " << continent << endl;
        //create appropriate territory and add to territories list
        Territory* territory = new Territory(continent, name, NULL, 0);
        territoriesListPtr->push_back(territory);
    }


    //create map object
    validMap = new Map(countries.size(), territoriesListPtr);
    vector<int> brdrsList;
    string nextBorder;

    //Add all borders to map object
    for(int j =0; j<borders.size(); j++)
    {
        brdrsList.clear();
        //convert the string of characters into numbers array
        for(std::string::iterator it=borders[j]->begin(); it!=borders[j]->end(); ++it)
        {
            //Only add numbers delimited by whitespace
            if(isdigit(*it))
            {
                nextBorder.push_back(*it);
            }
            //protect against end of lines & trailing spaces on ends of lines
            else if(nextBorder != "" && it != borders[j]->end())
            {
                //convert string to int and clear temp variable nextBorder for next line
                brdrsList.push_back(std::stoi(nextBorder, nullptr));
                nextBorder = ""; 
            }
        }
        //add borders to map object
        for( int k =1; k<brdrsList.size(); k++)
        {
            validMap->addBorder(brdrsList[0] - 1, brdrsList[k] - 1);
        }    
    }
 
    cout << "************" << endl;
    return validMap;
}