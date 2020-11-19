#pragma once
#include <list>
#include <string>
#include<iostream>

using namespace std;
class WarzoneGame;

class Observer
{
    public:
        virtual void Update() =0;
        ~Observer();

        Observer(const Observer& obs);
        Observer& operator = ( const Observer& obs);
        friend ostream &operator << (ostream& out, const Observer& o);
    protected:
        Observer();
};
//superclass of model
class Subject
{
    public:
        virtual void Attach(Observer* o);
        virtual void Detach(Observer* o);
        virtual void Notify();
        Subject();
        ~Subject();
        Subject(const Subject& obs);
        Subject& operator = (const Subject& obs);
        friend ostream& operator << (ostream& out, const Subject& o);
    private:
        std::list<Observer*>* _observers;
};
//phase view
class GameScreen : public Observer
{
    public:
        GameScreen();
        GameScreen(WarzoneGame* s);
        ~GameScreen();
        void Update();
        void displayReinforcementPhase();
        void displayIssuOrdersPhase();
        void displayExecuteOrdersPhase();
        void clearScreen();
        GameScreen(const GameScreen& obs);
        GameScreen& operator = (const GameScreen& obs);
        friend ostream& operator << (ostream& out, const GameScreen& o);
    private:
        WarzoneGame* _subject;
};
//stats view
class StatsScreen : public Observer
{
    public:
        StatsScreen();
        StatsScreen(WarzoneGame* s);
        ~StatsScreen();
        void Update();
        void Display();
        void displayWin();
        void clearScreen();
        StatsScreen(const StatsScreen& obs);
        StatsScreen& operator = (const StatsScreen& obs);
        friend ostream& operator << (ostream& out, const StatsScreen& o);
    private:
        WarzoneGame* _subject;
};
//controller
class GameController
{
    public:
        GameController(GameScreen* newView, StatsScreen* otherView, WarzoneGame* newModel);
        void controlGame();
        GameController(const GameController& obs);
        GameController& operator = (const GameController& obs);
        friend ostream& operator << (ostream& out, const GameController o);
    private:
        GameScreen* gameView;
        StatsScreen* statsView;
        WarzoneGame* gameModel;
};