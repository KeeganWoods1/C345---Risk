#include "MapLoader.cpp"
#include "../Map/map.cpp"
#include "../Player/Player.cpp"
#include "../Cards/Cards.cpp"
#include "../Orders/Orders.cpp"
#include <iostream>
#include <string>
using namespace std;

int main() {

    string map_name;

    //Ask the user for a map name to open it
    cout << "Please enter the name of the map file:" << endl;
    cin >> map_name;
    cout << "" << endl;

    MapLoader* mapLoader = new MapLoader(map_name);

    //testing toString method
    cout << *mapLoader;

    //to avoid memory leak
    delete mapLoader;
    mapLoader= nullptr;

    return 0;
}
