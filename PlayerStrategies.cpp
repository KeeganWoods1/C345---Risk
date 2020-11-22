#include "PlayerStrategies.h"

/*
NOTE
MAJORITY COMMENTS LOCATED IN . DUE TO SIMPLICITY OF .CPP

*/



PlayerStrategy::PlayerStrategy(Player* p) {
	player = p;
}
PlayerStrategy::~PlayerStrategy() {
	player = NULL;
}
PlayerStrategy::PlayerStrategy(const PlayerStrategy& h) {
	player = h.player;
}
PlayerStrategy &PlayerStrategy:: operator = (const PlayerStrategy& h) {
	player = h.player;
	return *this;
}
ostream& operator << (ostream& out,  PlayerStrategy& o) {
	Player* p;
	p = o.player;
	cout << "this is a player strategy abstract class." + p->getName();
	return out;
}
Player* PlayerStrategy::getPlayer() { return player; }

string PlayerStrategy::getPlayerName() {
	return player->getName();
}

void HumanPlayerStrategy::issueorder(Map* m, vector<Player*>* pl) {

}

HumanPlayerStrategy::HumanPlayerStrategy(Player* P) : PlayerStrategy{ P }
	{}

HumanPlayerStrategy::~HumanPlayerStrategy() {}
HumanPlayerStrategy::HumanPlayerStrategy(const HumanPlayerStrategy& h) :  PlayerStrategy{ h } {}
HumanPlayerStrategy& HumanPlayerStrategy:: operator = (const HumanPlayerStrategy& h)  { 
	PlayerStrategy::operator=(h);
	return *this; 
}

ostream& operator << (ostream& out,  HumanPlayerStrategy& h)
{
	string p;
	p = h.PlayerStrategy::getPlayerName();
	out << "this is a Human player strategy for player : " + p;
	return out;
}
void AggressivePlayerStrategy::issueorder(Map* m, vector<Player*>* pl) {

}

AggressivePlayerStrategy::AggressivePlayerStrategy(Player* P) : PlayerStrategy{ P } {
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
	out << "this is a Human player strategy for player : " + h.getPlayerName();
	return out;
}
void BenevolentPlayerStrategy::issueorder(Map* m, vector<Player*>* pl) {
}

BenevolentPlayerStrategy::BenevolentPlayerStrategy(Player* P) : PlayerStrategy{ P } {}

BenevolentPlayerStrategy::~BenevolentPlayerStrategy() {}
BenevolentPlayerStrategy::BenevolentPlayerStrategy(const BenevolentPlayerStrategy& h) : PlayerStrategy{ h } {}
BenevolentPlayerStrategy& BenevolentPlayerStrategy:: operator = (const BenevolentPlayerStrategy& h) {
	PlayerStrategy::operator=(h);
	return *this;
}

ostream& operator << (ostream& out,  BenevolentPlayerStrategy& h)
{
	out << "this is a Human player strategy for player : " + h.getPlayerName();
	return out;
}
void NeutralPlayerStrategy::issueorder(Map* m, vector<Player*>* pl) {
}

NeutralPlayerStrategy::NeutralPlayerStrategy(Player* P) : PlayerStrategy{ P } {}

NeutralPlayerStrategy::~NeutralPlayerStrategy() {}
NeutralPlayerStrategy::NeutralPlayerStrategy(const NeutralPlayerStrategy& h) : PlayerStrategy{ h } {}
NeutralPlayerStrategy& NeutralPlayerStrategy:: operator = (const NeutralPlayerStrategy& h) {
	PlayerStrategy::operator=(h);
	return *this;
}

ostream& operator << (ostream& out,  NeutralPlayerStrategy& h)


{
	out << "this is a Human player strategy for player : " + h.getPlayerName();
	return out;
}

void Context::issueOrder(Map* m, vector<Player*>* pl) {
	ps->issueorder(m, pl);
}
Context::Context(PlayerStrategy* playerstrat) {
	ps = playerstrat;
}
Context::~Context() {
	delete ps;
}

Context::Context(const Context& c) {
	ps = new PlayerStrategy(*c.ps);
}
Context& Context:: operator = (const Context& c) {
	ps = c.ps;
	return *this;
}
ostream& operator << (ostream& out, Context& o) {
	out << "this is the a context";
	return out;
}
string Context::getPlayerName() {
	return ps->getPlayerName();
}