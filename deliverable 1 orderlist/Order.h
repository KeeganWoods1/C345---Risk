#pragma once
#include <iostream>
using namespace std;
class Order {
public:
	Order();
	virtual bool validate();
	virtual bool execute();
	~Order();
	Order(const Order&);
	Order& operator = (const Order& o);
	friend istream &operator >> (istream& stream, Order& o);
	friend ostream& operator << (ostream& out, const Order& o);
private:
};