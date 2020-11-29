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

void HumanPlayerStrategy::issueorder(Map* m, vector<Player*>* pl, Player* curplayer, Deck* deckpointer) 
{
    //Make Switch Case Menu for each order
    int choice;
    bool isDone = false;

    while(!isDone)
    {
        vector<Territory*>* territoriesToDefend;
        
        int troopNum;
        int territory;
        int territoryDest;  
        Territory* sourceTerritory;
        Territory* destTerritory;
        int* n; 
        
        cout << "Issue Orders Menu:" << endl;
        cout << "1. Deploy Order" << endl << "2. Offensive Advance Order" << endl << "3. Defensive Advance Order" 
             << endl << "4. Card" << endl<< "0. End Turn" << endl;
        cin >> choice;
        cout << endl;

        switch(choice)
        {
            case 1:
            {
                territoriesToDefend = toDefend(m, curplayer);
                //Deploy troops                
                cout << "Select a territory to deploy troops to" << endl;
                for(int i=0; i<curplayer->getNumTerrOwned(); i++)
                {
                    cout << i+1 << ". " << *territoriesToDefend->at(i) << endl;
                }
                cin >> territory;
                cin.clear();
                cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                if (territory <= territoriesToDefend->size()) {
                    sourceTerritory = territoriesToDefend->at(territory - 1);

                    cout << "Select number of troops to deploy (" << curplayer->getCurrentReinforcements() << " troops left in pool)" << endl;
                    cin >> troopNum;
                    cin.clear();
                    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

                    n = DBG_NEW int(troopNum);

                    curplayer->addOrder(DBG_NEW Deployorder(curplayer, n, sourceTerritory));
                }
                else cout << "invlid input\n";
                break;
            }
            case 2:
            {      
               territoriesToDefend = toDefend(m, curplayer);
               //Attack Orders
               //Show player's territories
               cout << "Select a territory to attack FROM" << endl;
                for(int i=0; i<curplayer->getNumTerrOwned(); i++)
                {
                    cout << i+1 << ". " << *territoriesToDefend->at(i) << endl;
                }
                //select territory to attack from
                cin >> territory;
                cin.clear();
                cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

                sourceTerritory = territoriesToDefend->at(territory-1);
                 
                //show attackable territories
                cout << "Select a territory to attack" << endl;
                
                vector<Territory*>* territoriesToAttack = toAttack(m, curplayer, sourceTerritory);
                
                for(int i=0; i<territoriesToAttack->size(); i++)
                {
                    cout << i+1 << ". " << *territoriesToAttack->at(i) << endl;
                }

                cin >> territoryDest;
                cin.clear();
                cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                if (territoryDest - 1 < territoriesToAttack->size()) {
                    destTerritory = territoriesToAttack->at(territoryDest - 1);

                    //get number of units to attack with
                    cout << "How many troops would you like to attack with? (" << sourceTerritory->getterritory_armycount() << " troop(s) available)" << endl;
                    cin >> troopNum;
                    cin.clear();
                    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

                    n = DBG_NEW int(troopNum);

                    //issue advance order
                    curplayer->addOrder(DBG_NEW Advanceorder(n, curplayer, destTerritory, sourceTerritory, m));
                }
                else {
                    cout << "invalid input";
                }
                break;           
            }
            case 3:
            {
               territoriesToDefend = toDefend(m, curplayer);
               //Friendly Move Orders
               //Show player's territories
               cout << "Select a territory to move units FROM" << endl;
                for(int i=0; i<curplayer->getNumTerrOwned(); i++)
                {
                    cout << i+1 << ". " << *territoriesToDefend->at(i) << endl;
                }
                //select territory to attack from
                cin >> territory;
                cin.clear();
                cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

                sourceTerritory = territoriesToDefend->at(territory-1);
                 
                //show attackable territories
                cout << "Select a territory to move TO" << endl;
                
                vector<Territory*>* territoriesToMoveTo = curplayer->friendlyAdjacentTerritories(*m, *sourceTerritory);
                
                for(int i=0; i<territoriesToMoveTo->size(); i++)
                {
                    cout << i+1 << ". " << *territoriesToMoveTo->at(i) << endl;
                }

                cin >> territoryDest;
                cin.clear();
                cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

                destTerritory = territoriesToMoveTo->at(territoryDest-1);
                
                //get number of units to move with
                cout << "How many troops would you like to advance with? (" << sourceTerritory->getterritory_armycount() << " troop(s) available)"<< endl;
                cin >> troopNum;
                cin.clear();
                cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                delete territoriesToMoveTo;
                n = DBG_NEW int(troopNum);

                //issue advance order
                curplayer->addOrder(DBG_NEW Advanceorder(n, curplayer, destTerritory, sourceTerritory, m));
                break; 
            }
            case 4:
            {
                territoriesToDefend = toDefend(m, curplayer);
                int cardIdx;
                vector<Card*> cards = curplayer->getHand()->getHandContainer();
               //Cards Orders
                //show hand of cards
                //select a card
                cout << "Select a Card to play" << endl;
                for(int i=0; i<curplayer->getHand()->getHandContainer().size(); i++)
                {
                    cout << i+1 << ". " << *curplayer->getHand()->getHandContainer().at(i) << endl;
                }
                cin >> cardIdx;
                cin.clear();
                cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');  

                //play card
                if (cardIdx  <= cards.size()) {
                    Card* card = cards.at(cardIdx - 1);

                    if (card->getName() == "Blockade Card" && curplayer->gettoDefend(*m)->size() > 0)
                    {
                        territoriesToDefend = toDefend(m, curplayer);
                        cout << "Select the territory you wish to Blockade:" << endl;
                        for (int i = 0; i < territoriesToDefend->size(); i++)
                        {
                            cout << i + 1 << ". " << *territoriesToDefend->at(i) << endl;
                        }
                        cin >> territory;
                        cin.clear();
                        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                        if (territory - 1 < territoriesToDefend->size()) {
                            sourceTerritory = territoriesToDefend->at(territory - 1);
                            // the play method adds the order to the player's orderlist
                            dynamic_cast<BlockadeCard*>(card)->play(deckpointer, curplayer, sourceTerritory);
                        }
                        else cout << "invalid input\n";
                    }
                    else if ((card->getName()) == "Bomb Card" && curplayer->toAttack(*m)->size() > 0) {
                        territoriesToDefend = toDefend(m, curplayer);
                        vector<Territory*>* allHostileTerritories = toAttack(m, curplayer);

                        cout << "Select the territory you wish to Bomb:" << endl;
                        for (int i = 0; i < allHostileTerritories->size(); i++)
                        {
                            cout << i + 1 << ". " << *allHostileTerritories->at(i) << endl;
                        }
                        cin >> territory;
                        cin.clear();
                        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

                        destTerritory = allHostileTerritories->at(territory - 1);

                        // the play method adds the order to the player's orderlist
                        dynamic_cast<BombCard*>(card)->play(deckpointer, curplayer, destTerritory);
                    }
                    else if (card->getName() == "Reinforcement Card")
                    {
                        // the play method adds the order to the player's orderlist
                        dynamic_cast<ReinforcementCard*>(card)->play(deckpointer, curplayer);
                    }
                    else if (card->getName() == "Airlift Card" && curplayer->gettoDefend(*m)->size() > 1)
                    {
                        territoriesToDefend = toDefend(m, curplayer);
                        cout << "Select the territory you wish to Airlift FROM:" << endl;
                        for (int i = 0; i < territoriesToDefend->size(); i++)
                        {
                            cout << i + 1 << ". " << *territoriesToDefend->at(i) << endl;
                        }
                        cin >> territory;
                        cin.clear();
                        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                        if (territory - 1 < territoriesToDefend->size()) {
                            sourceTerritory = territoriesToDefend->at(territory - 1);

                            cout << "Select the territory you wish to Airlift TO:" << endl;
                            cin >> territoryDest;
                            cin.clear();
                            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

                            destTerritory = territoriesToDefend->at(territoryDest - 1);

                            //get number of units to attack with
                            cout << "How many troops would you like to Airlift out? (" << sourceTerritory->getterritory_armycount() << " troop(s) available)" << endl;
                            cin >> troopNum;
                            cin.clear();
                            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

                            n = DBG_NEW int(troopNum);
                            // the play method adds the order to the player's orderlist
                            int i = curplayer->gettoDefend(*m)->size() - 1;
                            if (i >= 1) dynamic_cast<AirliftCard*>(card)->play(deckpointer, curplayer, sourceTerritory, destTerritory, n);
                        }
                        else cout << "invalid input";
                    }
                    else if (card->getName() == "Diplomacy Card")
                    {
                        int enemyPlayerIdx;
                        vector<Player*>* enemyPlayerList = DBG_NEW vector<Player*>();
                        for (int i = 0; i < pl->size(); i++)
                        {
                            if (curplayer->getName().compare(pl->at(i)->getName()) != 0)
                            {
                                enemyPlayerList->push_back(pl->at(i));
                            }
                        }
                        cout << "Which player would you like to negotiate with?" << endl;
                        for (int i = 0; i < enemyPlayerList->size(); i++)
                        {
                            cout << i + 1 << ". " << enemyPlayerList->at(i)->getName() << endl;
                        }
                        cin >> enemyPlayerIdx;
                        cin.clear();
                        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

                        Player* enemyPlayer = enemyPlayerList->at(enemyPlayerIdx - 1);
                        delete enemyPlayerList;
                        dynamic_cast<DiplomacyCard*>(card)->play(deckpointer, curplayer, enemyPlayer);
                    }
                } cout << "Invalid choice\n";
                    break;
            }
            case 0:
            {
                isDone = true;
                break;
            }
        }
    }
}

HumanPlayerStrategy::HumanPlayerStrategy(){}
HumanPlayerStrategy::~HumanPlayerStrategy() {}
HumanPlayerStrategy::HumanPlayerStrategy(const HumanPlayerStrategy& h) :  PlayerStrategy{ h } {}
HumanPlayerStrategy& HumanPlayerStrategy:: operator = (const HumanPlayerStrategy& h)  
{ 
	PlayerStrategy::operator=(h);
	return *this; 
}

ostream& operator << (ostream& out,  HumanPlayerStrategy& h)
{
	out << "this is a Human player strategy";
	return out;
}

vector<Territory*>* HumanPlayerStrategy::toAttack(Map* m, Player* p) 
{
    //List of all Hostile territories that share at least one border with one of player's territories
    vector<Territory*>* territoriesToDefend = p->gettoDefend(*m);
    vector<Territory*>* territoriesToAttack = p->getterritoriesToAttack();
    territoriesToAttack->clear();
    vector<Territory*>* result = DBG_NEW vector<Territory*>();
    for (int i = 0; i < territoriesToDefend->size(); i++) 
    {
        vector<Territory*>* terr = p->surroundingterritories(*m, *territoriesToDefend->at(i));
        for (int j = 0; j < terr->size(); j++) 
        {
            if (terr->at(j)->getterritory_owner()->getName().compare(territoriesToDefend->at(i)->getterritory_owner()->getName()) != 0) 
            {
                bool exists = false;
                for (int k = 0; k < result->size(); k++) 
                {
                    if (terr->at(j)->getterritory_name().compare(result->at(k)->getterritory_name()) == 0)exists = true;
                }
                if (!exists) 
                {
                    result->push_back(terr->at(j));
                    break;
                }
            }
        }
        terr->clear();
        delete terr;
    }
    for (int i = 0; i < result->size(); i++) 
    {
        territoriesToAttack->push_back(result->at(i));
    }
    result->clear();
    delete result;
    return territoriesToAttack;
}
vector<Territory*>* HumanPlayerStrategy::toAttack(Map* m, Player* p, Territory* t)
{
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
vector<Territory*>* HumanPlayerStrategy::toDefend(Map* m, Player* p) 
{
    vector<Territory*>* territoriesToDefend = p->gettoDefend(*m);

    return  territoriesToDefend;
}
void AggressivePlayerStrategy::issueorder(Map* m, vector<Player*>* pl, Player* curplayer, Deck* deckpointer) {
    if (curplayer->toDefend(*m)->size() > 1) {
        int* reinforcementCounter = DBG_NEW int(curplayer->getCurrentReinforcements());
        Territory* t = curplayer->toDefend(*m)->at(0);
        curplayer->addOrder(DBG_NEW Deployorder(curplayer, reinforcementCounter, t));
        Territory* defend = toDefend(m, curplayer)->at(0);
        Territory* attack = toAttack(m, curplayer, defend)->at(0);
        for (int i = 1; i < curplayer->gettoDefend(*m)->size(); i++) {
            if (curplayer->gettoDefend(*m)->at(i)->getterritory_armycount() > 1 && m->isAdjacent(defend, curplayer->gettoDefend(*m)->at(i))) {
                int* attacknum2 = DBG_NEW int(curplayer->gettoDefend(*m)->at(i)->getterritory_armycount() - 1);
                curplayer->addOrder(DBG_NEW Advanceorder(attacknum2, curplayer, defend, curplayer->gettoDefend(*m)->at(i), m));
            }
        }
        int* attacknum = DBG_NEW int(*reinforcementCounter + t->getterritory_armycount() - 2);
        curplayer->addOrder(DBG_NEW Advanceorder(attacknum, curplayer, attack, defend, m));
    }
    vector<Card*> cards = curplayer->getHand()->getHandContainer();
    for (int i = 0; i < cards.size(); i++) {
        Card* card = cards.at(i);
        if (card->getName() == "Blockade Card" && curplayer->gettoDefend(*m)->size() > 0)
        {
            // the play method adds the order to the player's orderlist
             int end = curplayer->toDefend(*m)->size() - 1;
            dynamic_cast<BlockadeCard*>(card)->play(deckpointer, curplayer, curplayer->toDefend(*m)->at(end));
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
AggressivePlayerStrategy& AggressivePlayerStrategy::operator = (const AggressivePlayerStrategy& h)  {
	PlayerStrategy::operator=(h);
	return *this;
}

ostream& operator << (ostream& out,  AggressivePlayerStrategy& h)
{
	out << "this is a Agressive player strategy";
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
    if (curplayer->toDefend(*m)->size() > 1) {
        int* reinforcementCounter = DBG_NEW int(curplayer->getCurrentReinforcements());
        Territory* t = curplayer->toDefend(*m)->at(0);
        // deploy order which deploys to weakest territories
        curplayer->addOrder(new Deployorder(curplayer, reinforcementCounter, t));
        Territory* sourceterr = toDefend(m, curplayer)->at(3);
        Territory* destinationterr = toDefend(m, curplayer)->at(0);

        for (int i = 1; i < curplayer->gettoDefend(*m)->size(); i++) {
            if (curplayer->gettoDefend(*m)->at(i)->getterritory_armycount() > 1 && m->isAdjacent(sourceterr, curplayer->gettoDefend(*m)->at(i))) {
                int* armynum2 = new int(curplayer->gettoDefend(*m)->at(i)->getterritory_armycount() - 1);
                curplayer->addOrder(new Advanceorder(armynum2, curplayer, sourceterr, curplayer->gettoDefend(*m)->at(i), m));
            }
        }
        int* armynum = new int(*reinforcementCounter + t->getterritory_armycount() - 2);
        // advance order which advances armies on players weakest countries and
        // never advances to enemy territories
        curplayer->addOrder(new Advanceorder(armynum, curplayer, destinationterr, sourceterr, m));

        // deleting and emptying cards in benevolent players hand
        // since this player cannot issue orders related to cards
        vector<Card*> cards = curplayer->getHand()->getHandContainer();
        for(int i = 0; i < cards.size(); i ++){
            delete cards.at(i);
            cards.at(i) = NULL;
        }
        cards.clear();
    }
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
	out << "this is a Benevolent player strategy";
	return out;
}

vector<Territory*>* BenevolentPlayerStrategy::toAttack(Map* m, Player* p, Territory* t) {
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
vector<Territory*>* BenevolentPlayerStrategy::toAttack(Map* m, Player* p) {
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
vector<Territory*>* BenevolentPlayerStrategy::toDefend(Map* m, Player* p) {
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
        int min = 100000;
        int index = -1;
        for (int i = 0; i < terr2->size(); i++) {
            if (terr2->at(i)->getterritory_armycount() < min) {
                min = terr2->at(i)->getterritory_armycount();
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
	out << "this is a Neutral player strategy for player";
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
