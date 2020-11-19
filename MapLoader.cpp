#include "MapLoader.h"
#include <iostream>
#include <fstream>
#include <string>
using namespace std;
#ifdef _DEBUG
#define DBG_NEW new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
// Replace _NORMAL_BLOCK with _CLIENT_BLOCK if you want the
// allocations to be of _CLIENT_BLOCK type
#else
#define DBG_NEW new
#endif
//Default constructor
MapLoader::MapLoader() {
    map= nullptr;
    validMap = NULL;
}

//Parameterized constructor
MapLoader::MapLoader(string mapName) {
    map = DBG_NEW string(mapName);
    validMap = NULL;
    fstream map_stream;
    map_stream.open("MapFiles/"+*map, std::fstream::in | std::fstream::out);
    //if map file was found
    if (map_stream.is_open()) {
        std::cout << "Map file was opened successfully\n" << std::endl;
        loadMap(map_stream);

        //closes the stream
        map_stream.close();
    }
        //if map file was not opened successfully
    else
    {
        cout << "Unable to open the map file!\n" << endl;
    }
        
}

//Destructor
MapLoader::~MapLoader(){
    delete map;
    if (validMap != NULL)delete validMap;
    map = nullptr;
    validMap = nullptr;
    for (int i = 0; i < continents.size(); i++) {
        delete continents.at(i);
    }
    continents.clear();
    for (int i = 0; i < countries.size(); i++) {
        delete countries.at(i);
    }
    countries.clear();
    if (borders.size() >= 1)
    for (int i = 0; i < borders.size(); i++) {
        if (!borders.at(i)->empty())delete borders.at(i);
    }

    map = NULL;
    validMap = NULL;
}

//getters
Map* MapLoader::getMap() {
    return validMap;
}

bool MapLoader::getStatus()
{
    return isLoaded;
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
    string* str = NULL;
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
            continentsFound= true;
            counter= 0;

            //reading until end of continents
            while (line.find("[countries]") == -1){
                getline(map_stream,line, '\n');
                if (line.size() <= 1){
                    break;
                }

                str = DBG_NEW string (line);
                continents.push_back(str);
                //next continent index
                counter++;

            }//end of while loop for continents
            totalContinents = counter;
            cout << "Total number of continents is: " << totalContinents << endl;
        }//end of if for continents

        counter =-1;
        //until reaching "[countries]"
        if (line.find("[countries]") != -1){
            countriesFound= true;
            counter= 0;

            //reading until end of countries
            while (line.find("[borders]") == -1){
                getline(map_stream,line, '\n');
                if (line.size() <= 1){
                    break;
                }
                
                str = DBG_NEW string (line);
                countries.push_back(str);
                //next country index
                counter++;

            }//end of while loop for countries
            totalCountries= counter;
            cout << "Total number of countries is: " << totalCountries << endl;
        }//end of if for countries

        counter =-1;
        //until reaching "[borders]"
        if (line.find("[borders]") != -1){
            bordersFound= true;
            counter= 0;
            //reading until end of borders
            while (!map_stream.eof()){
                getline(map_stream,line, '\n');
                if (line.size() <= 1){
                    break;
                }
                str = DBG_NEW string (line);
                borders.push_back(str);
                //next border index
                counter++;

            }//end of while loop for borders
            totalBorders= counter;
            cout << "Total number of borders is: " << totalBorders << endl;
        }//end of if for borders

    }//end of while for all map file

    if (continentsFound & countriesFound & bordersFound)
    {
        cout << "\nCreating a map object...\n" << endl;
        if(!CreateMap(continents, countries, borders)->Validate())
        {
            cout << "Map file was loaded successfully, however, it's an invalid map" << endl;
        }   
    } 
    else 
    {
        cout << "Map file was loaded successfully, however, it's an invalid map" << endl;
    }
    isLoaded = true;

    //to avoid memory leak
    str = nullptr;
}//end of load map

//to print out a vector content
void MapLoader::printVector(vector<std::string*> aVector) {
    for (vector<std::string*>::const_iterator i = aVector.begin(); i != aVector.end(); ++i){
        std::cout << **i << endl;
    }
}
void MapLoader::printTerritories(vector<Territory*>* aVector){
    for (vector<Territory*>::const_iterator i = aVector->begin(); i != aVector->end(); ++i){
        std::cout << **i;
    }
    cout << "" << endl;
}
void MapLoader::printContinents(vector<Continent*>* aVector){
    for (vector<Continent*>::const_iterator i = aVector->begin(); i != aVector->end(); ++i){
        std::cout << **i;
    }
    cout << "" << endl;
}

//to return a map object
Map* MapLoader::CreateMap(vector<string *> continents, vector<string *> countries, vector<string *> borders) {

    //creating territories list object and adding each one to the continent that it belongs to
    vector<Territory*>* territoriesListPtr = DBG_NEW vector<Territory*>();
    //args of territory = int continent, string name, player* owner, int armies.
    for(int j=0; j<countries.size(); j++) {
        string name;
        int continentID;

        int wordCount = 1;
        string word = "";
        //There are 5 words in every line of countries vector, we need name/continentID or words 2&3
        for(auto nextWord : *countries[j]) {
            //reaching end of second word
            if(nextWord == ' ' && wordCount == 2) {
                name = word;
                word = "";
                wordCount++;
            }
            //reaching end of third word
            else if(nextWord == ' ' && wordCount == 3) {
                continentID = std::stoi(word, nullptr);
                word = "";
                wordCount++;
            }
            //reaching end of first word
            else if(nextWord == ' ') {
                word = "";
                wordCount++;
            }
            else {
                word = word + nextWord;
            }
        }
        //creating territory and add to territories list
        Player* neutralPlayer = DBG_NEW Player("Neutral");
        Territory* territory = DBG_NEW Territory(continentID, name, neutralPlayer, 1);
        territoriesListPtr->push_back(territory);
    }

    //creating Continents object and setting the bonus army for each continent
    vector<Continent*>* continentsListPtr = DBG_NEW vector<Continent*>();
    vector<Territory*> territoriesInContinent;
    for (int i=0; i<continents.size(); i++){
        territoriesInContinent.clear();
        string name;
        int id = i+1;
        int bonus;
        int wordCount = 1;
        string temp = "";
        //There are 3 words in every line of continents vector, we need name/bonus army or words 1&2
        for (auto nextWord : *continents[i]){
            //reach end of second word
            if (nextWord == ' ' && wordCount == 2){
                bonus = std::stoi(temp, nullptr);
                temp = "";
                wordCount++;
            }
            //reaching end of first word
            else if (nextWord == ' ' && wordCount ==1){
                name = temp;
                temp = "";
                wordCount++;
            }
            else if (wordCount >= 3){
                temp = "";
            }
            else{
                temp = temp + nextWord;
            }
        }
        for (auto Terr : *territoriesListPtr){
            if(Terr->getterritory_continent() == id){
                territoriesInContinent.push_back(Terr);
            }
        }
        //creating continent and add to continents list
        Continent* aContinent = DBG_NEW Continent(name, id, bonus, territoriesInContinent);
        continentsListPtr->push_back(aContinent);
    }
    //create map object
    validMap = DBG_NEW Map(countries.size(), territoriesListPtr, continentsListPtr);
    vector<int> brdrsList;
    string nextBorder;

    //Add all borders to map object
    for(int j =0; j<borders.size(); j++) {
        brdrsList.clear();

        //convert the string of characters into numbers array
        for(std::string::iterator it=borders[j]->begin(); it!=borders[j]->end(); ++it) {
            //Only add numbers delimited by whitespace
            if(isdigit(*it)) {
                nextBorder.push_back(*it);

                //If this is the last number on the line -> push to borders
                if(it == borders[j]->end()-1) {
                    //convert string to int and clear temp variable nextBorder for next line
                    brdrsList.push_back(std::stoi(nextBorder, nullptr));
                    nextBorder = ""; 
                }
            }
            //protect against end of lines & trailing spaces on ends of lines
            else if(nextBorder != "" && it != borders[j]->end()) {
                //convert string to int and clear temp variable nextBorder for next line
                brdrsList.push_back(std::stoi(nextBorder, nullptr));
                nextBorder = ""; 
            }
        }
        //add borders to map object
        for( int k =1; k<brdrsList.size(); k++) {
            validMap->addBorder(brdrsList[0] - 1, brdrsList[k] - 1);
        }   
    }
    continentsListPtr->clear();
    delete continentsListPtr;
    territoriesListPtr->clear();
    delete territoriesListPtr;

    return validMap;
}