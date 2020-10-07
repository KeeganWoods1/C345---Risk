#include <iostream>
#include "Orderlist.h"
#include "Order.cpp"
/*
Orderlist cpp file
This class holds the implmentation of Orderlist, a list that holds orders.
yet to be tested
*/

	//defualt constructor
	//may vary l8r depending on how ptr is decided  for now...
	//ptr is assigned a static array of Order objects and sets them all to null as you cant remove object antries
	Orderlist::Orderlist() {

		Order abc[100];
		ptr = abc;
		for (int i = 0; i < 100; i++) {
			if (!(ptr + i)->getisnull() || ptr+1 == NULL)(ptr + i)->setisnull(true);
		 }
	}
	//destructor for orderlist
	Orderlist::~Orderlist() {
		// may cause errors
		for (int i = 0; i < 100; i++) {
				delete (ptr + i);
		}
		delete[] ptr;
	}
	// copy constructor, should not be used in the context of hte program
	Orderlist::Orderlist(const Orderlist& ol) {
		Order temp[100];
		for (int i = 0; i < 100; i++) {
			temp[i] = *(ol.ptr + i);
		}
		ptr = ol.ptr;
	}
	//assignment operator, similary should not be used in this program
	Orderlist& Orderlist::operator = (const Orderlist& o) {
		ptr = o.ptr;
	}
	//stream output operator, will need to be used in driver but not in the program
	/*
	friend ostream& Orderlist::operator << (ostream& stream, Orderlist& o) {
		string s = "the elements in this list are:\n";
		stream << s;
		for (int i = 0; i < 100; i++) {
			 if (!(o.ptr + i)->getisnull()) stream << *(o.ptr + i) << "\n";
		}
			stream << "that is all the objects in this list\n";
	}*/
	//removes an object at location i and moves all non null objects ahead
	bool Orderlist::remove(int i) {
		if (i < 0 || i > 99) return false;
		delete (ptr + i);
		//may be invalid pointer
		(ptr + i)->setisnull(true);
		for (int j = i; j < 99; j++) {
			if (!(ptr + j + 1)->getisnull()) {
				*(ptr + j) = *(ptr + j + 1);
				remove(j + 1);
			}
		}
		return true;
	}
	//moves an object from position i to position j 
	//and moves all the ones it displaced back
	bool Orderlist::move(int i, int location) {
		if (i < 0 || i > 99) return false;
		//if ();
	}
	//adds an order to the list at the end
	void Orderlist::add(Order & o) {
		for (int i = 0; i < 100; i++) {
			if ((ptr + i)->getisnull()) {
				*(ptr + i) = o;
			}
		}

	}