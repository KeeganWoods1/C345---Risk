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

void HumanPlayerStrategy::issueorder(Map* m, vector<Player*>* pl, Player* curplayer, Deck* deckpointer) {

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
void AggressivePlayerStrategy::issueorder(Map* m, vector<Player*>* pl, Player* curplayer, Deck* deckpointer) {
    if (curplayer->toDefend(*m)->size() > 1) {
        int* reinforcementCounter = DBG_NEW int(curplayer->getCurrentReinforcements());
        Territory* t = curplayer->toDefend(*m)->at(0);
        curplayer->addOrder(new Deployorder(curplayer, reinforcementCounter, t));
        Territory* defend = toDefend(m, curplayer)->at(0);
        Territory* attack = toAttack(m, curplayer, defend)->at(0);
        for (int i = 1; i < curplayer->gettoDefend(*m)->size(); i++) {
            if (curplayer->gettoDefend(*m)->at(i)->getterritory_armycount() > 1 && m->isAdjacent(defend, curplayer->gettoDefend(*m)->at(i))) {
                int* attacknum2 = new int(curplayer->gettoDefend(*m)->at(i)->getterritory_armycount() - 1);
                curplayer->addOrder(new Advanceorder(attacknum2, curplayer, defend, curplayer->gettoDefend(*m)->at(i), m));
            }
        }
        int* attacknum = new int(*reinforcementCounter + t->getterritory_armycount() - 2);
        curplayer->addOrder(new Advanceorder(attacknum, curplayer, attack, defend, m));
    }
    vector<Card*> cards = curplayer->getHand()->getHandContainer();
    for (int i = 0; i < cards.size(); i++) {
        Card* card = cards.at(i);
            if (card->getName() == "Blockade Card" && curplayer->gettoDefend(*m)->size() > 0)
            {
                // the play method adds the order to the player's orderlist
                dynamic_cast<BlockadeCard*>(card)->play(deckpointer, curplayer, curplayer->toDefend(*m)->at(0));
            }
            else if ((card->getName()) == "Bomb Card" && curplayer->toAttack(*m)->size() > 0) {
                Territory* attack = curplayer->toAttack(*m)->at(0);
                // the play method adds the order to the player's orderlist
                dynamic_cast<BombCard*>(card)->play(deckpointer, curplayer, attack);
            }
            else if (card->getName() == "Reinforcement Card")
            {
                // the play method adds the order to the player's orderlist
                dynamic_cast<ReinforcementCard*>(card)->play(deckpointer, curplayer);
            }
            else if (card->getName() == "Airlift Card" && curplayer->gettoDefend(*m)->size() > 1)
            {
                // the play method adds the order to the player's orderlist
                int i = curplayer->gettoDefend(*m)->size() - 1;
                if (i >= 1) dynamic_cast<AirliftCard*>(card)->play(deckpointer, curplayer, curplayer->gettoDefend(*m)->at(i), curplayer->gettoDefend(*m)->at(0), DBG_NEW int(curplayer->gettoDefend(*m)->at(i)->getterritory_armycount() - 1));
            }
            
    }
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
vector<Territory*>* AggressivePlayerStrategy::toAttack(Map* m, Player* p) {
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
vector<Territory*>* AggressivePlayerStrategy::toDefend(Map* m, Player* p) {
    vector<Territory*>* territoriesToDefend = p->gettoDefend(*m);
    vector<Territory*>* terr2 = DBG_NEW vector<Territory*>;
    for (int j = 0; j < territoriesToDefend->size(); j++) {
        Territory t = territoriesToDefend->at(j);
        vector<Territory*>* terr = p->surroundingterritories(*m, t);
        for (int i = 0; i < terr->size(); i++) {
            if (terr->at(i)->getterritory_owner()->getName().compare(t.getterritory_owner()->getName()) != 0) {
                terr2->push_back(territoriesToDefend->at(j));
                break;
            }
        }
        terr->clear();
        delete terr;
    }
    vector<Territory*>* terr = DBG_NEW vector<Territory*>();
    int initialsize = terr2->size();
    for (int k = 0; k < initialsize; k++) {
        int max = -100000;
        int index = -1;
        for (int i = 0; i < terr2->size(); i++) {
            if (terr2->at(i)->getterritory_armycount() > max) {
                max = terr2->at(i)->getterritory_armycount();
                index = i;
            }
        }
        terr->push_back(terr2->at(index));
        terr2->erase(terr2->cbegin() + index);

    }
    terr2->clear();
    delete terr2;
    vector<Territory*>* surroundingterr = p->getSurroundingterr();
    surroundingterr->clear();
    for (int i = 0; i < terr->size(); i++) {
        surroundingterr->push_back(terr->at(i));
    }
    terr->clear();
    delete terr;
    return  surroundingterr;
}
void BenevolentPlayerStrategy::issueorder(Map* m, vector<Player*>* pl, Player* curplayer, Deck* deckpointer) {
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
void NeutralPlayerStrategy::issueorder(Map* m, vector<Player*>* pl, Player* curplayer, Deck* deckpointer) {
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
