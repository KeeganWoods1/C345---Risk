#pragma once
#include "MapLoader.h"
#include "Player.h"
#include "Cards.h"
#include "GameObservers.h"
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

class MapDirectoryInit 
{
    private:
    string selectedMap;

    public:
    MapDirectoryInit();
    ~MapDirectoryInit();
    //Copy constructor
    MapDirectoryInit(const MapDirectoryInit& md);
    string getSelectedMap();
    //Assignment operator
	MapDirectoryInit& operator = (const MapDirectoryInit& md);
    //I/O operator overloads
    friend istream &operator >> (istream &stream, MapDirectoryInit& md);
    friend ostream &operator << (ostream &out, const MapDirectoryInit& md);

};

class PlayerListInit
{
    private:
    int numOfPlayers;
    vector<Player*>* playerList;
    Deck* deckPtr;

    public:
    PlayerListInit();
    PlayerListInit(int);
    ~PlayerListInit();
    //Copy constructor
    PlayerListInit(const PlayerListInit& pl);
    vector<Player*>* getPlayerList();
    int getNumOfPlayers();
    Deck* getDeckPtr();
    //Assignment operator
	PlayerListInit& operator = (const PlayerListInit& pl);
    //I/O operator overloads
    friend istream &operator >> (istream &stream, PlayerListInit& pl);
    friend ostream &operator << (ostream &out, const PlayerListInit& pl);
};

class ObserverToggle
{
    private:
    PhaseObserver* phaseObserver;
    StatisticsObserver* statsObserver;

    public:
    ObserverToggle();
    ObserverToggle(PhaseObserver*, StatisticsObserver*);
    ~ObserverToggle();
    void toggle(PhaseObserver*);
    void toggle(StatisticsObserver*);
    //Copy constructor
    ObserverToggle(const ObserverToggle& ot);
    //Assignment operator
	ObserverToggle& operator = (const ObserverToggle& ot);
    //I/O operator overloads
    friend istream &operator >> (istream &stream, ObserverToggle& ot);
    friend ostream &operator << (ostream &out, const ObserverToggle& ot);
};