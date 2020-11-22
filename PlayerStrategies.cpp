#include "PlayerStrategies.h"

/*
NOTE
MAJORITY COMMENTS LOCATED IN . DUE TO SIMPLICITY OF .CPP

*/

#ifdef _DEBUG
#define DBG_NEW new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
// Replace _NORMAL_BLOCK with _CLIENT_BLOCK if you want the
// allocations to be of _CLIENT_BLOCK type
#else
#define DBG_NEW new
#endif

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
    vector<Territory*>* territoriesToDefend = p->gettoDefend(*m);
    vector<Territory*>* territoriesToAttack = p->getterritoriesToAttack();
    territoriesToAttack->clear();
    vector<Territory*>* terr = p->surroundingterritories(*m, *t);
    vector<Territory*>* terr2 = DBG_NEW vector<Territory*>;
    for (int i = 0; i < terr->size(); i++) {
        if (terr->at(i)->getterritory_owner()->getName().compare(t->getterritory_owner()->getName()) != 0)terr2->push_back(terr->at(i));
    }
    terr->clear();
    delete terr;
    terr = DBG_NEW vector<Territory*>();
    int initialsize = terr2->size();
    for (int k = 0; k < initialsize; k++) {
        int min = 100000;
        int index = -1;
        for (int i = 0; i < terr2->size(); i++) {
            if (terr2->at(i)->getterritory_armycount() < min) {
                min = terr2->at(i)->getterritory_armycount();
                index = i;
            }
        }
        if (index == -1)cout << "error here";
        terr->push_back(terr2->at(index));
        terr2->erase(terr2->cbegin() + index);

    }
    terr2->clear();
    delete terr2;
    for (int i = 0; i < terr->size(); i++) {
        territoriesToAttack->push_back(terr->at(i));
    }
    terr->clear();
    delete terr;
    return  territoriesToAttack;
}
vector<Territory*>* NeutralPlayerStrategy::toAttack(Map* m, Player* p) {
    vector<Territory*>* territoriesToDefend = p->gettoDefend(*m);
    vector<Territory*>* territoriesToAttack = p->getterritoriesToAttack();
    territoriesToAttack->clear();
    vector<Territory*>* result = DBG_NEW vector<Territory*>();
    for (int i = 0; i < territoriesToDefend->size(); i++) {
        vector<Territory*>* terr = p->surroundingterritories(*m, *territoriesToDefend->at(i));
        for (int j = 0; j < terr->size(); j++) {
            if (terr->at(j)->getterritory_owner()->getName().compare(territoriesToDefend->at(i)->getterritory_owner()->getName()) != 0) {
                bool exists = false;
                for (int k = 0; k < result->size(); k++) {
                    if (terr->at(j)->getterritory_name().compare(result->at(k)->getterritory_name()) == 0)exists = true;
                }
                if (!exists) {
                    result->push_back(terr->at(j));
                    break;
                }
            }
        }
        terr->clear();
        delete terr;
    }
    for (int k = 0; k < result->size(); k++) {
        int max = -1;
        int index = -1;
        int i = k;
        for (; i < result->size(); i++) {
            if (result->at(i)->getterritory_armycount() > max) {
                max = result->at(i)->getterritory_armycount();
                index = i;
            }
        }
        if (index != k) {
            iter_swap(result->begin() + index, result->begin() + k);
        }
    }
    for (int i = 0; i < result->size(); i++) {
        territoriesToAttack->push_back(result->at(i));
    }
    result->clear();
    delete result;
    return territoriesToAttack;
}
vector<Territory*>* NeutralPlayerStrategy::toDefend(Map* m, Player* p) {
	return p->gettoDefend(*m);
}
