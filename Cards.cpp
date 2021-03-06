#include "Cards.h"
#include <iostream>
#include <vector>
#include <stdlib.h>
#include <random>
#include <algorithm>
//#include <crtdbg.h>
#ifdef _DEBUG
#define DBG_NEW new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
// Replace _NORMAL_BLOCK with _CLIENT_BLOCK if you want the
// allocations to be of _CLIENT_BLOCK type
#else
#define DBG_NEW new
#endif
using namespace std;

//Card default constructor

Card::Card()
{
    name = "test";
}

//Card parametrized constructor
Card::Card(string name) :name(){}

//Card destructor
Card::~Card(){}

//virtual play() method will defer to the play() method of the calling card type
void Card::play(Deck* deck, Hand* hand, Orderlist* orderlist){std::cout << "Playing Default Card" << std::endl;}

//Accessor
string Card::getName()
{
    return this->name;
}

/*Find method
* 
* Linear search through a small array will
* return a pointer to the first occurence of the card being searched for.
*
* @params: Hand* hand, string name. 
*/
Card* Card::find(Hand* hand, string cardName)
{
    vector<Card*> handContainer = hand->getHandContainer();

    for(int i=0; i<handContainer.size(); i++)
    {
        if(handContainer[i]->getName() == cardName)
        {
            Card* cardToReturn = handContainer[i];
            handContainer.erase(handContainer.begin() + i);
            
            hand->setHand(handContainer);

            std::cout << "Playing " << *cardToReturn << std::endl;

            return cardToReturn;
        }
    }
    return NULL;
}

//copy constructor
Card::Card(const Card& c) : name(c.name) 
{
}

//assignmnet operator overload
Card &Card::operator = (const Card& o) 
{
    name = o.name;
    return *this;
}

//stream i/o overloads
istream &operator >> (istream &stream, Card &o)
{
    stream >> o.name;
    return stream;
}

ostream &operator << (ostream &out, const Card &o)
{
    out << o.name;
    return out;
}

//Constructor
BombCard::BombCard(string n)
{
    name = n;
    bombOrderPtr = NULL;
}

//BombCard destructor
BombCard::~BombCard()
{
    if (bombOrderPtr == NULL) return;
    delete(bombOrderPtr);
    bombOrderPtr = NULL;
}

/*
* Play method adds appropriate order to 
* the orderlist, removes card from hand and 
* replaces it in the deck
*
* @params Deck*, Hand*, Orderlist*
*/
void BombCard::play(Deck* deck, Player* player, Territory* territory)
{
    cout << "In Play() method" << endl;
    vector<Card*> deckContainer = deck->getDeck();

    //create order and add to orderlist
    player->addOrder(DBG_NEW Bomborder(player, territory));

    //remove card from the hand
    //place card back in deck
    deckContainer.push_back(find(player->getHand(), "Bomb Card"));
    deck->setDeck(deckContainer);
}

void BombCard::deletecard(Deck* deck, Hand* hand, Player* player) {
    vector<Card*> deckContainer = deck->getDeck();
    //place card back in deck
    deckContainer.push_back(find(player->getHand(), "Bomb Card"));
    deck->setDeck(deckContainer);
}

//copy constructor
BombCard::BombCard(const BombCard& c) : bombOrderPtr(c.bombOrderPtr) 
{
    std::cout << "copy construction of BombCard\n";
}

//assignment operator
BombCard &BombCard::operator = (const BombCard& o)
{
    std::cout << "copy assignment of BombCard\n";
    name = o.name;
    bombOrderPtr = o.bombOrderPtr;
    return *this;
}

//constructor
ReinforcementCard::ReinforcementCard(string n)
{
    name = n;
    reinforcementOrderPtr = NULL;
}

//ReinforcementCard destructor
ReinforcementCard::~ReinforcementCard()
{
    if (reinforcementOrderPtr == NULL) return;
    delete(reinforcementOrderPtr);
    reinforcementOrderPtr = NULL;
}

/*
* Play method adds appropriate order to 
* the orderlist, removes card from hand and 
* replaces it in the deck
*
* @params Deck*, Hand*, Orderlist*
*/
void ReinforcementCard::play(Deck* deck, Player* player)
{
    vector<Card*> deckContainer = deck->getDeck();

    //create order and add to orderlist
    player->addOrder(DBG_NEW Reinforcementorder(player));

    //remove card from the hand
    //place card back in deck
    deckContainer.push_back(find(player->getHand(), "Reinforcement Card"));
    deck->setDeck(deckContainer);
}

void ReinforcementCard::deletecard(Deck* deck, Hand* hand, Player* player) {
    vector<Card*> deckContainer = deck->getDeck();
    //place card back in deck
    deckContainer.push_back(find(player->getHand(), "Reinforcement Card"));
    deck->setDeck(deckContainer);
}

//copy ocnstructor
ReinforcementCard::ReinforcementCard(const ReinforcementCard& c) : reinforcementOrderPtr(c.reinforcementOrderPtr) 
{
    std::cout << "copy construction of Reinforcement Card\n";
}

//assignment operator
ReinforcementCard &ReinforcementCard::operator = (const ReinforcementCard& o)
{
    std::cout << "copy assignment of ReinforcementCard\n";
    name = o.name;
    reinforcementOrderPtr = o.reinforcementOrderPtr;
    return *this;
}

//constructor
BlockadeCard::BlockadeCard(string n)
{
    name = n;
    blockadeOrderPtr = NULL;
}

//BlockadeCard destructor
BlockadeCard::~BlockadeCard()
{
    if (blockadeOrderPtr == NULL) return;
    delete(blockadeOrderPtr);
    blockadeOrderPtr = NULL;
}

/*
* Play method adds appropriate order to 
* the orderlist, removes card from hand and 
* replaces it in the deck
*
* @params Deck*, Hand*, Orderlist*
*/
void BlockadeCard::play(Deck* deck, Player* player, Territory* territory)
{
    vector<Card*> deckContainer = deck->getDeck();   

    //create order and add to orderlist
    player->addOrder(DBG_NEW Blockadeorder(player, territory));

    //remove card from the hand
    //place card back in deck
    deckContainer.push_back(find(player->getHand(), "Blockade Card"));
    deck->setDeck(deckContainer);
}

void BlockadeCard::deletecard(Deck* deck, Hand* hand, Player* player) {

    vector<Card*> deckContainer = deck->getDeck();
    //place card back in deck
    deckContainer.push_back(find(player->getHand(), "Blockade Card"));
    deck->setDeck(deckContainer);
}

//copy ocnstructor
BlockadeCard::BlockadeCard(const BlockadeCard& c) : blockadeOrderPtr(c.blockadeOrderPtr) 
{
    std::cout << "copy construction of BlockadeCard\n";
}

//assignment operator
BlockadeCard &BlockadeCard::operator = (const BlockadeCard& o)
{
    std::cout << "copy assignment of BlockadeCard\n";
    name = o.name;
    blockadeOrderPtr = o.blockadeOrderPtr;
    return *this;
}

//constructor
AirliftCard::AirliftCard(string n)
{
    name = n;
    airliftOrderPtr = NULL;
}

//AirliftCard destructor
AirliftCard::~AirliftCard()
{
    if (airliftOrderPtr == NULL) return;
    delete(airliftOrderPtr);
    airliftOrderPtr = NULL;
}

/*
* Play method adds appropriate order to 
* the orderlist, removes card from hand and 
* replaces it in the deck
*
* @params Deck*, Hand*, Orderlist*
*/
void AirliftCard::play( Deck* deck, Player* player, Territory* territorySource, Territory* territoryDestination, int* i)
{
    vector<Card*> deckContainer = deck->getDeck();
    
    //create order and add to orderlist
    player->addOrder(DBG_NEW Airliftorder(i, territorySource, territoryDestination, player));

    //remove card from the hand
    //place card back in deck
    deckContainer.push_back(find(player->getHand(), "Airlift Card"));  
    deck->setDeck(deckContainer);
}

void AirliftCard::deletecard(Deck* deck, Hand* hand, Player* player) {
    vector<Card*> deckContainer = deck->getDeck();
    //place card back in deck
    deckContainer.push_back(find(player->getHand(), "Airlift Card"));
    deck->setDeck(deckContainer);

}

//copy ocnstructor
AirliftCard::AirliftCard(const AirliftCard& c) : airliftOrderPtr(c.airliftOrderPtr) 
{
    std::cout << "copy construction of AirliftCard\n";
}

//assignment operator
AirliftCard &AirliftCard::operator = (const AirliftCard& o)
{
    std::cout << "copy assignment of AirliftCard\n";
    name = o.name;
    airliftOrderPtr = o.airliftOrderPtr;
    return *this;
}

//constructor
DiplomacyCard::DiplomacyCard(string n) 
{
    name = n;
    diplomacyOrderPtr = NULL;
}

//DiplomacyCard destructor
DiplomacyCard::~DiplomacyCard()
{
    if (diplomacyOrderPtr == NULL) return;
    delete(diplomacyOrderPtr);
    diplomacyOrderPtr = NULL;
}

/*
* Play method adds appropriate order to 
* the orderlist, removes card from hand and 
* replaces it in the deck
*
* @params Deck*, Hand*, Orderlist*
*/
void DiplomacyCard::play(Deck* deck, Player* player, Player* targetPlayer)
{
    vector<Card*> deckContainer = deck->getDeck();

    //create order and add to orderlist
    player->addOrder(DBG_NEW Negotiateorder(player, targetPlayer));

    //remove card from the hand
    //place card back in deck
    deckContainer.push_back(find(player->getHand(), "Diplomacy Card"));
    deck->setDeck(deckContainer);
}

void DiplomacyCard::deletecard(Deck* deck, Hand* hand, Player* player) {
    vector<Card*> deckContainer = deck->getDeck();
    //place card back in deck
    deckContainer.push_back(find(player->getHand(), "Diplomacy Card"));
    deck->setDeck(deckContainer);

}

//copy ocnstructor
DiplomacyCard::DiplomacyCard(const DiplomacyCard& c) : diplomacyOrderPtr(c.diplomacyOrderPtr) 
{
    std::cout << "copy construction of DiplomacyCard\n";
}

//assignment operator
DiplomacyCard &DiplomacyCard::operator = (const DiplomacyCard& o)
{
    std::cout << "copy assignment of DiplomacyCard\n";
    name = o.name;
    diplomacyOrderPtr = o.diplomacyOrderPtr;
    return *this;
}

//constructor
Deck::Deck()
{
    cout << "\nGenerating Deck..." << std::endl;

    deckOfCardsPtr = DBG_NEW vector<Card*>();

    //Create pointers to card objects 
    bombCrdPtr = DBG_NEW BombCard("Bomb Card");
    reinCrdPtr = DBG_NEW ReinforcementCard("Reinforcement Card");
    alftCrdPtr = DBG_NEW AirliftCard("Airlift Card");
    dpcyCrdPtr = DBG_NEW DiplomacyCard("Diplomacy Card");
    blkdCrdPtr = DBG_NEW BlockadeCard("Blockade Card");

    //push 5 cards into the deck
    deckOfCardsPtr->push_back(bombCrdPtr);
    deckOfCardsPtr->push_back(reinCrdPtr);
    deckOfCardsPtr->push_back(alftCrdPtr);
    deckOfCardsPtr->push_back(dpcyCrdPtr);
    deckOfCardsPtr->push_back(blkdCrdPtr);    
}

//parametrized constructor
Deck::Deck(int numOfPlayers)
{
    cout << "\nGenerating Deck..." << std::endl;

    deckOfCardsPtr = DBG_NEW vector<Card*>();

    //The more players there are, the larger the deck should be
    for(int i=0; i<numOfPlayers; i++)
    {
        //push 5 cards into the deck
        deckOfCardsPtr->push_back(DBG_NEW BombCard("Bomb Card"));
        deckOfCardsPtr->push_back(DBG_NEW ReinforcementCard("Reinforcement Card"));
        deckOfCardsPtr->push_back(DBG_NEW AirliftCard("Airlift Card"));
        deckOfCardsPtr->push_back(DBG_NEW DiplomacyCard("Diplomacy Card"));
        deckOfCardsPtr->push_back(DBG_NEW BlockadeCard("Blockade Card"));
    } 
    cout << "Shuffling Cards..." << endl;
    //shuffle deck
    //rng used as seed for std::mt19337
    std::random_device rd;
    //mersenne-twister-engine to ensure high quality "shuffle"
    std::mt19937 g(rd());
    //shuffle playerList, play order will be the order in which players appear in the shuffled list
    std::shuffle(deckOfCardsPtr->begin(), deckOfCardsPtr->end(), g);
}

//Destructor
Deck::~Deck()
{
    for(int i=0; i<deckOfCardsPtr->size(); i++)
    {
        if(deckOfCardsPtr->at(i) != NULL)
        {
            delete(deckOfCardsPtr->at(i));
            deckOfCardsPtr->at(i) = NULL;
        }
    }

    if(deckOfCardsPtr != NULL)
    {
        delete(deckOfCardsPtr);
    }
}

/*
* Draw method will randomly pick a card out of a deck structure
* and place the card at the front of a hand structure. 
*
* @Params Deck*, Hand*
*/
void Deck::draw(Hand* hand)
{
    //Define the vector/vector arrays containing the hand/deck cards respectively
    vector<Card*> handContainer = hand->getHandContainer();
    vector<Card*> deckContainer = this->getDeck();
    if (deckContainer.size() ==0){
        cout<<"sorry the deck is empty! please play more cards";
        return;
    }
    //Draw a card, push it to the hand object's vector array and remove it from the deck object's vector array
    Card* drawnCard = deckContainer.at(0);
    handContainer.push_back(drawnCard);
    deckContainer.erase(deckContainer.begin());

    //Set the hand and deck object's arrays to the post-draw container values
    hand->setHand(handContainer);
    this->setDeck(deckContainer);
}

//Accessor
vector<Card*> Deck::getDeck()
{
    return *this->deckOfCardsPtr;
}

//Mutator
void Deck::setDeck(vector<Card*> d)
{
    *deckOfCardsPtr = d;
}

//copy ocnstructor
Deck::Deck(const Deck& d) 
{
    deckOfCardsPtr = DBG_NEW vector<Card*>;
    for (int i = 0; i < d.deckOfCardsPtr->size(); i++) {
        deckOfCardsPtr->push_back(DBG_NEW Card(*d.deckOfCardsPtr->at(i)));
    }
}

//assignment operator
Deck &Deck::operator = (const Deck& d)
{
    deckOfCardsPtr = d.deckOfCardsPtr;
    itFront = d.itFront;
    return *this;
}

//stream i/o operator overloads
istream &operator >> (istream& stream, Deck& o)
{
    if(o.deckOfCardsPtr->size() > 0)
    {
        for(auto cardPtr : *o.deckOfCardsPtr)
        {
            stream >> *cardPtr;
        } 
    }

    return stream;
}

ostream &operator << (ostream &out, const Deck& o)
{
    if(o.deckOfCardsPtr->size() > 0)
    {
        for(auto cardPtr : *o.deckOfCardsPtr)
        {
            out << *cardPtr << endl;
        } 
    }
    else
    {
        out << "Deck is empty" << endl;
    }

    return out;
}

//Constructor
Hand::Hand()
{
    handOfCardsPtr = DBG_NEW vector<Card*>();
}

//Hand destructor
Hand::~Hand() 
{
    for (int i = 0; i < handOfCardsPtr->size(); i++) {
        delete handOfCardsPtr->at(i);
    }
    delete handOfCardsPtr;
    handOfCardsPtr = NULL;
}

//Accessor
vector<Card*> Hand::getHandContainer()
{
    return *this->handOfCardsPtr;
}

//Mutator
void Hand::setHand(vector<Card*> h)
{
    *handOfCardsPtr = h;
}

//copy ocnstructor
Hand::Hand(const Hand& h) 
{
    handOfCardsPtr = DBG_NEW vector<Card*>;
    for (int i = 0; i < h.handOfCardsPtr->size(); i++) {
        handOfCardsPtr->push_back(DBG_NEW Card(*h.handOfCardsPtr->at(i)));
    }
}

//assignment operator
Hand &Hand::operator = (const Hand& h)
{
    std::cout << "copy assignment of Deck\n";
    handOfCardsPtr = h.handOfCardsPtr;
    return *this;
}

//stream i/o operator overloads
istream &operator >> (istream& stream, Hand& o)
{   
    if(o.handOfCardsPtr->size() > 0)
    {
        for(int i=0; i<o.handOfCardsPtr->size(); i++)
        {
            stream >> *o.handOfCardsPtr->at(i);
        }  
    }

    return stream;
}

ostream &operator << (ostream &out, const Hand& o)
{
    if(o.handOfCardsPtr->size() > 0)
    {
        for(int i=0; i<o.handOfCardsPtr->size(); i++)
        {
            out << *o.handOfCardsPtr->at(i) << endl;
        }  
    }
    else
    {
        out << "Hand is empty" << endl;
    }

    return out;
}

