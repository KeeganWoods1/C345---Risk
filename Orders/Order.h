#pragma once
#include <iostream>
/*#include "../Player/Player.h"
#include "../Map/map.h"*/
#include "dummy.h"
/*
This is the header file for the orders 
This class has an abstract orderclass and all its children orders [this is so they all fit in the same list]

*/
using namespace std;
class Order {
public:
	//constructor
	Order();
	//constructor with the isnull parameter initilized
	Order(bool b);
	//abstract method for validate
	virtual bool validate() = 0;
	//abstract method for execute
	virtual bool execute() = 0;
	//destructor
	~Order();
	//copy ocnstructor
	Order(const Order&);
	//assignment operator
	Order& operator = (const Order& o);
	//insertion operator
	friend ostream& operator << (ostream& out, const Order& o);
	//getter method
	bool getisnull();
	//print method to add polymorphism to operator <<
	virtual string print()const = 0;
	//setter method
	void setisnull(bool b);
private:
	//variable to tell if an object is null or an actual order 
	//nessecary for now as i cant seem to eliminate entries in the array
	bool isnull;
};
//order for advancing unit (either for attacking or simply moving to allied territory
class Advanceorder : public Order {
public:
	//constructor
	Advanceorder();
	Advanceorder(int i, Player orderp, Territory destt, Territory souret);
	//mehtod to validate if the conditions are met to execute the function
	bool validate();
	//method to execute the order
	bool execute();
	//destructor
	~Advanceorder();
	//sopy constructor
	Advanceorder(const Advanceorder& old);
	//assignment operator
	Advanceorder& operator = (const Advanceorder& o);
	//stream insertion operations
	friend ostream& operator << (ostream& out, const Advanceorder& o);
	//print method to add polymorphism to operator <<
	string print()const;
private:
	// the nubmer of troops to be moved
	int* troopnum;
	//the territory where the troops are moving from
	Territory* sourceterritory;
	//the territory they are being asked to go to
	Territory* destinationterritory;
	//the player that orderd it [important for blockade and making sure they are ordering their own troops]
	Player* orderplayer;

};
//airlift order, drops a set number troops into a owned territory from another non or adjacent territory
class airliftorder : public Order {
public:
	//constructor
	airliftorder(int i, Territory sourcet, Territory destinationt, Player orderp);
	//makes sure the terrtories are both owned by the player and the number of troops doest not leave the territory with <1 troops
	bool validate ();
	//executes the order
	bool execute();
	//destructor
	~airliftorder();
	//copy constructor
	airliftorder(const airliftorder& old);
	//assingmnet operator
	airliftorder& operator = (const airliftorder& old);
	//stream insertion override
	friend ostream& operator << (ostream& out, const airliftorder& o);
	//print method to add polymorphism to operator <<
	string print()const;
private:
	//# of troops to be moved
	int* troopnum;
	//territory where troops are being moved from
	Territory* sourceterritory;
	//territory where the troops are being moved to
	Territory* destinationterritory;
	//the playter who initiated the order
	Player* orderplayer;
	//may also need a pointer to two Territory objects and a player pointer to make sure the player calling the order is the owner of source
};
//triples army count of owned territory but then turns neutral
class Blockadeorder : public Order {
public:
	//constructor
	Blockadeorder(Player orderplayer, Territory destt);
	//makes sure the territory is owned by the player
	bool validate();
	//executes the order
	bool execute();
	//destructor
	~Blockadeorder();
	//copy constructor
	Blockadeorder(const Blockadeorder& old);
	//assignment operator
	Blockadeorder& operator = (const Blockadeorder& old);
	//insertion operators
	friend ostream& operator << (ostream& out, const Blockadeorder& o);
	//print method to add polymorphism to operator <<
	string print()const;
private:
	//player who initiated the order
	Player* orderplayer;
	//territory to be turned neutral
	Territory* destinationterritory;
};
//country losses half its troops
class Bomborder : public Order {
public:
	//constructor
	Bomborder(Player orderp, Territory destt);
	//no real validation, simply halves units rounded down (even if its the players territory)
	bool validate();
	//executes order
	bool execute();
	//destructor
	~Bomborder();
	//copy constructor
	Bomborder(const Bomborder& old);
	//addignment operator
	Bomborder& operator = (const Bomborder& old);
	//insertion operators
	friend ostream& operator << (ostream& out, const Bomborder& o);
	//print method to add polymorphism to operator <<
	string print()const;
private:
	//player who issued the order [may need for console but no validate]
	Player* orderplayer;
	//territory to be bombed
	Territory* destinationterritory;
};
//deploys the set ammount of troops the class has to a territory
//currently cant validate but needs to check the num of available troops
class Deployorder : public Order {
public:
	//constructor
	Deployorder(Player orderp, int troopnum, Territory destt);
	//makes sure the player owns the territory and that the ammount oftroops palced does not exceed the mamount that he has
	bool validate();
	//execute order
	bool execute();
	//destructor
	~Deployorder();
	//copy constructor
	Deployorder(const Deployorder& old);
	//assignment operator
	Deployorder& operator = (const Deployorder& old);
	//insertion operators
	friend ostream& operator << (ostream& out, const Deployorder& o);
	//print method to add polymorphism to operator <<
	string print()const;
private:
	//player who issued the order
	Player* orderplayer;
	//ammount of troops to be placed
	int* troopnum;
	//territory to recieve troops
	Territory* destinationterritory;
};
//prevents battles between two players (will need to be added to some orders or player class)
class Negotiateorder : public Order {
public:
	//constructor
	Negotiateorder(Player orderp, Player destp);
	//makes sure the two players are not the same player
	bool validate();
	//exectues order
	bool execute();
	//destructor
	~Negotiateorder();
	//copy constructor
	Negotiateorder(const Negotiateorder& old);
	//assignment operator
	Negotiateorder& operator = (const Negotiateorder& old);
	//insertion opperators
	friend ostream& operator << (ostream& out, const Negotiateorder& o);
	//print method to add polymorphism to operator <<
	string print()const;
private:
	//player who issued the order
	Player* orderplayer;
	//player to be targeted for negotiation
	Player* otherplayer;

};
//gives the player 5 armies to deploy [needs to be instant and the player needs an ammount of troops]
class Reinforcementorder : public Order {
public:
	//constructor
	Reinforcementorder(Player orderp);
	//no validation required
	bool validate();
	//excecutes order
	bool execute();
	//destructor
	~Reinforcementorder();
	//copy constructor
	Reinforcementorder(const Reinforcementorder& old);
	//assignment operator
	Reinforcementorder& operator = (const Reinforcementorder& old);
	//insertion operator
	friend ostream& operator << (ostream& out, const Reinforcementorder& o);
	//print method to add polymorphism to operator <<
	string print()const;
private:
	//player hwo issued the order
	Player* orderplayer;
};