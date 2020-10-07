#include <iostream>
#include "Order.h"
using namespace std;
// Do to the length of this file all comments will be algorith mrealted. for more general comments check the Order.h file
// abstract class parent class, no algorithm so for this class all comments are in Order.h
	Order::Order() { isnull = true; };
	Order::Order(bool b) { isnull = b; };
	bool Order::validate() {
		return true;
	}
	bool Order::execute() {
		return true;
	}
	Order::~Order() { isnull = true; };
	Order::Order(const Order&) {};
	Order& Order::operator = (const Order & o) {};/*
	istream& operator >> (istream& stream, Order& o) {};
	ostream& operator << (ostream& out, const Order& o) {};*/
	bool Order::getisnull() {
		return isnull;
	}
	void Order::setisnull(bool b) {
		isnull = b;
	}

	Advanceorder::Advanceorder(int i, Player orderp, Territory destt, Territory souret): Order(true) {
		troopnum = new int;
		//temporary, replace int with appropriate class
		troopnum = new int(i);
		orderplayer = new Player(orderp);
		destinationterritory = new Territory(destt);
		sourceterritory = new Territory(souret);
	}
	bool Advanceorder::validate() {
		// check if two terretories are adjacent and troopnum does not exceed terretories troop count;
		return true;
	}
	bool Advanceorder::execute() {
		if (validate) {
			cout << *troopnum + " units advancing by " + orderplayer->getName() + " to " + destinationterritory->getTerritoryName() + " from " + sourceterritory->getTerritoryName();
			return true;
		}
		return false;
	};
	Advanceorder::~Advanceorder() {
		delete troopnum;
		delete sourceterritory;
		delete destinationterritory;
		delete orderplayer;
	}
	Advanceorder::Advanceorder(const Advanceorder&) {


	}
	Advanceorder& Advanceorder::operator = (const Advanceorder& o) {

	}/*
	friend istream& operator >> (istream& stream, Advanceorder& o) {

	}
	friend ostream& operator << (ostream& out, const Advanceorder& o) {

	}*/

	//will need to add the other pointers to the consturctor and destructor
	airliftorder::airliftorder(int i, Territory sourceterritory, Territory destinationterritory, Player orderplayer);
	bool airliftorder::validate();
	bool airliftorder::execute();
	airliftorder::~airliftorder();
	airliftorder::airliftorder(const airliftorder&);
	airliftorder& airliftorder::operator = (const airliftorder& o);/*
	friend istream& operator >> (istream& stream, airliftorder& o);
	friend ostream& operator << (ostream& out, const airliftorder& o);*/
	Blockadeorder::Blockadeorder(Player orderp, Territory destt);
	bool Blockadeorder::validate();
	bool Blockadeorder::execute();
	Blockadeorder::~Blockadeorder();
	Blockadeorder::Blockadeorder(const Blockadeorder&);
	Blockadeorder::Blockadeorder& operator = (const Blockadeorder& o);/*
	friend istream& operator >> (istream& stream, Blockadeorder& o);
	friend ostream& operator << (ostream& out, const Blockadeorder& o);*/
	Bomborder::Bomborder(Player orderp, Territory destt);
	bool Bomborder::validate();
	bool Bomborder::execute();
	Bomborder::~Bomborder();
	Bomborder::Bomborder(const Bomborder&);
	Bomborder::Bomborder& operator = (const Bomborder& o);/*
	friend istream& operator >> (istream& stream, Bomborder& o);
	friend ostream& operator << (ostream& out, const Bomborder& o);*/
	Deployorder::Deployorder(Player orderp, int j, Territory destinationterritory);
	bool Deployorder::validate();
	bool Deployorder::execute();
	Deployorder::~Deployorder();
	Deployorder::Deployorder(const Deployorder&);
	Deployorder::Deployorder& operator = (const Deployorder& o);/*
	friend istream& operator >> (istream& stream, Deployorder& o);
	friend ostream& operator << (ostream& out, const Deployorder& o);*/
	Negotiateorder::Negotiateorder(Player orderp, Player destp);
	bool Negotiateorder::validate();
	bool Negotiateorder::execute();
	Negotiateorder::~Negotiateorder();
	Negotiateorder::Negotiateorder(const Negotiateorder&);
	Negotiateorder::Negotiateorder& operator = (const Negotiateorder& o);/*
	friend istream& operator >> (istream& stream, Negotiateorder& o);
	friend ostream& operator << (ostream& out, const Negotiateorder& o);*/

	Reinforcementorder::Reinforcementorder(Player orderp);
	bool Reinforcementorder::validate();
	bool Reinforcementorder::execute();
	Reinforcementorder::~Reinforcementorder();
	Reinforcementorder::Reinforcementorder(const Reinforcementorder&);
	Reinforcementorder& Reinforcementorder::operator = (const Reinforcementorder& o);/*
	friend istream& operator >> (istream& stream, Reinforcementorder& o);
	friend ostream& operator << (ostream& out, const Reinforcementorder& o);*/