#include "GameObservers.h"
#include "GameEngine.h"
#include <iostream>
#include <limits>

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

void Subject::NotifyPhase(int n)
{
    std::list<Observer*>::iterator i = _observers->begin();
    for(; i != _observers->end(); i++)
    {
        (*i)->updatePhase(n);
    }
}

void Subject::NotifyStats()
{
    std::list<Observer*>::iterator i = _observers->begin();
    for(; i != _observers->end(); i++)
    {
        (*i)->updateStats();
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

void GameScreen::updatePhase(int n)
{
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

void GameScreen::updateStats()
{
    displayStats();
}

void GameScreen::displayReinforcementPhase()
{
    cout << "************************************************************" << endl;
    cout << "Displaying Reinforcement Phase Info for " << *_subject->getCurrentPlayer() << ":" << endl;
    cout << "Reinforcements Available: " << _subject->getCurrentPlayer()->getCurrentReinforcements() << endl;
    cout << "Continent Bonus: " << endl;
    cout << "************************************************************" << flush;
    
    string x;
    cin >> x;
    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    clearScreen();
}

void GameScreen::displayIssuOrdersPhase()
{
    cout << "************************************************************" << endl;
    cout << "Displaying Issue Orders Phase Info for " << *_subject->getCurrentPlayer() << ":" << endl;
    cout << "Reinforcements Available:" << _subject->getCurrentPlayer()->getCurrentReinforcements() << endl;
    cout << "\nTerritories To Defend:" << endl;
    for (Territory* territory : *_subject->getCurrentPlayer()->toDefend(*_subject->getGameMap()))
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

    string x;
    cin >> x;
    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    clearScreen();
}

void GameScreen::displayExecuteOrdersPhase()
{
    cout << "Displaying Execute Orders Phase Info for " << *_subject->getCurrentPlayer() << endl;
}

void GameScreen::displayStats()
{
    cout << "Displaying Stats Info" << endl;
}
//pathetic implementation to clear the output window, better than calling 'system' and suitable for program of this size.
void GameScreen::clearScreen()
{
    for(int i =0; i<10; i++)
    {
        cout << "\n\n\n\n\n\n\n\n\n\n"; 
    }
}

GameController::GameController(GameScreen* newView, WarzoneGame* newModel)
{
    gameView = newView;
    gameModel = newModel;
}

void GameController::controlGame()
{
    cout << "Starting game...\n" <<endl;
    gameModel->mainGameLoop();
}