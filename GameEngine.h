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
    string selectedMapName;
    Map* gameMapPtr;

    public:
    MapDirectoryInit();
    ~MapDirectoryInit();
    //Copy constructor
    MapDirectoryInit(const MapDirectoryInit& md);
    //Get user selected map file name
    string getSelectedMapName();
    //Get Map object created in MapLoader constructor
    Map* getGameMap();
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
    vector<Player*>* playerListPtr;
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

class GameInit
{
    private:
    vector<Player*>* playerListPtr;
    Map* gameMapPtr;
    void startupPhase(vector<Player*>*, Map*);

    public:
    GameInit(vector<Player*>*, Map*);
    ~GameInit();
    vector<Player*>* getPlayerListPtr();
    Map* getGameMapPtr();
    //copy constructor
    GameInit(const GameInit& gi);
    //assignment operator
    GameInit& operator = (const GameInit& gi);
    //I/O operator overloads
    friend istream &operator >> (istream &stream, GameInit& gi);
    friend ostream &operator << (ostream &out, const GameInit& gi);
};

class WarzoneGame
{
    private:
    vector<Player*>* playerListPtr;
    Map* gameMapPtr;

    public:
    WarzoneGame(GameInit*);
    ~WarzoneGame();
    void reinforcementPhase();
    void issueOrdersPhase();
    void executeOrdersPhase(vector<Player*> &pl);
    void mainGameLoop();
    //Copy constructor
    WarzoneGame(const WarzoneGame& wzg);
    //Assignment operator
	WarzoneGame& operator = (const WarzoneGame& wzg);
    //I/O operator overloads
    friend istream &operator >> (istream &stream, WarzoneGame& wzg);
    friend ostream &operator << (ostream &out, const WarzoneGame& wzg);

};