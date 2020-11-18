#include "GameObservers.h"
#include "GameEngine.h"
#include <iostream>
#include <limits>
#include <filesystem>

using namespace std;

Observer::Observer() {}

Observer::~Observer() {}

Subject::Subject()
{
    _observers = new std::list<Observer*>;
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
    for (Territory* territory : *_subject->getCurrentPlayer()->gettoDefend())
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
        float percentOwned = ((float)player->gettoDefend()->size()/(float)_subject->getGameMap()->getTerritories()->size()) * 100;
        cout << "Player: " << player->getName() << " -> Dominating ";
        cout << std::setprecision(2) << percentOwned <<"% of the map.\n"<< endl;
    }
    cout << "************************************************************\n" << endl;

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

GameController::GameController(GameScreen* newView, StatsScreen* otherView, WarzoneGame* newModel)
{
    gameView = newView;
    statsView = otherView;
    gameModel = newModel;
}

void GameController::controlGame()
{
    cout << "Starting game...\n" <<endl;
    gameModel->mainGameLoop();
}