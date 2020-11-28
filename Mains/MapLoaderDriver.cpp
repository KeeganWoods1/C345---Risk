#include "../MapLoader.h"
#include <iostream>
#include <string>
using namespace std;

int main() {
    cout << "--Welcome to Warzone Game--" << endl;

    int map_type;
    string map_name;

    do {
        //Ask the user for a map type
        cout << "Please choose a map type" << endl;
        cout << "Please enter (1) for Warzone Map or (2) for a Conquest Map?" << endl;
        cin >> map_type;
        //Ask the user for a map name
        if (map_type == 1){
            cout << "Please enter the name of the Warzone Map file:" << endl;
            cin >> map_name;
            cout << "" << endl;
            MapLoader* mapLoader = new MapLoader(map_name);
            //testing toString method
            //cout << *mapLoader;
        }
        else if(map_type == 2){
            cout << "Please enter the name of the Conquest map file:" << endl;
            cin >> map_name;
            cout << "" << endl;
            bool yes = true;
            ConquestFileReader* conquestFileReader = new ConquestFileReader(map_name);
            if (conquestFileReader->getStatus()){
                ConquestFileReaderAdapter* conquestFileReaderAdapter = new ConquestFileReaderAdapter(conquestFileReader);
                conquestFileReaderAdapter->loadMap(map_name);
            }
        }
    } while ((map_type != 1) && (map_type !=2) && (map_type !=0));

    return 0;
}