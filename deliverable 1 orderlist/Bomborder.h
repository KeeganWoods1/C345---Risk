#pragma once
#include "Order.h";
class Bomborder {
	Bomborder(int i, int j);
	bool validate();
	bool execute();
	~Bomborder();
	Bomborder(const Bomborder&);
	Bomborder& operator = (const Bomborder& o);
	friend istream& operator >> (istream& stream, Bomborder& o);
	friend ostream& operator << (ostream& out, const Bomborder& o);
private:
	int* orderplayer;
	int* destinationterritory
};