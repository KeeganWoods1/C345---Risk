#pragma once
#include <iostream>
using namespace std;
class Player {
public:
	Player(string n);
	string getName();
	Player(const Player& old);
private:
	string name;

};

class Territory {
public:
	Territory(string n);
	string getTerritoryName();
	Territory(const Territory& old);
private:
	string name;
};