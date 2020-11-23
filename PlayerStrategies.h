#pragma once
#include "map.h"
#include "Player.h"
#include"Cards.h"
#include <vector>
class Deck;
//BASE CLASS TO be derived and is the foundation of the "strategy" part of the stretegy design pattern (with gameengine.cpp being the context)
class PlayerStrategy {
public:
	//abstract method (makes the whole method an "interface")
	virtual void issueorder(Map* m, vector<Player*>* pl, Player* curplayer, Deck* deckpointer) {};
	// default constructor
	PlayerStrategy();
	//destructor
	~PlayerStrategy();
	//copy constructor
	PlayerStrategy(const PlayerStrategy& h);
	//assignment operator
	PlayerStrategy& operator = (const PlayerStrategy& h);
	//stream insertion override
	friend ostream& operator << (ostream& out,  PlayerStrategy& o);
	//to attack and to defend methods
	virtual vector<Territory*>* toAttack(Map* m, Player* p, Territory* t) { return NULL; };
	virtual vector<Territory*>* toAttack(Map* m, Player* p) { return NULL; };
	virtual vector<Territory*>* toDefend(Map* m, Player* p) { return NULL; };
	//getter method (no setter method by design, although it may be needed if there were a "drop-in drop-out" feature [see Civlization 5 pit boss mode)
};
//derived class that implements humanPlayerStrategy issue order (the concrete implementation of the strategy design pattern)
class HumanPlayerStrategy : public PlayerStrategy {
public:
	// main function that acts as part of the strategy design pattern
	void issueorder(Map* m, vector<Player*>* pl, Player* curplayer, Deck* deckpointer);
	//constructor
	HumanPlayerStrategy();
	//empty destructor
	~HumanPlayerStrategy();
	//copy constructor
	HumanPlayerStrategy(const HumanPlayerStrategy& h);
	//assignment operator ovveride
	HumanPlayerStrategy& operator = (const HumanPlayerStrategy& h);
	//stream insertion ovveride
	friend ostream& operator << (ostream& out,  HumanPlayerStrategy& o);
	//to attack and to defend methods
	vector<Territory*>* toAttack(Map* m, Player* p, Territory* t);
	vector<Territory*>* toAttack(Map* m, Player* p);
	vector<Territory*>* toDefend(Map* m, Player* p);
};
//derived class that implements aggressive player strategy
class AggressivePlayerStrategy : public PlayerStrategy {
public:
	//main function that acts as the concrete implementation part of the strategy design pattern
	void issueorder(Map* m, vector<Player*>* pl, Player* curplayer, Deck* deckpointer);
	//constructor
	AggressivePlayerStrategy ();
	//destructor
	~AggressivePlayerStrategy ();
	//copu constructor
	AggressivePlayerStrategy (const AggressivePlayerStrategy & h);
	//assignment override constructor 
	AggressivePlayerStrategy & operator = (const AggressivePlayerStrategy & h);
	//stream insertion override
	friend ostream& operator << (ostream& out,  AggressivePlayerStrategy & o);
	//to attack and to defend methods
	vector<Territory*>* toAttack(Map* m, Player* p, Territory* t);
	vector<Territory*>* toAttack(Map* m, Player* p);
	vector<Territory*>* toDefend(Map* m, Player* p);
};
//derived class that implements BenevolentPlayerStrategy issue order
class BenevolentPlayerStrategy : public PlayerStrategy {
public:
	//main function for concrete implementation
	void issueorder(Map* m, vector<Player*>* pl, Player* curplayer, Deck* deckpointer);
	//constructor
	BenevolentPlayerStrategy();
	//destructor
	~BenevolentPlayerStrategy();
	//copy constructor
	BenevolentPlayerStrategy(const BenevolentPlayerStrategy& h);
	//assignment operator
	BenevolentPlayerStrategy& operator = (const BenevolentPlayerStrategy& h);
	//stream insertion override
	friend ostream& operator << (ostream& out,  BenevolentPlayerStrategy& o);
	//to attack and to defend methods
	vector<Territory*>* toAttack(Map* m, Player* p, Territory* t);
	vector<Territory*>* toAttack(Map* m, Player* p);
	vector<Territory*>* toDefend(Map* m, Player* p);
};
//derived class that implements NeutralPlayerStrategy issue order
class NeutralPlayerStrategy : public PlayerStrategy {
public:
	//main function
	void issueorder(Map* m, vector<Player*>* pl, Player* curplayer, Deck* deckpointer);
	//constructor
	NeutralPlayerStrategy();
	//destructor
	~NeutralPlayerStrategy();
	//copy constructor
	NeutralPlayerStrategy(const NeutralPlayerStrategy& h);
	//assignemnt operator
	NeutralPlayerStrategy& operator = (const NeutralPlayerStrategy& h);
	//stream insertion operator
	friend ostream& operator << (ostream& out,  NeutralPlayerStrategy& o);
	//to attack and to defend methods
	vector<Territory*>* toAttack(Map* m, Player* p, Territory* t);
	vector<Territory*>* toAttack(Map* m, Player* p);
	vector<Territory*>* toDefend(Map* m, Player* p);
};
//the contest class of the deisng strategy pattern