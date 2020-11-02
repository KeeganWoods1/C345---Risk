#include "GameEngine.h"
#include <iostream>
#include <fstream>
#include <filesystem>
#include <string>
using namespace std;

int main() {

    //Initialize the map directory and get user's selected map
    MapDirectoryInit* mdiPtr = new MapDirectoryInit();
    //Initialize player list and get number of players
    PlayerListInit* pliPtr = new PlayerListInit();
    //Initialize phase observers and ask user if they wish to turn either one off
    PhaseObserver* poPtr = new PhaseObserver();
    StatisticsObserver* soPtr = new StatisticsObserver();
    ObserverToggle* otPtr = new ObserverToggle(poPtr, soPtr);
    
    //use user input as parameter to MapLoader() constructor
    MapLoader* mapLoader = new MapLoader("MapFiles/" + mdiPtr->getSelectedMap());

        //create player objects and add them to the player list
    for (int i= 0; i<pliPtr->getNumOfPlayers(); i++)
    {
        string playerName;
        cout << "Please enter player " << i+1 << "'s name"<< endl;
        cin >> playerName;
        Player* player = new Player(playerName);

        pliPtr->getPlayerList()->push_back(player); 
    }

    //Create deck object
    Deck* deck = new Deck(pliPtr->getNumOfPlayers());

    cout << "\nPrinting Players in the game: " << endl;

    for(int i=0; i< pliPtr->getPlayerList()->size(); i++)
    {
        cout << *pliPtr->getPlayerList()->at(i) << endl;
    }


    

    return 0;
}