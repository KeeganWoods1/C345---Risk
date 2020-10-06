#include <iostream>
#include "Orderlist.h"
#include "Order.cpp"
class Orderlist {
public:
	Orderlist() {

		Order abc[100];
		ptr = abc;
		for (int i = 0; i < 100; i++) {
			if (!(ptr + i)->getisnull() || ptr+1 == NULL)(ptr + i)->setisnull(true);
		 }
	}
	~Orderlist() {
		// may cause errors
		for (int i = 0; i < 100; i++) {
				delete (ptr + i);
		}
		delete[] ptr;
	}
	Orderlist(const Orderlist& ol) {
		Order temp[100];
		for (int i = 0; i < 100; i++) {
			temp[i] = *(ol.ptr + i);
		}
		ptr = ol.ptr;
	}
	Orderlist& operator = (const Orderlist& o) {
		ptr = o.ptr;
	}
	friend ostream& operator << (ostream& stream, Orderlist& o) {
		string s = "the elements in this list are:\n";
		stream << s;
		for (int i = 0; i < 100; i++) {
			 if (!(o.ptr + i)->getisnull()) stream << *(o.ptr + i) << "\n";
		}
			stream << "that is all the objects in this list\n";
	}
	bool remove(int i) {
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
	bool move(int i, int location) {
		if (i < 0 || i > 99) return false;
		if ();
	}
	void add(Order & o) {
		for (int i = 0; i < 100; i++) {
			if ((ptr + i)->getisnull()) {
				*(ptr + i) = o;
			}
		}

	}
private:
	//Order* ptr[100];
	Order* ptr;
};