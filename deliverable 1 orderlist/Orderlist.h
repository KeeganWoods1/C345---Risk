#pragma once
#include "Order.h"
#include <vector>
/*
Class orderlist
holds a list of orders and is able to execute the order, move them around, remove them and add them.
using a pointer to an object array but uncertain will check if this makes sense later
*/
class Orderlist {
public:
	//constructor
	Orderlist();
	//destructor
	~Orderlist();
	// copy constructor
	Orderlist(const Orderlist& ol);
	//assignment operator
	Orderlist& operator = (const Orderlist& o);
	// insertion stream operator
	friend ostream& operator << (ostream& stream, Orderlist& o);
	// basic remove, move and add functions
	bool remove(int i);
	bool move(int i, int location);
	void add(Advanceorder& o);
	void add(airliftorder& o);
	void add(Blockadeorder& o);
	void add(Bomborder& o);
	void add(Deployorder& o);
	void add(Negotiateorder& o);
	void add(Reinforcementorder& o);
	vector<Order*>* ptr;
private:
	//pointer to object order array
	///REquires major testing so dont assum this is permanant (should be good after wednesday the 
	//vector<Order*>* ptr;

};