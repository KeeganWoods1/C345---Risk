#pragma once
#include "Order.h"
class Orderlist {
public:
	Orderlist();
	~Orderlist();
	Orderlist(const Orderlist&);
	Orderlist& operator = (const Orderlist& o);
	friend istream& operator >> (istream& stream, Orderlist& o);
	boolean remove(Order* ptr);
	boolean move(Order* ptr, int location);
private:
	Order* ptr;

};