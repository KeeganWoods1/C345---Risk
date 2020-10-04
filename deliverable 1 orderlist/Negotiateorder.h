#pragma once
#include "Order.h"
class Negotiateorder {
	Negotiateorder(int i,int j);
	bool validate();
	bool execute();
	~Negotiateorder();
	Negotiateorder(const Negotiateorder&);
	Negotiateorder& operator = (const Negotiateorder& o);
	friend istream& operator >> (istream& stream, Negotiateorder& o);
	friend ostream& operator << (ostream& out, const Negotiateorder& o);
private:
	int* orderplayer;
	int* otherplayer

	//may also need a pointer to two Territory objects and a player pointer to make sure the player calling the order is the owner of source
};
