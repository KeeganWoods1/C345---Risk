#pragma once
#include "Order.h"
class airliftorder {
public:
	//will need to add the other pointers to the consturctor and destructor
	airliftorder(int i, int sourceterritory, int destinationterritory, int orderplayer);
	bool validate();
	bool execute();
	~airliftorder();
	airliftorder(const airliftorder&);
	airliftorder& operator = (const airliftorder& o);
	friend istream& operator >> (istream& stream, airliftorder& o);
	friend ostream& operator << (ostream& out, const airliftorder& o);
private:
	int* troopnum;
	int* sourceterritory;
	int* destinationterritory;
	int* orderplayer;
	//may also need a pointer to two Territory objects and a player pointer to make sure the player calling the order is the owner of source
};
