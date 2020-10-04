#pragma once
#include <iostream>
using namespace std;
class Order {
public:
	Order();
	virtual bool validate();
	virtual bool execute();
	~Order();
	Order(const Order&);
	Order& operator = (const Order& o);
	friend istream &operator >> (istream& stream, Order& o);
	friend ostream& operator << (ostream& out, const Order& o);
private:
};
class Advanceorder : public Order {
public:
	Advanceorder(int i, int sourceterritory, int destinationterritory, int orderplayer);
	bool validate();
	bool execute();
	~Advanceorder();
	Advanceorder(const Advanceorder&);
	Advanceorder& operator = (const Advanceorder& o);
	friend istream& operator >> (istream& stream, Advanceorder& o);
	friend ostream& operator << (ostream& out, const Advanceorder& o);
private:
	int* troopnum;
	int* sourceterritory;
	int* destinationterritory;
	int* orderplayer;

	//may also need a pointer to two Territory objects and a player pointer to make sure the player calling the order is the owner of source

};
class airliftorder : public Order {
public:
	//will need to add the other pointers to the consturctor and destructor
	airliftorder(int i, int sourceterritory, int destinationterritory, int orderplayer);
	bool validate();
	bool execute();
	~airliftorder();
	airliftorder(const airliftorder&);
	airliftorder& operator = (const airliftorder& o);
	friend istream& operator >> (istream& stream, airliftorder& o);
	friend ostream& operator << (ostream& out, const airliftorder& o);
private:
	int* troopnum;
	int* sourceterritory;
	int* destinationterritory;
	int* orderplayer;
	//may also need a pointer to two Territory objects and a player pointer to make sure the player calling the order is the owner of source
};
class Blockadeorder : public Order {
	Blockadeorder(int i, int j);
	bool validate();
	bool execute();
	~Blockadeorder();
	Blockadeorder(const Blockadeorder&);
	Blockadeorder& operator = (const Blockadeorder& o);
	friend istream& operator >> (istream& stream, Blockadeorder& o);
	friend ostream& operator << (ostream& out, const Blockadeorder& o);
private:
	int* orderplayer;
	int* destinationterritory;
};
class Bomborder : public Order {
	Bomborder(int i, int j);
	bool validate();
	bool execute();
	~Bomborder();
	Bomborder(const Bomborder&);
	Bomborder& operator = (const Bomborder& o);
	friend istream& operator >> (istream& stream, Bomborder& o);
	friend ostream& operator << (ostream& out, const Bomborder& o);
private:
	int* orderplayer;
	int* destinationterritory;
};
class Deployorder : public Order {
	Deployorder(int i, int j);
	bool validate();
	bool execute();
	~Deployorder();
	Deployorder(const Deployorder&);
	Deployorder& operator = (const Deployorder& o);
	friend istream& operator >> (istream& stream, Deployorder& o);
	friend ostream& operator << (ostream& out, const Deployorder& o);
private:
	int* orderplayer;
	int* troopnum;
};
class Negotiateorder : public Order {
	Negotiateorder(int i, int j);
	bool validate();
	bool execute();
	~Negotiateorder();
	Negotiateorder(const Negotiateorder&);
	Negotiateorder& operator = (const Negotiateorder& o);
	friend istream& operator >> (istream& stream, Negotiateorder& o);
	friend ostream& operator << (ostream& out, const Negotiateorder& o);
private:
	int* orderplayer;
	int* otherplayer;

	//may also need a pointer to two Territory objects and a player pointer to make sure the player calling the order is the owner of source
};
class Reinforcementorder : public Order {
public:
	Reinforcementorder(int i);
	bool validate();
	bool execute();
	~Reinforcementorder();
	Reinforcementorder(const Reinforcementorder&);
	Reinforcementorder& operator = (const Reinforcementorder& o);
	friend istream& operator >> (istream& stream, Reinforcementorder& o);
	friend ostream& operator << (ostream& out, const Reinforcementorder& o);
private:
	int* orderplayer;

	//may also need a pointer to two Territory objects and a player pointer to make sure the player calling the order is the owner of source
};
