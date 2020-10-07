#include <iostream>
#include "Order.h"
using namespace std;
class Order {
public:
	Order() { isnull = true; };
	Order(bool b) { isnull = b; };
	virtual bool validate() {
		return true;
	}
	virtual bool execute() {
		return true;
	}
	~Order() { isnull = true; };
	Order(const Order&) {}
		;
		Order& operator = (const Order & o) {};
		friend istream& operator >> (istream& stream, Order& o) {
		
		};
		friend ostream& operator << (ostream& out, const Order& o) {

		};
		bool getisnull() {
			return isnull;
		}
		void setisnull(bool b) {
			isnull = b;
		}
private:
	bool isnull;
};
class Advanceorder : public Order {
public:
	Advanceorder(int i, Player orderp, Territory destt, Territory souret): Order(true) {
		troopnum = new int;
		//temporary, replace int with appropriate class
		*troopnum = i;
		*orderplayer = orderp;
		*destinationterritory = destt;
		*sourceterritory = souret;
	}
	bool validate() {
		// check if two terretories are adjacent and troopnum does not exceed terretories troop count;
		return true;
	}
	bool execute() {
		if (validate) {
			cout << this;
			return true;
		}
		return false;
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
	Territory* sourceterritory;
	Territory* destinationterritory;
	Player* orderplayer;
};
class airliftorder : public Order {
public:
	//will need to add the other pointers to the consturctor and destructor
	airliftorder(int i, Territory sourceterritory, Territory destinationterritory, Player orderplayer);
	bool validate();
	bool execute();
	~airliftorder();
	airliftorder(const airliftorder&);
	airliftorder& operator = (const airliftorder& o);
	friend istream& operator >> (istream& stream, airliftorder& o);
	friend ostream& operator << (ostream& out, const airliftorder& o);
private:
	int* troopnum;
	Territory* sourceterritory;
	Territory* destinationterritory;
	Player* orderplayer;
	//may also need a pointer to two Territory objects and a player pointer to make sure the player calling the order is the owner of source
};
class Blockadeorder : public Order {
	Blockadeorder(Player orderp, Territory destt);
	bool validate();
	bool execute();
	~Blockadeorder();
	Blockadeorder(const Blockadeorder&);
	Blockadeorder& operator = (const Blockadeorder& o);
	friend istream& operator >> (istream& stream, Blockadeorder& o);
	friend ostream& operator << (ostream& out, const Blockadeorder& o);
private:
	Player* orderplayer;
	Territory* destinationterritory;
};
class Bomborder : public Order {
	Bomborder(Player orderp, Territory destt);
	bool validate();
	bool execute();
	~Bomborder();
	Bomborder(const Bomborder&);
	Bomborder& operator = (const Bomborder& o);
	friend istream& operator >> (istream& stream, Bomborder& o);
	friend ostream& operator << (ostream& out, const Bomborder& o);
private:
	Player* orderplayer;
	Territory* destinationterritory;
};
class Deployorder : public Order {
	Deployorder(Player orderp, int j, Territory destinationterritory);
	bool validate();
	bool execute();
	~Deployorder();
	Deployorder(const Deployorder&);
	Deployorder& operator = (const Deployorder& o);
	friend istream& operator >> (istream& stream, Deployorder& o);
	friend ostream& operator << (ostream& out, const Deployorder& o);
private:
	Player* orderplayer;
	int* troopnum;
	Territory destinationterritory;
};
class Negotiateorder : public Order {
	Negotiateorder(Player orderp, Player destp);
	bool validate();
	bool execute();
	~Negotiateorder();
	Negotiateorder(const Negotiateorder&);
	Negotiateorder& operator = (const Negotiateorder& o);
	friend istream& operator >> (istream& stream, Negotiateorder& o);
	friend ostream& operator << (ostream& out, const Negotiateorder& o);
private:
	Player* orderplayer;
	Player* otherplayer;

	//may also need a pointer to two Territory objects and a player pointer to make sure the player calling the order is the owner of source
};
class Reinforcementorder : public Order {
public:
	Reinforcementorder(Player orderp);
	bool validate();
	bool execute();
	~Reinforcementorder();
	Reinforcementorder(const Reinforcementorder&);
	Reinforcementorder& operator = (const Reinforcementorder& o);
	friend istream& operator >> (istream& stream, Reinforcementorder& o);
	friend ostream& operator << (ostream& out, const Reinforcementorder& o);
private:
	Player* orderplayer;

	//may also need a pointer to two Territory objects and a player pointer to make sure the player calling the order is the owner of source
};