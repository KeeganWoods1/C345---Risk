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
    validMap = nullptr;
    isLoaded = false;
}

//Parameterized constructor
MapLoader::MapLoader(string mapName) {
    map = DBG_NEW string(mapName);
    fstream map_stream;
    validMap = NULL;
    map_stream.open("MapFiles/"+*map, std::fstream::in | std::fstream::out);
    //if map file was found
    if (map_stream.is_open()) {
        std::cout << "Map file was opened successfully\n" << std::endl;
        loadMap(*map);
        //closes the stream
        map_stream.close();
    }
}
//Copy constructor
MapLoader::MapLoader(const MapLoader &anotherMap) {
    cout << "Using copy constructor";
    map= anotherMap.map;
    validMap= anotherMap.validMap;
    isLoaded= anotherMap.isLoaded;
}
//Destructor
MapLoader::~MapLoader(){
    delete map;
    if (validMap != NULL)
    //delete validMap;
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
    for (int i = 0; i < borders.size(); i++) {
        if (!borders.at(i)->empty())delete borders.at(i);
    }
    borders.clear();
}

//getters
Map* MapLoader::getMap() {
    return validMap;
}
bool MapLoader::getStatus() {
    return isLoaded;
}

//Assignment operator
MapLoader& MapLoader::operator = (const MapLoader& aMap) {
    cout << "Using assignment operator";
    map = aMap.map;
    validMap = aMap.validMap;
    isLoaded = aMap.isLoaded;
    return *this;
}

//Stream insertion operator (toString method)
std::ostream &operator<<(ostream &out, const MapLoader &map) {
    out << "Map is: " << *map.map << endl;
    return out;
}

//to load a map and store its contents in vectors
void MapLoader::loadMap(std::string map_name) {

    fstream map_stream;
    map_stream.open("MapFiles/"+map_name, std::fstream::in | std::fstream::out);

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
            continentsFound = true;
            counter = 0;

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

    if (continentsFound & countriesFound & bordersFound) {
        cout << "\nCreating a map object...\n" << endl;
        CreateMap(continents, countries, borders);
    }
    else
        cout << "Map file was loaded successfully, however, it's an invalid map" << endl;
    //closes the stream
    map_stream.close();
}//end of loadMap()

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
        Player* neutralPlayer = DBG_NEW Player("Neutral", DBG_NEW NeutralPlayerStrategy());
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
    //deleting territoriesListPtr and continentsListPtr to avoid memory leak
    delete territoriesListPtr;
    delete continentsListPtr;

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
    if (validMap->Validate()) {
        std::cout << "Map is valid because it is a connected graph.\n" << std::endl;
        isLoaded = true;
    }
    else {
        std::cout << "Map is invalid because it is NOT a connected graph.\n" << std::endl;
        isLoaded = false;
    }
    return validMap;
}//end of CreateMap()

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

//Default constructor
ConquestFileReader::ConquestFileReader() {
    conquest_map = nullptr;
    validConquestMap = nullptr;
    isLoaded = false;
}

//Parameterized constructor
ConquestFileReader::ConquestFileReader(string conquest_map_Name) {
    conquest_map = DBG_NEW string(conquest_map_Name);
    fstream conquest_map_stream;
    conquest_map_stream.open("MapFiles/ConquestMaps/"+*conquest_map, std::fstream::in | std::fstream::out);
    //if map file was found
    if (conquest_map_stream.is_open()) {
        std::cout << "Map file was opened successfully\n" << std::endl;
        //closes the stream
        conquest_map_stream.close();
    }
    delete conquest_map;
}

//Copy constructor
ConquestFileReader::ConquestFileReader(const ConquestFileReader &anotherConquestMap) {
    cout << "Using copy constructor";
    conquest_map = anotherConquestMap.conquest_map;
    validConquestMap = anotherConquestMap.validConquestMap;
    isLoaded = anotherConquestMap.isLoaded;
}

//getters
Map* ConquestFileReader::getMap() {
    return validConquestMap;
}
bool ConquestFileReader::getStatus() {
    return isLoaded;
}

//Assignment operator
ConquestFileReader& ConquestFileReader::operator=(const ConquestFileReader& aConquest_map) {
    cout << "Using assignment operator";
    conquest_map = aConquest_map.conquest_map;
    validConquestMap = aConquest_map.validConquestMap;
    isLoaded = aConquest_map.isLoaded;
    return *this;
}

//to load a map and store its contents in vectors
void ConquestFileReader::loadMap(std::string conquest_map_name) {
    fstream conquest_map_stream;
    conquest_map_stream.open("MapFiles/ConquestMaps/"+conquest_map_name, std::fstream::in | std::fstream::out);
    if (!conquest_map_stream.is_open()) {
        cout << "this is an invalid map (or isnt a map)\n";
        isLoaded = false;
        return;
    }
    string line;
    string* str = NULL;
    int counter;
    int totalContinents;
    int totalCountries;
    bool continentsFound= false;
    bool countriesFound= false;

    //while file has a line
    while (!conquest_map_stream.eof()){
        //read line
        getline(conquest_map_stream,line);

        //until reaching "[Continents]"
        if (line.find("[Continents]") != -1){
            continentsFound = true;
            counter = 0;
            //reading until end of continents
            while (line.find("[Territories]") == -1){
                getline(conquest_map_stream,line, '\n');
                if (line.size() <= 1){
                    break;
                }
                str = DBG_NEW string (line);
                continents.push_back(str);
                //next continent index
                counter++;
            }
            totalContinents = counter;
            cout << "Total number of continents is: " << totalContinents << endl;
        }//end of if for continents

        counter =-1;
        //until reaching "[Territories]"
        if (line.find("[Territories]") != -1){
            countriesFound= true;
            counter= 0;
            //reading until end of Territories
            while (!conquest_map_stream.eof()){
                getline(conquest_map_stream,line, '\n');
                if (line.size() > 1){
                    str = DBG_NEW string (line);
                    countries.push_back(str);
                    //next country index
                    counter++;
                }
            }
            totalCountries= counter;
            cout << "Total number of countries is: " << totalCountries << endl;
        }
    }//end of while for all map file

    if (continentsFound & countriesFound) {
        cout << "\nCreating a map object...\n" << endl;
        CreateMap(continents, countries, borders);
    }
    else
        cout << "Map file was loaded successfully, however, it's an invalid map" << endl;

    //closes the stream
    conquest_map_stream.close();
}

//to return a map object
Map* ConquestFileReader::CreateMap(vector<string *> continents, vector<string *> countries, vector<string *> borders) {
    vector<Territory*>* territoriesListPtr = DBG_NEW vector<Territory*>();
    vector<Continent*>* continentsListPtr = DBG_NEW vector<Continent*>();
    vector<Territory*> territoriesInContinent;

    //args of territory = int continent, string territoryName, player* owner, int armies.
    //creating territories list object and adding each one to the continent that it belongs to
    for(int j=0; j<countries.size(); j++) {
        string territoryName;
        int continentID;
        string continentName;
        int wordCount = 1;
        string word = "";
        string name = "";
        string* rest = NULL;
        //we need name/continentName or words 1&4
        for(auto nextWord : *countries[j]) {
            //reaching end of 4th word
            if (nextWord == ',' && wordCount == 4){
                continentName = word;
                word = "";
                wordCount++;
            }
            //reaching end of first word
            else if (nextWord == ',' && wordCount == 1){
                territoryName = word;
                word = "";
                wordCount++;
            }
            else if (nextWord == ',' && (wordCount == 2 || wordCount == 3)){
                word = "";
                wordCount++;
            }
            else {
                word = word + nextWord;
            }
        }
        rest = DBG_NEW string(word);
        borders.push_back(rest);
        //getting the id of the continent this Territory is in
        for(int i=0; i <continents.size(); i++){
            string temp = "";
            for (auto ch : *continents[i]) {
                if (ch == '=') {
                    name = temp;
                    temp = "";
                    wordCount++;
                }
                else {
                    temp = temp + ch;
                }
            }
            if (name == continentName){
                int id = i+1;
                continentID = id;
            }
        }
        //creating territory and add to territories list
        Player* neutralPlayer = DBG_NEW Player("Neutral", DBG_NEW NeutralPlayerStrategy());
        Territory* territory = DBG_NEW Territory(continentID, territoryName, neutralPlayer, 1);
        territoriesListPtr->push_back(territory);
    }

    //creating Continents object and setting the bonus army for each continent
    for(int j=0; j<continents.size(); j++) {
        territoriesInContinent.clear();
        string name;
        int continentID = j+1;
        string temp;
        int bonus = 0;
        int wordCount = 1;
        bool done = false;
        for (auto ch : *continents[j]) {
            if (ch == '=') {
                name = temp;
                temp = "";
                wordCount++;
            }
            else if (wordCount == 2 && !done){
                temp = ch;
                bonus = std::stoi(temp, nullptr);;
                temp = "";
                done = true;
            }
            else {
                temp = temp + ch;
            }
        }
        for (auto Terr : *territoriesListPtr){
            if(Terr->getterritory_continent() == continentID){
                territoriesInContinent.push_back(Terr);
            }
        }
        //creating continent and add to continents list
        Continent* aContinent = DBG_NEW Continent(name, continentID, bonus, territoriesInContinent);
        continentsListPtr->push_back(aContinent);
    }//end of for loop for continents

    //create map object
    validConquestMap = DBG_NEW Map(countries.size(), territoriesListPtr, continentsListPtr);

    //Add all borders to map object
    vector<int> brdrsList;

    for(int j = 0; j<borders.size(); j++) {
        brdrsList.clear();
        string neighborTerr;
        string word;
        int terrId = j+1;
        brdrsList.push_back(terrId);
        int neighborId;
        int len = borders[j]->length();
        int len_Count = 0;

        for(auto ch : *borders[j]) {
            int count = 0;
            len_Count++;
            //assuming that we have an empty line at the end of the file to make it work
            if (ch == ',' || len_Count == len){
                neighborTerr = word;
                word = "";
                for (auto Terr : *territoriesListPtr){
                    count++;
                    if(Terr->getterritory_name() == neighborTerr){
                        neighborId = count;
                        brdrsList.push_back(neighborId);
                    }
                }
            }
            else{
                word = word + ch;
                neighborTerr = "";
            }
        }
        for(int k =1; k<brdrsList.size(); k++) {
            validConquestMap->addBorder(brdrsList[0] - 1, brdrsList[k] - 1);
        }
    }

    //deleting territoriesListPtr and continentsListPtr to avoid memory leak
    delete territoriesListPtr;
    delete continentsListPtr;

    if (validConquestMap->Validate()) {
        std::cout << "Map is valid because it is a connected graph.\n" << std::endl;
        isLoaded = true;
    }
    else {
        std::cout << "Map is invalid because it is NOT a connected graph.\n" << std::endl;
        isLoaded = false;
    }
    for (int i = 0; i < borders.size(); i++) {
        delete borders.at(i);
    }
    borders.clear();
    return validConquestMap;
}//end of CreateMap()

//to print out a vector content
void ConquestFileReader::printVector(vector<std::string*> aVector) {
    for (vector<std::string*>::const_iterator i = aVector.begin(); i != aVector.end(); ++i){
        std::cout << **i << endl;
    }
}
void ConquestFileReader::printTerritories(vector<Territory*>* aVector){
    for (vector<Territory*>::const_iterator i = aVector->begin(); i != aVector->end(); ++i){
        std::cout << **i;
    }
    cout << "" << endl;
}
void ConquestFileReader::printContinents(vector<Continent*>* aVector){
    for (vector<Continent*>::const_iterator i = aVector->begin(); i != aVector->end(); ++i){
        std::cout << **i;
    }
    cout << "" << endl;
}

//Destructor
ConquestFileReader::~ConquestFileReader(){
    //delete conquest_map;
    if (validConquestMap != NULL)
       // delete validConquestMap;
    conquest_map = nullptr;
    validConquestMap = nullptr;
    for (int i = 0; i < continents.size(); i++) {
        delete continents.at(i);
    }
    continents.clear();
    for (int i = 0; i < countries.size(); i++) {
        delete countries.at(i);
    }
    countries.clear();
    for (int i = 0; i < borders.size(); i++) {
      delete borders.at(i);
    }
    borders.clear();

}

//constructor
ConquestFileReaderAdapter::ConquestFileReaderAdapter(ConquestFileReader* conquest_map_reader){
    this->conquest_map = conquest_map_reader;
}
ConquestFileReaderAdapter::~ConquestFileReaderAdapter() {
    delete conquest_map;
}

void ConquestFileReaderAdapter::loadMap(std::string map_name) {
    cout << "Using File Reader Adapter to load a map\n" << endl;
    conquest_map->loadMap(map_name);
}