#include <iostream>;
#include "Advanceorder.h";
class Advanceorder {
public:
	Advanceorder(int i, int& souret, int& destt, int& orderp) {
		troopnum = new int;
		//temporary, replace int with appropriate class
		*troopnum = i;/*
		orderplayer = orderp;
		destinationterritory = destt;
		sourceterritory = souret;*/
	}
	bool validate() {
		// check if two terretories are adjacent and troopnum does not exceed terretories troop count;
		return true;
	}
	bool execute() {
		return true;
	};
	~Advanceorder() {
		delete troopnum;
		delete sourceterritory;
		delete destinationterritory;
		delete orderplayer;
	}
	Advanceorder(const Advanceorder&) {
	
	
	}
	Advanceorder& operator = (const Advanceorder& o) {

	}
	friend istream& operator >> (istream& stream, Advanceorder& o) {

	}
	friend ostream& operator << (ostream& out, const Advanceorder& o) {

	}
private:
	int* troopnum;
	int* sourceterritory;
	int* destinationterritory;
	int* orderplayer;
};