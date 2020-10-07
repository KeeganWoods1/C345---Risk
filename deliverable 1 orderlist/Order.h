#pragma once
#include <iostream>
#include "../Player/Player.h"
#include "../Map/map.h"
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
	virtual bool validate();
	//abstract method for execute
	virtual bool execute();
	//destructor
	~Order();
	//copy ocnstructor
	Order(const Order&);
	//assignment operator
	Order& operator = (const Order& o);
	//insertion operator
	friend istream &operator >> (istream& stream, Order& o);
	friend ostream& operator << (ostream& out, const Order& o);
	//getter method
	bool getisnull();
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
	Advanceorder(int i, Player orderp, Territory destt, Territory souret);
	//mehtod to validate if the conditions are met to execute the function
	bool validate();
	//method to execute the order
	bool execute();
	//destructor
	~Advanceorder();
	//sopy constructor
	Advanceorder(const Advanceorder&);
	//assignment operator
	Advanceorder& operator = (const Advanceorder& o);
	//stream insertion operations
	friend istream& operator >> (istream& stream, Advanceorder& o);
	friend ostream& operator << (ostream& out, const Advanceorder& o);
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
	airliftorder(int i, Territory sourceterritory, Territory destinationterritory, Player orderplayer);
	//makes sure the terrtories are both owned by the player and the number of troops doest not leave the territory with <1 troops
	bool validate();
	//executes the order
	bool execute();
	//destructor
	~airliftorder();
	//copy constructor
	airliftorder(const airliftorder&);
	//assingmnet operator
	airliftorder& operator = (const airliftorder& o);
	//stream insertion override
	friend istream& operator >> (istream& stream, airliftorder& o);
	friend ostream& operator << (ostream& out, const airliftorder& o);
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
	//constructor
	Blockadeorder(Player orderplayer, Territory destt);
	//makes sure the territory is owned by the player
	bool validate();
	//executes the order
	bool execute();
	//destructor
	~Blockadeorder();
	//copy constructor
	Blockadeorder(const Blockadeorder&);
	//assignment operator
	Blockadeorder& operator = (const Blockadeorder& o);
	//insertion operators
	friend istream& operator >> (istream& stream, Blockadeorder& o);
	friend ostream& operator << (ostream& out, const Blockadeorder& o);
private:
	//player who initiated the order
	Player* orderplayer;
	//territory to be turned neutral
	Territory* destinationterritory;
};
//country losses half its troops
class Bomborder : public Order {
	//constructor
	Bomborder(Player orderp, Territory destt);
	//no real validation, simply halves units rounded down (even if its the players territory)
	bool validate();
	//executes order
	bool execute();
	//destructor
	~Bomborder();
	//copy constructor
	Bomborder(const Bomborder&);
	//addignment operator
	Bomborder& operator = (const Bomborder& o);
	//insertion operators
	friend istream& operator >> (istream& stream, Bomborder& o);
	friend ostream& operator << (ostream& out, const Bomborder& o);
private:
	//player who issued the order [may need for console but no validate]
	Player* orderplayer;
	//territory to be bombed
	Territory* destinationterritory;
};
//deploys the set ammount of troops the class has to a territory
//currently cant validate but needs to check the num of available troops
class Deployorder : public Order {
	//constructor
	Deployorder(Player orderp, int troopnum, Territory destinationterritory);
	//makes sure the player owns the territory and that the ammount oftroops palced does not exceed the mamount that he has
	bool validate();
	//execute order
	bool execute();
	//destructor
	~Deployorder();
	//copy constructor
	Deployorder(const Deployorder&);
	//assignment operator
	Deployorder& operator = (const Deployorder& o);
	//insertion operators
	friend istream& operator >> (istream& stream, Deployorder& o);
	friend ostream& operator << (ostream& out, const Deployorder& o);
private:
	//player who issued the order
	Player* orderplayer;
	//ammount of troops to be placed
	int* troopnum;
	//territory to recieve troops
	Territory destinationterritory;
};
//prevents battles between two players (will need to be added to some orders or player class)
class Negotiateorder : public Order {
	//constructor
	Negotiateorder(Player orderp, Player destp);
	//makes sure the two players are not the same player
	bool validate();
	//exectues order
	bool execute();
	//destructor
	~Negotiateorder();
	//copy constructor
	Negotiateorder(const Negotiateorder&);
	//assignment operator
	Negotiateorder& operator = (const Negotiateorder& o);
	//insertion opperators
	friend istream& operator >> (istream& stream, Negotiateorder& o);
	friend ostream& operator << (ostream& out, const Negotiateorder& o);
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
	Reinforcementorder(const Reinforcementorder&);
	//assignment operator
	Reinforcementorder& operator = (const Reinforcementorder& o);
	//insertion operator
	friend istream& operator >> (istream& stream, Reinforcementorder& o);
	friend ostream& operator << (ostream& out, const Reinforcementorder& o);
private:
	//player hwo issued the order
	Player* orderplayer;
};
