#pragma once
#include "Player.h"
#include "map.h"
#include <vector>
//BASE CLASS TO be derived and is the foundation of the "strategy" part of the stretegy design pattern (with gameengine.cpp being the context)
class PlayerStrategy {
public:
	//abstract method (makes the whole method an "interface")
	virtual void issueorder(Map* m, vector<Player*>* pl) {};
	// parameter constructor
	PlayerStrategy(Player* p);
	//destructor
	~PlayerStrategy();
	//copy constructor
	PlayerStrategy(const PlayerStrategy& h);
	//assignment operator
	PlayerStrategy& operator = (const PlayerStrategy& h);
	//stream insertion override
	friend ostream& operator << (ostream& out,  PlayerStrategy& o);
	//getter method (no setter method by design, although it may be needed if there were a "drop-in drop-out" feature [see Civlization 5 pit boss mode)
	Player* getPlayer();
	//getter method that only returns the name of the player
	string getPlayerName();
private:
	//the shared player pointer (it is meant to be deleted as usual so to prevent double deletion, the pointer just changes its target to NULL)
	Player* player;
};
//derived class that implements humanPlayerStrategy issue order (the concrete implementation of the strategy design pattern)
class HumanPlayerStrategy : public PlayerStrategy {
public:
	// main function that acts as part of the strategy design pattern
	void issueorder(Map* m, vector<Player*>* pl);
	//constructor
	HumanPlayerStrategy(Player* p);
	//empty destructor
	~HumanPlayerStrategy();
	//copy constructor
	HumanPlayerStrategy(const HumanPlayerStrategy& h);
	//assignment operator ovveride
	HumanPlayerStrategy& operator = (const HumanPlayerStrategy& h);
	//stream insertion ovveride
	friend ostream& operator << (ostream& out,  HumanPlayerStrategy& o);
};
//derived class that implements aggressive player strategy
class AggressivePlayerStrategy : public PlayerStrategy {
public:
	//main function that acts as the concrete implementation part of the strategy design pattern
	void issueorder(Map* m, vector<Player*>* pl);
	//constructor
	AggressivePlayerStrategy (Player* p);
	//destructor
	~AggressivePlayerStrategy ();
	//copu constructor
	AggressivePlayerStrategy (const AggressivePlayerStrategy & h);
	//assignment override constructor 
	AggressivePlayerStrategy & operator = (const AggressivePlayerStrategy & h);
	//stream insertion override
	friend ostream& operator << (ostream& out,  AggressivePlayerStrategy & o);
};
//derived class that implements BenevolentPlayerStrategy issue order
class BenevolentPlayerStrategy : public PlayerStrategy {
public:
	//main function for concrete implementation
	void issueorder(Map* m, vector<Player*>* pl);
	//constructor
	BenevolentPlayerStrategy(Player* p);
	//destructor
	~BenevolentPlayerStrategy();
	//copy constructor
	BenevolentPlayerStrategy(const BenevolentPlayerStrategy& h);
	//assignment operator
	BenevolentPlayerStrategy& operator = (const BenevolentPlayerStrategy& h);
	//stream insertion override
	friend ostream& operator << (ostream& out,  BenevolentPlayerStrategy& o);
};
//derived class that implements NeutralPlayerStrategy issue order
class NeutralPlayerStrategy : public PlayerStrategy {
public:
	//main function
	void issueorder(Map* m, vector<Player*>* pl);
	//constructor
	NeutralPlayerStrategy(Player* p);
	//destructor
	~NeutralPlayerStrategy();
	//copy constructor
	NeutralPlayerStrategy(const NeutralPlayerStrategy& h);
	//assignemnt operator
	NeutralPlayerStrategy& operator = (const NeutralPlayerStrategy& h);
	//stream insertion operator
	friend ostream& operator << (ostream& out,  NeutralPlayerStrategy& o);
};
//the contest class of the deisng strategy pattern
class Context {
public:
	//getter method
	string getPlayerName();
	//calls the stragtegies issue order
	void issueOrder(Map* m, vector<Player*>* pl);
	//constructor
	Context(PlayerStrategy* playerstrat);
	//destructor
	~Context();
	//copy ocnstructor
	Context(const Context& c);
	//assignment operator
	Context& operator = (const Context& c);
	//stream insertion operator
	friend ostream& operator << (ostream& out, Context& o);
private:
	//private variable that hodls the execution
	PlayerStrategy* ps;
};