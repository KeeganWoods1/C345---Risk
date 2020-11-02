#include "Orders.h"
#include <iostream>

// Do to the length of this file all comments will be algorith mrealted. for more general comments check the Order.h file
// abstract class parent class, no algorithm so for this class all comments are in Order.h
	Order::Order() {};
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
	Advanceorder::Advanceorder(int* i, Player* orderp, Territory* destt, Territory* souret): Order(true) {
		troopnum = i;
		orderplayer = orderp;
		destinationterritory = destt;
		sourceterritory = souret;
	}
	bool Advanceorder::validate() {
		// check if two terretories are adjacent and troopnum does not exceed terretories troop count;
		return true;
	}
	bool Advanceorder::execute() {
		if (validate()) {
			cout << "executing advance order by " + orderplayer->getName() + " and is " + to_string(*troopnum) + " units attacking " + destinationterritory->getterritory_name() + " from " + sourceterritory->getterritory_name() + "\n";
			return true;
		}
		return false;
	};
	Advanceorder::~Advanceorder() {
	}
	string Advanceorder::print()const {
		return "this is an advance order by " + orderplayer->getName() + " and is " + to_string(*troopnum) + " units attacking " + destinationterritory->getterritory_name() + " from " + sourceterritory->getterritory_name();
	}
	Advanceorder::Advanceorder(const Advanceorder& old) {
		troopnum = new int(*old.troopnum);
		sourceterritory = new Territory(*old.sourceterritory);
		destinationterritory = new Territory(*old.destinationterritory);
		orderplayer = new Player(*old.orderplayer);
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
	Airliftorder::Airliftorder(int* i, Territory* sourcet, Territory* destinationt, Player* orderp) {
		troopnum = i;
		sourceterritory = sourcet;
		destinationterritory = destinationt;
		orderplayer = orderp;
	}
	bool Airliftorder::validate() {
		//check if both are player owned and match the troop num
		if (*troopnum < 1)return false;
		return true;
	}
	bool Airliftorder::execute() {
		if (validate()) {
			cout << "executing Airlift order by " + orderplayer->getName() + " and is " + to_string(*troopnum) + " troops being Airlifted to " + destinationterritory->getterritory_name() + " from " + sourceterritory->getterritory_name() + "\n";
			return true;
		}
		else return false;
	}
	Airliftorder::~Airliftorder() {
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
		string s = "this is an Airlift order by " + orderplayer->getName() + " and is " + to_string(*troopnum) + " troops being Airlifted to " + destinationterritory->getterritory_name() + " from " + sourceterritory->getterritory_name();
		return s;

	}
	string Blockadeorder::print()const {
		string s = "this is a blockade order from " + orderplayer->getName() + ", to blockade territory " + destinationterritory->getterritory_name() ;
		return s;
	}
	Blockadeorder::Blockadeorder(Player* orderp, Territory* destt) {
		orderplayer = orderp;
		destinationterritory = destt;
	}
	bool Blockadeorder::validate() {
		return true;
	}
	bool Blockadeorder::execute() {
		if (validate()) {
			cout << "executing blockade order from " + orderplayer->getName() + ", to blockade territory " + destinationterritory->getterritory_name() + "\n";
			return true;
		}
		else return false;
	}
	Blockadeorder::~Blockadeorder() {
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
		string s = "this is a bomb order from " + orderplayer->getName() + " on country " + destinationterritory->getterritory_name();
			return s;
	}
	Bomborder::Bomborder(Player* orderp, Territory* destt) {
		orderplayer = orderp;
		destinationterritory = destt;
	}
	bool Bomborder::validate() {
		return true;
	}
	bool Bomborder::execute() {
		if (validate()) {
			cout << "executing bomb order from " + orderplayer->getName() + " on country " + destinationterritory->getterritory_name() + "\n";
			return true;
		}
		else return false;
	}
	Bomborder::~Bomborder() {
		if(orderplayer == NULL) {cout << "OrderPlayer is null" << endl;}
		if(destinationterritory == NULL) {cout << "destinationterritory is null" << endl;}
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
		string s = "this is a deploy order from " + orderplayer->getName() + " to deploy " + to_string(*troopnum) + " troops to " + destinationterritory->getterritory_name();
		return s;
	}
	Deployorder::Deployorder(Player* orderp, int* j, Territory* destt) {
		orderplayer = orderp;
		troopnum = j;
		destinationterritory = destt;
	}
	bool Deployorder::validate() {
		return true;
	}
	bool Deployorder::execute() {
		if (validate()) {
			cout << "executing deploy order from " + orderplayer->getName() + " to deploy " + to_string(*troopnum) + " troops to " + destinationterritory->getterritory_name() + "\n";
			return true;
		}
		else return false;
	}
	Deployorder::~Deployorder() {
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
	Negotiateorder::Negotiateorder(Player* orderp, Player* destp) {
		orderplayer = orderp;
		otherplayer = destp;
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
	Reinforcementorder::Reinforcementorder(Player* orderp) {
		orderplayer = orderp;
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
	// copy constructor, should not be used in the context of the program
	Orderlist::Orderlist(const Orderlist& ol) {
		ptr = new vector<Order*> (*ol.ptr);
	}
	//assignment operator, similary should not be used in this program
	Orderlist& Orderlist::operator = (const Orderlist& o) {
		ptr = o.ptr;
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
	void Orderlist::add(Order* o) {
		cout << "Adding order to list" << endl;
		//this calls the copy constructor
		ptr->push_back(o);
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