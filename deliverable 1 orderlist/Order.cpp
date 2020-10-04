#include <iostream>
#include "Order.h"
using namespace std;
class Order {
public:
	Order() {};
	virtual bool validate() {
		return true;
	}
	virtual bool execute() {
		return true;
	}
	~Order() {};
	Order(const Order&) {}
		;
		Order& operator = (const Order & o) {};
		friend istream& operator >> (istream& stream, Order& o) {
		
		};
		friend ostream& operator << (ostream& out, const Order& o) {

		};
private:
};