#pragma once
#include "Order.h";
class Deployorder {
	Deployorder(int i, int j);
	bool validate();
	bool execute();
	~Deployorder();
	Deployorder(const Deployorder&);
	Deployorder& operator = (const Deployorder& o);
	friend istream& operator >> (istream& stream, Deployorder& o);
	friend ostream& operator << (ostream& out, const Deployorder& o);
private:
	int* orderplayer;
	int* troopnum
};