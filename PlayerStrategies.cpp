#include "PlayerStrategies.h"

/*
NOTE
MAJORITY COMMENTS LOCATED IN . DUE TO SIMPLICITY OF .CPP

*/



PlayerStrategy::PlayerStrategy() {
}
PlayerStrategy::~PlayerStrategy() {
}
PlayerStrategy::PlayerStrategy(const PlayerStrategy& h) {
}
PlayerStrategy &PlayerStrategy:: operator = (const PlayerStrategy& h) {
	return *this;
}
ostream& operator << (ostream& out,  PlayerStrategy& o) {

	cout << "this is a player strategy abstract class.";
	return out;
}
vector<Territory*>* PlayerStrategy::toAttack(Map* m, Player* p, Territory* t) { return NULL; }
vector<Territory*>* PlayerStrategy::toAttack(Map* m, Player* p){ return NULL; }
vector<Territory*>* PlayerStrategy::toDefend(Map* m, Player* p){ return NULL; }

void HumanPlayerStrategy::issueorder(Map* m, vector<Player*>* pl, Player* curplayer) {

}

HumanPlayerStrategy::HumanPlayerStrategy(){}
HumanPlayerStrategy::~HumanPlayerStrategy() {}
HumanPlayerStrategy::HumanPlayerStrategy(const HumanPlayerStrategy& h) :  PlayerStrategy{ h } {}
HumanPlayerStrategy& HumanPlayerStrategy:: operator = (const HumanPlayerStrategy& h)  { 
	PlayerStrategy::operator=(h);
	return *this; 
}

ostream& operator << (ostream& out,  HumanPlayerStrategy& h)
{
	out << "this is a Human player strategy";
	return out;
}
vector<Territory*>* HumanPlayerStrategy::toAttack(Map* m, Player* p, Territory* t) {
	return NULL;
}
vector<Territory*>* HumanPlayerStrategy::toAttack(Map* m, Player* p) {
	return NULL;
}
vector<Territory*>* HumanPlayerStrategy::toDefend(Map* m, Player* p) {
	return NULL;
}
void AggressivePlayerStrategy::issueorder(Map* m, vector<Player*>* pl, Player* curplayer) {

}

AggressivePlayerStrategy::AggressivePlayerStrategy() {
}

AggressivePlayerStrategy::~AggressivePlayerStrategy() {}
AggressivePlayerStrategy::AggressivePlayerStrategy(const AggressivePlayerStrategy& h) : PlayerStrategy{ h } {
}
AggressivePlayerStrategy& AggressivePlayerStrategy:: operator = (const AggressivePlayerStrategy& h)  {
	PlayerStrategy::operator=(h);
	return *this;
}

ostream& operator << (ostream& out,  AggressivePlayerStrategy& h)
{
	out << "this is a Human player strategy";
	return out;
}
vector<Territory*>* AggressivePlayerStrategy::toAttack(Map* m, Player* p, Territory* t) {
	return NULL;
}
vector<Territory*>* AggressivePlayerStrategy::toAttack(Map* m, Player* p) {
	return NULL;
}
vector<Territory*>* AggressivePlayerStrategy::toDefend(Map* m, Player* p) {
	return NULL;
}
void BenevolentPlayerStrategy::issueorder(Map* m, vector<Player*>* pl, Player* curplayer) {
}

BenevolentPlayerStrategy::BenevolentPlayerStrategy() {}

BenevolentPlayerStrategy::~BenevolentPlayerStrategy() {}
BenevolentPlayerStrategy::BenevolentPlayerStrategy(const BenevolentPlayerStrategy& h) : PlayerStrategy{ h } {}
BenevolentPlayerStrategy& BenevolentPlayerStrategy:: operator = (const BenevolentPlayerStrategy& h) {
	PlayerStrategy::operator=(h);
	return *this;
}

ostream& operator << (ostream& out,  BenevolentPlayerStrategy& h)
{
	out << "this is a Human player strategy";
	return out;
}
vector<Territory*>* BenevolentPlayerStrategy::toAttack(Map* m, Player* p, Territory* t) {
	return NULL;
}
vector<Territory*>* BenevolentPlayerStrategy::toAttack(Map* m, Player* p) {
	return NULL;
}
vector<Territory*>* BenevolentPlayerStrategy::toDefend(Map* m, Player* p) {
	return NULL;
}
void NeutralPlayerStrategy::issueorder(Map* m, vector<Player*>* pl, Player* curplayer) {
}

NeutralPlayerStrategy::NeutralPlayerStrategy(){}

NeutralPlayerStrategy::~NeutralPlayerStrategy() {}
NeutralPlayerStrategy::NeutralPlayerStrategy(const NeutralPlayerStrategy& h) : PlayerStrategy{ h } {}
NeutralPlayerStrategy& NeutralPlayerStrategy:: operator = (const NeutralPlayerStrategy& h) {
	PlayerStrategy::operator=(h);
	return *this;
}

ostream& operator << (ostream& out,  NeutralPlayerStrategy& h)


{
	out << "this is a Human player strategy for player";
	return out;
}
vector<Territory*>* NeutralPlayerStrategy::toAttack(Map* m, Player* p, Territory* t) {
	return NULL;
}
vector<Territory*>* NeutralPlayerStrategy::toAttack(Map* m, Player* p) {
	return NULL;
}
vector<Territory*>* NeutralPlayerStrategy::toDefend(Map* m, Player* p) {
	return NULL;
}
