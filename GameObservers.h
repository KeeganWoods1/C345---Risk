#pragma once
#include <list>
#include <string>

class WarzoneGame;

class Observer
{
    public:
        virtual void updatePhase(int) =0;
        virtual void updateStats() =0;
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
        virtual void NotifyPhase(int);
        virtual void NotifyStats();
        Subject();
        ~Subject();
    private:
        std::list<Observer*>* _observers;
};

//view
class GameScreen : public Observer
{
    public:
        GameScreen();
        GameScreen(WarzoneGame* s);
        ~GameScreen();
        void updatePhase(int);
        void updateStats();
        void displayReinforcementPhase();
        void displayIssuOrdersPhase();
        void displayExecuteOrdersPhase();
        void displayStats();
        void clearScreen();
    private:
        WarzoneGame* _subject;
};
//controller
class GameController
{
    public:
        GameController(GameScreen* newView, WarzoneGame* newModel);
        void controlGame();
    private:
        GameScreen* gameView;
        WarzoneGame* gameModel;
};