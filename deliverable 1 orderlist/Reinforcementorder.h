#pragma once
#include "Order.h"
class Reinforcementorder {
public:
	Reinforcementorder(int i);
	bool validate();
	bool execute();
	~Reinforcementorder();
	Reinforcementorder(const Reinforcementorder&);
	Reinforcementorder& operator = (const Reinforcementorder& o);
	friend istream& operator >> (istream& stream, Reinforcementorder& o);
	friend ostream& operator << (ostream& out, const Reinforcementorder& o);
private:
	int* orderplayer;

	//may also need a pointer to two Territory objects and a player pointer to make sure the player calling the order is the owner of source
};