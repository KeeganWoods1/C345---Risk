#pragma once
#include "Order.h"
#include <sstream>
// Do to the length of this file all comments will be algorith mrealted. for more general comments check the Order.h file
// abstract class parent class, no algorithm so for this class all comments are in Order.h
	Order::Order() { isnull = true; };
	Order::Order(bool b) { isnull = b; };
	Order::~Order() { isnull = true; };
	Order::Order(const Order&) { 
		isnull = false;
	};
	Order& Order::operator = (const Order& o) { return *this; };
	ostream& operator << (ostream& out, const Order& o) { out << o.print(); return out; };
	bool Order::getisnull() {
		return isnull;
	}
	void Order::setisnull(bool b) {
		isnull = b;
	}
	Advanceorder::Advanceorder() {

	}
	Advanceorder::Advanceorder(int i, Player orderp, Territory destt, Territory souret): Order(true) {
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
		if (validate()) {
			cout << "executing advance order by " + orderplayer->getName() + " and is " + to_string(*troopnum) + " units attacking " + destinationterritory->getTerritoryName() + " from " + sourceterritory->getTerritoryName() + "\n";
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
	string Advanceorder::print()const {
		return "this is an advance order by " + orderplayer->getName() + " and is " + to_string(*troopnum) + " units attacking " + destinationterritory->getTerritoryName() + " from " + sourceterritory->getTerritoryName();
	}
	Advanceorder::Advanceorder(const Advanceorder& old) {
		troopnum = new int(*old.troopnum);
		sourceterritory = new Territory(*old.sourceterritory);
		destinationterritory = new Territory(*old.destinationterritory);
		orderplayer = new Player(*old.orderplayer);
		cout << "this called\n";
	}
	Advanceorder& Advanceorder::operator = (const Advanceorder& old) {
		cout <<"that is called\n";
		troopnum = old.troopnum;
		sourceterritory = old.sourceterritory;
		destinationterritory = old.destinationterritory;
		orderplayer = old.orderplayer;
		return *this;
	}
	ostream& operator << (ostream& out, Advanceorder& o) {
		out << o.print();
		return out;
	}
	Airliftorder::Airliftorder(int i, Territory sourcet, Territory destinationt, Player orderp) {
		troopnum = new int(i);
		//when using map use copy constructors and new
		sourceterritory = new Territory(sourcet);
		destinationterritory = new Territory(destinationt);
		orderplayer =new Player(orderp);

	}
	bool Airliftorder::validate() {
		//check if both are player owned and match the troop num
		if (*troopnum < 1)return false;
		return true;
	}
	bool Airliftorder::execute() {
		if (validate()) {
			cout << "executing Airlift order by " + orderplayer->getName() + " and is " + to_string(*troopnum) + " troops being Airlifted to " + destinationterritory->getTerritoryName() + " from " + sourceterritory->getTerritoryName() + "\n";
			return true;
		}
		else return false;
	}
	Airliftorder::~Airliftorder() {
		delete troopnum;
		delete sourceterritory;
		delete destinationterritory;
		delete orderplayer;
	}
	Airliftorder::Airliftorder(const Airliftorder& old) {
		troopnum = new int(*old.troopnum);
		sourceterritory = new Territory(*old.sourceterritory);
		destinationterritory = new Territory(*old.destinationterritory);
		orderplayer = new Player(* old.orderplayer);
	}
	Airliftorder& Airliftorder::operator = (const Airliftorder& old) {
		troopnum = old.troopnum;
		sourceterritory = old.sourceterritory;
		destinationterritory = old.destinationterritory;
		orderplayer = old.orderplayer;
		return *this;
	}
	ostream& operator << (ostream& out, Airliftorder& o) {
		out << o.print();
		return out;
	}
	string Airliftorder::print() const{
		string s = "this is an Airlift order by " + orderplayer->getName() + " and is " + to_string(*troopnum) + " troops being Airlifted to " + destinationterritory->getTerritoryName() + " from " + sourceterritory->getTerritoryName();
		return s;

	}
	string Blockadeorder::print()const {
		string s = "this is a blockade order from " + orderplayer->getName() + ", to blockade territory " + destinationterritory->getTerritoryName() ;
		return s;
	}
	Blockadeorder::Blockadeorder(Player orderp, Territory destt) {
		orderplayer = new Player(orderp);
		destinationterritory = new Territory(destt);
	}
	bool Blockadeorder::validate() {
		return true;
	}
	bool Blockadeorder::execute() {
		if (validate()) {
			cout << "executing blockade order from " + orderplayer->getName() + ", to blockade territory " + destinationterritory->getTerritoryName() + "\n";
			return true;
		}
		else return false;
	}
	Blockadeorder::~Blockadeorder() {
		delete orderplayer;
		delete destinationterritory;
	}
	Blockadeorder::Blockadeorder(const Blockadeorder& old) {
		orderplayer = new Player(*old.orderplayer);
		destinationterritory = new Territory(*old.destinationterritory);
	}
	Blockadeorder& Blockadeorder::operator = (const Blockadeorder& old) {
		orderplayer = old.orderplayer;
		destinationterritory = old.destinationterritory;
		return *this;
	}
	ostream& operator << (ostream& out, const Blockadeorder& o) {
		out << o.print();
		return out;
	}
	string Bomborder::print() const {
		string s = "this is a bomb order from " + orderplayer->getName() + " on country " + destinationterritory->getTerritoryName();
			return s;
	}
	Bomborder::Bomborder(Player orderp, Territory destt) {
		orderplayer = new Player(orderp);
		destinationterritory = new Territory(destt);
	}
	bool Bomborder::validate() {
		return true;
	}
	bool Bomborder::execute() {
		if (validate()) {
			cout << "executing bomb order from " + orderplayer->getName() + " on country " + destinationterritory->getTerritoryName() + "\n";
			return true;
		}
		else return false;
	}
	Bomborder::~Bomborder() {
		delete orderplayer;
		delete destinationterritory;
	}
	Bomborder::Bomborder(const Bomborder& old) {
		orderplayer = new Player(*old.orderplayer);
		destinationterritory = new Territory(*old.destinationterritory);
	}
	Bomborder& Bomborder::operator = (const Bomborder& old) {
		orderplayer = old.orderplayer;
		destinationterritory = old.destinationterritory;
		return *this;

	}
	ostream& operator << (ostream& out, const Bomborder& o) {
		out << o.print();
		return out;

	}
	string Deployorder::print() const {
		string s = "this is a deploy order from " + orderplayer->getName() + " to deploy " + to_string(*troopnum) + " troops to " + destinationterritory->getTerritoryName();
		return s;
	}
	Deployorder::Deployorder(Player orderp, int j, Territory destt) {
		orderplayer = new Player(orderp);
		troopnum = new int(j);
		destinationterritory = new Territory(destt);
	}
	bool Deployorder::validate() {
		return true;
	}
	bool Deployorder::execute() {
		if (validate()) {
			cout << "executing deploy order from " + orderplayer->getName() + " to deploy " + to_string(*troopnum) + " troops to " + destinationterritory->getTerritoryName() + "\n";
			return true;
		}
		else return false;
	}
	Deployorder::~Deployorder() {
		delete troopnum;
		delete orderplayer;
		delete destinationterritory;
	}
	Deployorder::Deployorder(const Deployorder& old) {
		troopnum = new int(*old.troopnum);
		orderplayer = new Player(*old.orderplayer);
		destinationterritory = new Territory(*old.destinationterritory);
	}
	Deployorder& Deployorder::operator = (const Deployorder& old) {
		troopnum = old.troopnum;
		orderplayer = old.orderplayer;
		destinationterritory = old.destinationterritory;
		return *this;
	}
	ostream& operator << (ostream& out, const Deployorder& o) {
		out << o.print();
		return out;

	}
	string Negotiateorder::print() const {
		string s = "this is a negotiate order from " + orderplayer->getName() + " to " + otherplayer->getName();
		return s;
	}
	Negotiateorder::Negotiateorder(Player orderp, Player destp) {
		orderplayer = new Player(orderp);
		otherplayer = new Player(destp);
	}
	bool Negotiateorder::validate() {
		return true;
	}
	bool Negotiateorder::execute() {
		if (validate()) {
			cout << "executing negotiate order from " + orderplayer->getName() + " to " + otherplayer->getName() + "\n";
			return true;
		}
		else return false;
	}
	Negotiateorder::~Negotiateorder() {
		delete orderplayer;
		delete otherplayer;
	}
	Negotiateorder::Negotiateorder(const Negotiateorder& old) {
		orderplayer = new Player(*old.orderplayer);
		otherplayer = new Player(*old.otherplayer);
	}
	Negotiateorder& Negotiateorder::operator = (const Negotiateorder& old) {
		orderplayer = old.orderplayer;
		otherplayer = old.otherplayer;
		return *this;
	}
	ostream& operator << (ostream& out, const Negotiateorder& o) {
		out << o.print();
		return out;
	}
	string Reinforcementorder::print() const {
		string s = "this is a Reinforcement order from " + orderplayer->getName() + " to reinforce their army with 5 troops";
		return s;
	}
	Reinforcementorder::Reinforcementorder(Player orderp) {
		orderplayer = new Player(orderp);
	}
	bool Reinforcementorder::validate() {
		return true;
	}
	bool Reinforcementorder::execute() {
		if (validate()) {
			cout<< "executing Reinforcement order from " + orderplayer->getName() + " to reinforce their army with 5 troops" + "\n";
			return true;
		}
		else return false;
	}
	Reinforcementorder::~Reinforcementorder() {
		delete orderplayer;
	}
	Reinforcementorder::Reinforcementorder(const Reinforcementorder& old) {
		orderplayer = new Player(*old.orderplayer);
	}
	Reinforcementorder& Reinforcementorder::operator = (const Reinforcementorder& old) {
		orderplayer = old.orderplayer;
		return *this;

	}
	ostream& operator << (ostream& out, const Reinforcementorder& o) {
		out << o.print();
		return out;
	}