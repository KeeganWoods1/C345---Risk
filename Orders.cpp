#include "Orders.h"
#include <iostream>
#ifdef _DEBUG
#define DBG_NEW new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
// Replace _NORMAL_BLOCK with _CLIENT_BLOCK if you want the
// allocations to be of _CLIENT_BLOCK type
#else
#define DBG_NEW new
#endif
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
	Advanceorder::Advanceorder(int* i, Player* orderp, Territory* destt, Territory* souret, Map *m): Order(true) {
		troopnum = i;
		orderplayer = orderp;
		destinationterritory = destt;
		sourceterritory = souret;
		map = m;
		msg = "Advance order by " + orderplayer->getName() + " to move " + to_string(*troopnum) + " armies from " + sourceterritory->getterritory_name() + " to " + destinationterritory->getterritory_name();
	}
	Map* Advanceorder::getMap()
	{
		return map;
	}
	bool Advanceorder::validate() {
		if (sourceterritory->getterritory_owner()->getName().compare(orderplayer->getName())!=0)
		{
			return false;
		}
        if (sourceterritory->getterritory_armycount()- *troopnum < 1)
		{
			return false;
		}
        if (orderplayer->getName().compare(destinationterritory->getterritory_owner()->getName()) != 0)
		{

			if (orderplayer->isNegotiatedFriend(destinationterritory->getterritory_owner()->getName()))
			{
				return false;
			}
		}
		bool b = map->isAdjacent(sourceterritory, destinationterritory);
		if (!b) {
			return (b);
		}
		else return b;
	}
	//returns true if attacker wins the territory (Important for notifying observers of changes in territory owners)
	bool Advanceorder::execute() 
	{
		if (validate()) 
		{
			if (sourceterritory->getterritory_owner()->getName().compare(destinationterritory->getterritory_owner()->getName())==0)
			{
			    sourceterritory->setterritory_armycount(sourceterritory->getterritory_armycount()-*troopnum);
                destinationterritory->setterritory_armycount(destinationterritory->getterritory_armycount()+*troopnum);
				msg = "moving " + to_string(*troopnum) + " units from " + sourceterritory->getterritory_name() + " to " + destinationterritory->getterritory_name() + " resulting in a new total of " + to_string(destinationterritory->getterritory_armycount()) + " units\n";
				cout << msg;
                return true;
			}
			else 
			{
				int totalattackerDestroyed = 0;
				int totaldefenderDestroyed = 0;
				while (*troopnum > 0 && destinationterritory->getterritory_armycount() > 0){
					int attackerDestroyed = 0;
					int defenderDestroyed = 0;
					for (int i=0; i<*troopnum; i++){
						if (rand() %100 >= 59)defenderDestroyed++;
					}
					for (int i=0; i<destinationterritory->getterritory_armycount(); i++){
						if (rand() %100 >= 69)attackerDestroyed++;
					}
					*troopnum = *troopnum- attackerDestroyed;
					destinationterritory->setterritory_armycount(destinationterritory->getterritory_armycount()-defenderDestroyed);
					totalattackerDestroyed+= attackerDestroyed;
					totaldefenderDestroyed+=defenderDestroyed;
				}
				if (*troopnum < 1)
				{
					msg = "Attack failed " + orderplayer->getName() + " defeated by the " + destinationterritory->getterritory_owner()->getName() + "\n";
					cout << msg;

					//attack unsuccessful
					return false;
				}
				else 
				{
					//attacker wins the battle
					msg = "Attack won " + orderplayer->getName() + " conquers the " + destinationterritory->getterritory_owner()->getName() +"\n";
					cout << msg;
					destinationterritory->setterritory_armycount(*troopnum);
					if (destinationterritory->getterritory_owner()->getName().compare("Neutral") == 0)
					{
						delete destinationterritory->getterritory_owner();
					}
					destinationterritory->setterritory_owner(orderplayer);
					orderplayer->setcaptureTerritory(true);
					return true;
				}
            }
		}
		return false;
	};
	Advanceorder::~Advanceorder() {
		delete troopnum;
	    map = NULL;
	}
	string Advanceorder::print()const {
		return msg;
        }
	Advanceorder::Advanceorder(const Advanceorder& old) {
		troopnum = DBG_NEW int(*old.troopnum);
		sourceterritory = DBG_NEW Territory(*old.sourceterritory);
		destinationterritory = DBG_NEW Territory(*old.destinationterritory);
		orderplayer = DBG_NEW Player(*old.orderplayer);
		msg = old.msg;
	}
	Advanceorder& Advanceorder::operator = (const Advanceorder& old) {
		cout <<"that is called\n";
		troopnum = old.troopnum;
		sourceterritory = old.sourceterritory;
		destinationterritory = old.destinationterritory;
		orderplayer = old.orderplayer;
		msg = old.msg;
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
		msg = "Airlift order by " + orderplayer->getName() + " and is " + to_string(*troopnum) + " troops being Airlifted to " + destinationterritory->getterritory_name() + " from " + sourceterritory->getterritory_name();
	}
	bool Airliftorder::validate() {

		if (*troopnum < 1 || sourceterritory->getterritory_armycount()- *troopnum < 1)return false;
		if (sourceterritory->getterritory_owner()->getName().compare(orderplayer->getName())!=0)return false;
        if (destinationterritory->getterritory_owner()->getName().compare(orderplayer->getName())!=0)return false;
		return true;
	}
	bool Airliftorder::execute() {
		if (validate()) {
			sourceterritory->setterritory_armycount(sourceterritory->getterritory_armycount()-*troopnum);
			destinationterritory->setterritory_armycount(destinationterritory->getterritory_armycount()+*troopnum);
			msg = "airlifted " + to_string(*troopnum) + " units to " + destinationterritory->getterritory_name() + " from " + sourceterritory->getterritory_name() + " for a new total of " + to_string(destinationterritory->getterritory_armycount()) + "units\n";
			cout << msg;
			return true;
		}
		else return false;
	}
	Airliftorder::~Airliftorder() {
		delete troopnum;
	}
	Airliftorder::Airliftorder(const Airliftorder& old) {
		troopnum = DBG_NEW int(*old.troopnum);
		sourceterritory = DBG_NEW Territory(*old.sourceterritory);
		destinationterritory = DBG_NEW Territory(*old.destinationterritory);
		orderplayer = DBG_NEW Player(* old.orderplayer);
		msg = old.msg;
	}
	Airliftorder& Airliftorder::operator = (const Airliftorder& old) {
		troopnum = old.troopnum;
		sourceterritory = old.sourceterritory;
		destinationterritory = old.destinationterritory;
		orderplayer = old.orderplayer;
		msg = old.msg;
		return *this;
	}
	ostream& operator << (ostream& out, Airliftorder& o) {
		out << o.print();
		return out;
	}
	string Airliftorder::print() const{
		return msg;

	}
	string Blockadeorder::print()const {
		return msg;
	}
	Blockadeorder::Blockadeorder(Player* orderp, Territory* destt) {
		orderplayer = orderp;
		destinationterritory = destt;
		msg = "Blockade order from " + orderplayer->getName() + ", to blockade territory " + destinationterritory->getterritory_name();
	}
	bool Blockadeorder::validate() {
	    if (destinationterritory->getterritory_owner()->getName().compare(orderplayer->getName())!=0)return false;
		return true;
	}
	bool Blockadeorder::execute() {
		if (validate()) {
			destinationterritory->setterritory_owner(DBG_NEW Player("Neutral"));
			destinationterritory->setterritory_armycount(destinationterritory->getterritory_armycount() * 2);
			msg = "setting territory " + destinationterritory->getterritory_name() + " to neutral with a new army count of " + to_string(destinationterritory->getterritory_armycount()) + "units\n";
			cout << msg;
			return true;
		}
		else return false;
	}
	Blockadeorder::~Blockadeorder() {
	}
	Blockadeorder::Blockadeorder(const Blockadeorder& old) {
		orderplayer = DBG_NEW Player(*old.orderplayer);
		destinationterritory = DBG_NEW Territory(*old.destinationterritory);
		msg = old.msg;
	}
	Blockadeorder& Blockadeorder::operator = (const Blockadeorder& old) {
		orderplayer = old.orderplayer;
		destinationterritory = old.destinationterritory;
		msg = old.msg;
		return *this;
	}
	ostream& operator << (ostream& out, const Blockadeorder& o) {
		out << o.print();
		return out;
	}
	string Bomborder::print() const {
		return msg;
	}
	Bomborder::Bomborder(Player* orderp, Territory* destt) {
		orderplayer = orderp;
		destinationterritory = destt;
		msg = "bomb order from " + orderplayer->getName() + " on country " + destinationterritory->getterritory_name();
	}
	bool Bomborder::validate() {
	    if (destinationterritory->getterritory_owner()->getName().compare(orderplayer->getName())==0)return false;
		return true;
	}
	bool Bomborder::execute() {
		if (validate()) {
			destinationterritory->setterritory_armycount(destinationterritory->getterritory_armycount()/2);
			msg = "bombed " + destinationterritory->getterritory_name() + " making the new count " + to_string(destinationterritory->getterritory_armycount()) + " units\n";
			cout << msg;
			return true;
		}
		else return false;
	}
	Bomborder::~Bomborder() {
		if(orderplayer == NULL) {cout << "OrderPlayer is null" << endl;}
		if(destinationterritory == NULL) {cout << "destinationterritory is null" << endl;}
	}
	Bomborder::Bomborder(const Bomborder& old) {
		orderplayer = DBG_NEW Player(*old.orderplayer);
		destinationterritory = DBG_NEW Territory(*old.destinationterritory);
		msg = old.msg;
	}
	Bomborder& Bomborder::operator = (const Bomborder& old) {
		orderplayer = old.orderplayer;
		destinationterritory = old.destinationterritory;
		msg = old.msg;
		return *this;

	}
	ostream& operator << (ostream& out, const Bomborder& o) {
		out << o.print();
		return out;

	}
	string Deployorder::print() const {
		return msg;
	}
	Deployorder::Deployorder(Player* orderp, int* j, Territory* destt) {
		orderplayer = orderp;
		troopnum = j;
		destinationterritory = destt;
		msg = "Deploy order from " + orderplayer->getName() + " to deploy " + to_string(*troopnum) + " troops to " + destinationterritory->getterritory_name() + "\n";
	}
	bool Deployorder::validate() {
        if (orderplayer->getCurrentReinforcements()< *troopnum)return false;
        if (destinationterritory->getterritory_owner()->getName().compare(orderplayer->getName())!=0)return false;
		return true;
	}
	bool Deployorder::execute() {
		if (validate()) {
			destinationterritory->setterritory_armycount(destinationterritory->getterritory_armycount()+*troopnum);
			orderplayer->setCurrentReinforcements(orderplayer->getCurrentReinforcements()-*troopnum);
			msg = "moved " + to_string(*troopnum) + " units to " + destinationterritory->getterritory_name() + " for a total of " + to_string(destinationterritory->getterritory_armycount()) + " units\n";
			cout << msg;
			return true;
		}
		else return false;
	}
	Deployorder::~Deployorder() {
		delete troopnum;
	}
	Deployorder::Deployorder(const Deployorder& old) {
		troopnum = DBG_NEW int(*old.troopnum);
		orderplayer = DBG_NEW Player(*old.orderplayer);
		destinationterritory = DBG_NEW Territory(*old.destinationterritory);
		msg = old.msg;
	}
	Deployorder& Deployorder::operator = (const Deployorder& old) {
		troopnum = old.troopnum;
		orderplayer = old.orderplayer;
		destinationterritory = old.destinationterritory;
		msg = old.msg;
		return *this;
	}
	ostream& operator << (ostream& out, const Deployorder& o) {
		out << o.print();
		return out;

	}
	string Negotiateorder::print() const {
		return msg;
	}
	Negotiateorder::Negotiateorder(Player* orderp, Player* destp) {
		orderplayer = orderp;
		otherplayer = destp;
		msg = "Negotiate order from " + orderplayer->getName() + " to " + otherplayer->getName();
	}
	bool Negotiateorder::validate() {
	    if (orderplayer->getName().compare(otherplayer->getName())==0)return false;
		return true;
	}
	bool Negotiateorder::execute() {
		if (validate()) {
			orderplayer->addnegotiateFriends(otherplayer->getName());
			otherplayer->addnegotiateFriends(orderplayer->getName());
			msg = "a truce was brokered between " +orderplayer->getName() + " and " +otherplayer->getName() +"\n";
			return true;
		}
		else return false;
	}
	Negotiateorder::~Negotiateorder() {
	}
	Negotiateorder::Negotiateorder(const Negotiateorder& old) {
		orderplayer = DBG_NEW Player(*old.orderplayer);
		otherplayer = DBG_NEW Player(*old.otherplayer);
		msg = old.msg;
	}
	Negotiateorder& Negotiateorder::operator = (const Negotiateorder& old) {
		orderplayer = old.orderplayer;
		otherplayer = old.otherplayer;
		msg = old.msg;
		return *this;
	}
	ostream& operator << (ostream& out, const Negotiateorder& o) {
		out << o.print();
		return out;
	}
	string Reinforcementorder::print() const {
		return msg;
	}
	Reinforcementorder::Reinforcementorder(Player* orderp) {
		orderplayer = orderp;
		msg = "Reinforcement order from " + orderplayer->getName() + " to reinforce their army with 5 troops";
	}
	bool Reinforcementorder::validate() {
		return true;
	}
	bool Reinforcementorder::execute() {
		if (validate()) {
			orderplayer->addReinforcements(5);
			msg = "adding 5 reinfrocements to the pool of player " + orderplayer->getName();
			cout << msg;
			return true;
		}
		else return false;
	}
	Reinforcementorder::~Reinforcementorder() {

	}
	Reinforcementorder::Reinforcementorder(const Reinforcementorder& old) {
		orderplayer = DBG_NEW Player(*old.orderplayer);
		msg = old.msg;
	}
	Reinforcementorder& Reinforcementorder::operator = (const Reinforcementorder& old) {
		orderplayer = old.orderplayer;
		msg = old.msg;
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
		ptr = DBG_NEW vector<Order*>();
	}
	//destructor for orderlist
	Orderlist::~Orderlist() {
		if (ptr == NULL) return;
		for (int i = 0; i < ptr->size(); i++) {
			delete ptr->at(i);
		}
		delete ptr;
	}
	// copy constructor, should not be used in the context of the program
	Orderlist::Orderlist(const Orderlist& ol) {
		ptr = DBG_NEW vector<Order*> (*ol.ptr);
	}
	//assignment operator, similary should not be used in this program
	Orderlist& Orderlist::operator = (const Orderlist& o) {


		ptr = o.ptr;
		return *this;
	}
	//stream output operator, will need to be used in driver but not in the program
	
	ostream& operator << (ostream& stream, Orderlist& o) {
		
		for (int i = 0; i < o.ptr->size(); i++) {
			stream << *o.ptr->at(i);
			stream << "\n";
		}
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
		//this calls the copy constructor
		ptr->push_back(o);
	}

	//executes orders and then deletes them all
	void Orderlist::executelist() {
		cout << "\n";
		while(!ptr->empty()) {
			ptr->at(0)->execute();
            remove(0);
		}
		delete this;
	}

vector<Order*>* Orderlist::retirevelist(){return ptr;}
