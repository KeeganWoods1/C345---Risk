#pragma once
#include "Order.h";
class Blockadeorder {
	Blockadeorder(int i, int j);
	bool validate();
	bool execute();
	~Blockadeorder();
	Blockadeorder(const Blockadeorder&);
	Blockadeorder& operator = (const Blockadeorder& o);
	friend istream& operator >> (istream& stream, Blockadeorder& o);
	friend ostream& operator << (ostream& out, const Blockadeorder& o);
private:
	int* orderplayer;
	int* destinationterritory;
};