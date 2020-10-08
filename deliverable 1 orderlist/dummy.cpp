#pragma once
#include <iostream>
#include "dummy.h"
using namespace std;
Player::Player(string n) {
	name = n;
}
string Player::getName() {
	return name;
}
Territory::Territory(string n) {
	name = n;
}
string Territory::getTerritoryName() {
	return name;
}
Player::Player(const Player& old) {
	name = old.name;
}
Territory::Territory(const Territory& old) {
	name = old.name;
}
