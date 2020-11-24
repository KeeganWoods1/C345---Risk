#include "GameObservers.h"
#include "GameEngine.h"
#include <iostream>
#include <limits>
#include <filesystem>
#ifdef _DEBUG
#define DBG_NEW new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
// Replace _NORMAL_BLOCK with _CLIENT_BLOCK if you want the
// allocations to be of _CLIENT_BLOCK type
#else
#define DBG_NEW new
#endif
using namespace std;

Observer::Observer() {}

Observer::~Observer() {}

Observer::Observer(const Observer& obs) {
}
Observer& Observer::operator = (const Observer& obs) {
    return *this;
}
ostream& operator << (ostream& out, const Observer& o) {
    out << " this is an observor";
    return out;
}

Subject::Subject()
{
    _observers = DBG_NEW std::list<Observer*>;
}

Subject::~Subject()
{
    delete _observers;
}

void Subject::Attach(Observer* o)
{
    _observers->push_back(o);
}

void Subject::Detach(Observer* o)
{
    _observers->remove(o);
}

void Subject::Notify()
{
    std::list<Observer*>::iterator i = _observers->begin();
    for(; i != _observers->end(); i++)
    {
        (*i)->Update();
    }
}

Subject::Subject(const Subject& obs) {
    _observers = new std::list<Observer*>;
    for (int i = 0; i < obs._observers->size(); i++) {
        _observers[i] = (obs._observers[i]);
    }
}
Subject& Subject::operator = (const Subject& obs) {
    _observers = obs._observers;
    return *this;
}
ostream& operator << (ostream& out, const Subject& o) {
    out << " this is a subject"; 
    return out;
}

GameScreen::GameScreen() {}

GameScreen::GameScreen(WarzoneGame* s)
{
    _subject = s;
    _subject->Attach(this);
}

GameScreen::~GameScreen()
{
    _subject->Detach(this);
}

void GameScreen::Update()
{
    int n = _subject->getCurrentPhase();

    switch(n)
    {
        case 0:
        {
            displayReinforcementPhase();
            break;
        }
        case 1:
        {
            displayIssuOrdersPhase();
            break;
        }
        case 2:
        {
            displayExecuteOrdersPhase();
            break;
        }
    }
}

void GameScreen::displayReinforcementPhase()
{
    cout << "************************************************************" << endl;
    cout << "Displaying Reinforcement Phase Info for " << *_subject->getCurrentPlayer() << ":" << endl;
    cout << "Reinforcements Available: " << _subject->getCurrentPlayer()->getCurrentReinforcements() << endl;
    cout << "Continent Bonus: " << endl;
    cout << "************************************************************" << flush;

    cout << "\nPress any key to continue " << flush;
    cin.get();
    cin.get();
    clearScreen();
}

void GameScreen::displayIssuOrdersPhase()
{
    cout << "************************************************************" << endl;
    cout << "Displaying Issue Orders Phase Info for " << *_subject->getCurrentPlayer() << ":" << endl;
    cout << "Reinforcements Available:" << _subject->getCurrentPlayer()->getCurrentReinforcements() << endl;
    cout << "\nTerritories To Defend:" << endl;
    for (Territory* territory : *_subject->getCurrentPlayer()->gettoDefend(*_subject->getGameMap()))
    {
        cout << *territory << endl; 
    }
    cout << "\nTerritories To Attack:" << endl;
    for (Territory* territory : *_subject->getCurrentPlayer()->toAttack(*_subject->getGameMap()))
    {
        cout << *territory << endl;
    }
    cout << "\nHand Contents:" << endl;
    cout << *_subject->getCurrentPlayer()->getHand();
    cout << "\nOrder List:" << endl;
    cout << *_subject->getCurrentPlayer()->getPlayerlist();
    cout << "************************************************************" << flush;

    cout << "\nPress any key to continue " << flush;
    cin.get();
    cin.get();
    clearScreen();
}

void GameScreen::displayExecuteOrdersPhase()
{
    bool hasWon = _subject->getHasWon();
    
    if(!hasWon){
    cout << "************************************************************" << endl;
    cout << "Displaying Execute Orders Phase Info " << endl;
    cout << "Executing..." << endl;
    for(Order* order : _subject->getExecutionQueue())
    {
        cout << *order << endl;
    }
    cout << "************************************************************" << flush;

    cout << "\nPress any key to continue " << flush;
    cin.get();
    cin.get(); 
    clearScreen();
    }
}

//pathetic implementation to clear the output window, better than calling 'system' and suitable for program of this size.
void GameScreen::clearScreen()
{
    for(int i =0; i<10; i++)
    {
        cout << "\n\n\n\n\n\n\n\n\n\n"; 
    }
}
GameScreen::GameScreen(const GameScreen& obs) {
    _subject = new WarzoneGame(*obs._subject);
}
GameScreen& GameScreen::operator = (const GameScreen& obs) {
    _subject = obs._subject;
    return *this;
}
ostream& operator << (ostream& out, const GameScreen& o) {
    out << "this is a game screen ";
    return out;
}

StatsScreen::StatsScreen() {}

StatsScreen::StatsScreen(WarzoneGame* s) 
{
    _subject = s;
    _subject->Attach(this);
}

StatsScreen::~StatsScreen()
{
    _subject->Detach(this);
}

void StatsScreen::Update()
{
    bool hasWon = _subject->getHasWon();

    if(!hasWon)
    {
        Display();
    }
    else
    {
        displayWin();
    }   
}

void StatsScreen::Display()
{
    cout << "************************************************************" << endl;
    cout << "World Domination Status:\n" << endl;
    for(Player* player : _subject->getPlayerList())
    {
        float percentOwned = ((float)player->gettoDefend(*_subject->getGameMap())->size()/(float)_subject->getGameMap()->getTerritories()->size()) * 100;
        cout << "Player: " << player->getName() << " -> Dominating ";
        if (percentOwned < 100 )cout << std::setprecision(2) << percentOwned <<"% of the map.\n"<< endl;
        else cout << std::setprecision(3) << percentOwned << "% of the map.\n" << endl;
    }
    cout << "************************************************************\n" << endl;
    
    cout << "\nPress any key to continue " << flush;
    cin.get();
    cin.get(); 
}

void StatsScreen::displayWin()
{
    clearScreen();
    cout << "YOU WIN!!" << endl;
}

//pathetic implementation to clear the output window, better than calling 'system' and suitable for program of this size.
void StatsScreen::clearScreen()
{
    for(int i =0; i<10; i++)
    {
        cout << "\n\n\n\n\n\n\n\n\n\n"; 
    }
}
StatsScreen::StatsScreen(const StatsScreen& obs) {
    _subject = new WarzoneGame(*obs._subject);
}
StatsScreen& StatsScreen::operator = (const StatsScreen& obs) {
    _subject = obs._subject;
    return *this;
}
ostream& operator << (ostream& out, const StatsScreen& o) {
    out << " this is a stats screen";
    return out;
}

GameController::GameController(GameScreen* newView, StatsScreen* otherView, WarzoneGame* newModel)
{
    gameView = newView;
    statsView = otherView;
    gameModel = newModel;
}

void GameController::controlGame()
{
    cout << "Starting game...\n" <<endl;
    
    if(!gameModel->getGameInitPtr()->getpliPtr()->getDisplayPhaseInfo())
    {
        gameModel->Detach(gameView);
    }
    if(!gameModel->getGameInitPtr()->getpliPtr()->getDisplayStatsInfo())
    {
        gameModel->Detach(statsView);
    }
    gameModel->mainGameLoop();
}
GameController::GameController(const GameController& obs) {
    gameView = new GameScreen(*obs.gameView);
    statsView = new StatsScreen(*obs.statsView);
    gameModel = new WarzoneGame(*obs.gameModel);
}
GameController& GameController::operator = (const GameController& obs) {
    gameView = obs.gameView;
    statsView = obs.statsView;
    gameModel = obs.gameModel;
    return *this;
}
ostream& operator << (ostream& out, const GameController o) {
    out << "this is a game controller";
    return out;
}