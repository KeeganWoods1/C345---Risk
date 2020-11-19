#pragma once
#include "MapLoader.h"
#include "Player.h"
#include "Cards.h"
#include "GameObservers.h"
#include <iostream>
#include <fstream>
#include <string>
#include <list>

using namespace std;

class Subject;
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
    bool phaseObservers;
    bool statsObservers;

    public:
    PlayerListInit();
    PlayerListInit(int);
    ~PlayerListInit();
    vector<Player*>* getPlayerList();
    int getNumOfPlayers();
    Deck* getDeckPtr();
    bool getDisplayPhaseInfo();
    void setDisplayPhaseInfo(bool);
    bool getDisplayStatsInfo();
    void setDisplayStatsInfo(bool);    
    //Copy constructor
    PlayerListInit(const PlayerListInit& pl);
    //Assignment operator
	PlayerListInit& operator = (const PlayerListInit& pl);
    //I/O operator overloads
    friend istream &operator >> (istream &stream, PlayerListInit& pl);
    friend ostream &operator << (ostream &out, const PlayerListInit& pl);
};

class GameInit
{
    private:
    PlayerListInit* pliPtr;
    vector<Player*>* playerListPtr;
    Map* gameMapPtr;
    Deck* gameDeckPtr;
    void startupPhase(vector<Player*>*, Map*);

    public:
    GameInit(vector<Player*>*, Map*, PlayerListInit*);
    ~GameInit();
    vector<Player*>* getPlayerListPtr();
    Map* getGameMapPtr();
    Deck* getGameDeckPtr();
    PlayerListInit* getpliPtr();
    //copy constructor
    GameInit(const GameInit& gi);
    //assignment operator
    GameInit& operator = (const GameInit& gi);
    //I/O operator overloads
    friend istream &operator >> (istream &stream, GameInit& gi);
    friend ostream &operator << (ostream &out, const GameInit& gi);
};

class WarzoneGame : public Subject
{
    private:
    vector<Player*>* playerListPtr;
    Map* gameMapPtr;
    Deck* gameDeckPtr;
    Player* currentPlayer;
    vector<Order*> executionQueue;
    int currentPhase;
    bool hasWon;
    GameInit* gameInitPtr;

    public:
    WarzoneGame(GameInit*);
    ~WarzoneGame();
    bool ordersRemain();
    void reinforcementPhase(Player *player, int numTerrOwned);
    void issueOrdersPhase(Player*);
    void executeOrdersPhase();
    void mainGameLoop(); 
    Player* getCurrentPlayer();
    void setCurrentPlayer(Player*);
    Map* getGameMap();
    void setExecutionQueue();
    vector<Order*> getExecutionQueue();
    int getCurrentPhase();
    void setCurrentPhase(int);
    bool getHasWon();
    void setHasWon(bool);
    GameInit* getGameInitPtr();
    vector<Player*> getPlayerList();
    //Copy constructor
    WarzoneGame(const WarzoneGame& wzg);
    //Assignment operator
	WarzoneGame& operator = (const WarzoneGame& wzg);
    //I/O operator overloads
    friend istream &operator >> (istream &stream, WarzoneGame& wzg);
    friend ostream &operator << (ostream &out, const WarzoneGame& wzg);

};