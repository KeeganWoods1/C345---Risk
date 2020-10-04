#pragma once
#include "Order.h"
class Advanceorder {
public:
	Advanceorder(int i,int sourceterritory, int destinationterritory, int orderplayer);
	bool validate();
	bool execute();
	~Advanceorder();
	Advanceorder(const Advanceorder&);
	Advanceorder& operator = (const Advanceorder& o);
	friend istream& operator >> (istream& stream, Advanceorder& o);
	friend ostream& operator << (ostream& out, const Advanceorder& o);
private:
	int* troopnum;
	int* sourceterritory;
	int* destinationterritory;
	int* orderplayer;

	//may also need a pointer to two Territory objects and a player pointer to make sure the player calling the order is the owner of source

};