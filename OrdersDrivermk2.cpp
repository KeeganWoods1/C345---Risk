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
    //Initialize game start phase
    GameInit* giPtr = new GameInit(pliPtr->getPlayerList(), mdiPtr->getGameMap());

    for (int i=0; i<mdiPtr->getGameMap()->getTerritories()->size(); i++)
    {
        cout << *mdiPtr->getGameMap()->getTerritories()->at(i) << endl;
    }
    for (int i=0; i<mdiPtr->getGameMap()->getTerritories()->size(); i++){
        mdiPtr->getGameMap()->getTerritories()->at(i)->setterritory_armycount(6);
    }
    cout<<mdiPtr->getGameMap()->getTerritories()->at(0)->getterritory_armycount()<<"\n";
    Orderlist ol;
    ol.add(new Deployorder(pliPtr->getPlayerList()->at(0),new int (3),pliPtr->getPlayerList()->at(0)->toDefend()->at(0)));
    ol.add(new Deployorder(pliPtr->getPlayerList()->at(1),new int (3),pliPtr->getPlayerList()->at(1)->toDefend()->at(0)));
    Territory *attack = NULL;
    Territory *defend = NULL;
    //Map* m1 = new Map(m);
    for (int k=0; k<pliPtr->getPlayerList()->at(0)->toDefend()->size(); k++) {
        vector<Territory *> *ter = pliPtr->getPlayerList()->at(0)->surroundingterritories(*mdiPtr->getGameMap(),pliPtr->getPlayerList()->at(0)->toDefend()->at(k));

        for (int i = 0; i < ter->size(); i++) {
            if (ter->at(i)->getterritory_owner()->getName().compare(pliPtr->getPlayerList()->at(0)->getName()) !=0 && mdiPtr->getGameMap()->isAdjacent(ter->at(i),pliPtr->getPlayerList()->at(0)->toDefend()->at(k))) {
                attack = ter->at(i);
                defend = pliPtr->getPlayerList()->at(0)->toDefend()->at(k);
                break;
            }
        }
        if (attack!=NULL) break;
    }
    Territory *from = NULL;
    Territory *to = NULL;
    for (int k=0; k<pliPtr->getPlayerList()->at(0)->toDefend()->size(); k++) {
        vector<Territory *> *ter = pliPtr->getPlayerList()->at(0)->surroundingterritories(*mdiPtr->getGameMap(),pliPtr->getPlayerList()->at(0)->toDefend()->at(k));

        for (int i = 0; i < ter->size(); i++) {
            if (ter->at(i)->getterritory_owner()->getName().compare(pliPtr->getPlayerList()->at(0)->getName()) ==0 && mdiPtr->getGameMap()->isAdjacent(ter->at(i),pliPtr->getPlayerList()->at(0)->toDefend()->at(k))) {
                from = ter->at(i);
                to = pliPtr->getPlayerList()->at(0)->toDefend()->at(k);
                break;
            }
        }
        if (to!=NULL) break;
    }
    if (attack != NULL) ol.add(new Advanceorder(new int(1),pliPtr->getPlayerList()->at(0),attack,defend,mdiPtr->getGameMap()));
    else ol.add(new Advanceorder(new int(1),pliPtr->getPlayerList()->at(1),pliPtr->getPlayerList()->at(1)->toDefend()->at(4),pliPtr->getPlayerList()->at(0)->toDefend()->at(0),mdiPtr->getGameMap()));
    ol.add(new Airliftorder(new int (1),pliPtr->getPlayerList()->at(0)->toDefend()->at(1),pliPtr->getPlayerList()->at(0)->toDefend()->at(0),pliPtr->getPlayerList()->at(0)));
    ol.add(new Bomborder(pliPtr->getPlayerList()->at(0),pliPtr->getPlayerList()->at(1)->toDefend()->at(3)));
    ol.add(new Blockadeorder(pliPtr->getPlayerList()->at(0),pliPtr->getPlayerList()->at(0)->toDefend()->at(3)));
    ol.add(new Negotiateorder(pliPtr->getPlayerList()->at(0),pliPtr->getPlayerList()->at(1)));
    ol.add(new Advanceorder(new int(1),pliPtr->getPlayerList()->at(0),attack,defend,mdiPtr->getGameMap()));
    ol.add(new Advanceorder(new int(1),pliPtr->getPlayerList()->at(0), to,from,mdiPtr->getGameMap()));
    ol.executelist();
    return 0;
}