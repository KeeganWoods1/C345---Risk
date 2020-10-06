#pragma once
#include "Order.h"
class Orderlist {
public:
	Orderlist();
	~Orderlist();
	Orderlist(const Orderlist& ol);
	Orderlist& operator = (const Orderlist& o);
	friend ostream& operator << (ostream& stream, Orderlist& o);
	bool remove(int i);
	bool move(int i, int location);
	void add(Order& o);
private:
	Order* ptr[100];

};