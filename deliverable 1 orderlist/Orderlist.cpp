#include <iostream>
#include "Orderlist.h"
#pragma once
/*
Orderlist cpp file
This class holds the implmentation of Orderlist, a list that holds orders.
yet to be tested
*/

	//defualt constructor
	//may vary l8r depending on how ptr is decided  for now...
	//ptr is assigned a static array of Order objects and sets them all to null as you cant remove object antries
	Orderlist::Orderlist() {
		ptr = new vector<Order*>();
	}
	//destructor for orderlist
	Orderlist::~Orderlist() {
		if (ptr == NULL) return;
		for (int i = 0; i < ptr->size(); i++) {
			delete ptr->at(i);
		}
	}
	// copy constructor, should not be used in the context of hte program
	Orderlist::Orderlist(const Orderlist& ol) {
		
	}
	//assignment operator, similary should not be used in this program
	Orderlist& Orderlist::operator = (const Orderlist& o) {
		
		
		return *this;
	}
	//stream output operator, will need to be used in driver but not in the program
	
	ostream& operator << (ostream& stream, Orderlist& o) {
		string s = "the elements in this list are:\n";
		stream << s;
		for (int i = 0; i < o.ptr->size(); i++) {
			stream << *o.ptr->at(i);
			stream << "\n";
		}
			stream << "that is all the objects in this list\n";
			return stream;
	}
	//removes an object at location i and moves all non null objects ahead
	bool Orderlist::remove(int i) {
		if (i <= ptr->size() - 1) {
			ptr->erase(ptr->begin() + i);
			return true;
		}
		else return false;
	}
	//moves an object from position i to position j 
	//and moves all the ones it displaced back
	bool Orderlist::move(int i, int location) {
		if (location > ptr->size() - 1 || i > ptr->size() - 1 || i < 0 || location < 0)return false;
		ptr->insert(ptr->begin() + location, ptr->at(i));
		ptr->erase(ptr->begin() + i + 1);
		return true;
	}
	void Orderlist::add(Advanceorder& o) {
		//this calls the copy constructor
		ptr->push_back(new Advanceorder(o));

	}
	void Orderlist::add(airliftorder& o) {
		//this calls the copy constructor
		ptr->push_back(new airliftorder(o));

	}
	void Orderlist::add(Blockadeorder& o) {
		//this calls the copy constructor
		ptr->push_back(new Blockadeorder(o));

	}
	void Orderlist::add(Bomborder& o) {
		//this calls the copy constructor
		ptr->push_back(new Bomborder(o));

	}
	void Orderlist::add(Deployorder& o) {
		//this calls the copy constructor
		ptr->push_back(new Deployorder(o));

	}
	void Orderlist::add(Negotiateorder& o) {
		//this calls the copy constructor
		ptr->push_back(new Negotiateorder(o));

	}
	void Orderlist::add(Reinforcementorder& o) {
		//this calls the copy constructor
		ptr->push_back(new Reinforcementorder(o));

	}
	//executes orders and then deletes them all
	void Orderlist::executelist() {
		cout << "\n";
		for (int i = 0; i < ptr->size(); i++) {
			ptr->at(i)->execute();
		}
		cout << "\n";
		for (int i = 0; i < ptr->size(); i= i+0) {
			remove(0);
		}
	}