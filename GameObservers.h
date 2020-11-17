#pragma once
#include <list>
#include <string>

class WarzoneGame;

class Observer
{
    public:
        virtual void Update() =0;
        ~Observer();
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
    private:
        WarzoneGame* _subject;
};
//controller
class GameController
{
    public:
        GameController(GameScreen* newView, StatsScreen* otherView, WarzoneGame* newModel);
        void controlGame();
    private:
        GameScreen* gameView;
        StatsScreen* statsView;
        WarzoneGame* gameModel;
};