#pragma once
#include "Cards.h"
#include <iostream>
#include <vector>
#include <stdlib.h>
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
    vector<Card*> handContainer = hand->getHand();

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
    std::cout << "copy construction of Card\n";
}

//assignmnet operator overload
Card &Card::operator = (const Card& o) 
{
    std::cout << "copy assignment of Card\n";
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
    cout << "Creating " << name << std::endl;
}

//BombCard destructor
BombCard::~BombCard()
{
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
void BombCard::play(Deck* deck, Hand* hand, Orderlist* orderlist, Player* player, Territory* territory)
{
    vector<Card*> deckContainer = deck->getDeck();
    Player* p = new Player(*player);
    Territory* t = new Territory(territory);

    //create order and add to orderlist
    bombOrderPtr = new Bomborder(*p, *t);
    orderlist->add(bombOrderPtr);

    //remove card from the hand
    //place card back in deck
    deckContainer.push_back(find(hand, "Bomb Card"));
    deck->setDeck(deckContainer);

    delete(player);
    delete(territory);
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
    cout << "Creating " << name << std::endl;
}

//ReinforcementCard destructor
ReinforcementCard::~ReinforcementCard()
{
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
void ReinforcementCard::play(Deck* deck, Hand* hand, Orderlist* orderlist, Player* player)
{
    vector<Card*> deckContainer = deck->getDeck();

    //create order and add to orderlist
    reinforcementOrderPtr = new Reinforcementorder(*player);//SEGMENTATION FAULT 11 !!!
    orderlist->add(reinforcementOrderPtr);

    //remove card from the hand
    //place card back in deck
    deckContainer.push_back(find(hand, "Reinforcement Card"));
    deck->setDeck(deckContainer);

    delete(player);
    delete(reinforcementOrderPtr);
    player =NULL;
    reinforcementOrderPtr = NULL;
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
    cout << "Creating " << name << std::endl;
}

//BlockadeCard destructor
BlockadeCard::~BlockadeCard()
{
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
void BlockadeCard::play(Deck* deck, Hand* hand, Orderlist* orderlist, Player* player, Territory* territory)
{
    vector<Card*> deckContainer = deck->getDeck();   

    //create order and add to orderlist
    blockadeOrderPtr = new Blockadeorder(*player, *territory);
    orderlist->add(blockadeOrderPtr);

    //remove card from the hand
    //place card back in deck
    deckContainer.push_back(find(hand, "Blockade Card"));
    deck->setDeck(deckContainer);

    delete(player);
    delete(territory);
    delete(blockadeOrderPtr);
    player = NULL;
    territory = NULL;
    blockadeOrderPtr = NULL;
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
    cout << "Creating " << name << std::endl;
}

//AirliftCard destructor
AirliftCard::~AirliftCard()
{
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
void AirliftCard::play(
    Deck* deck, 
    Hand* hand, 
    Orderlist* orderlist, 
    Player* player, 
    Territory* territorySource, 
    Territory* territoryDestination,
    int i)
{
    vector<Card*> deckContainer = deck->getDeck();
    
    //create order and add to orderlist
    airliftOrderPtr = new Airliftorder(i, *territorySource, *territoryDestination, *player);
    orderlist->add(airliftOrderPtr);

    //remove card from the hand
    //place card back in deck
    deckContainer.push_back(find(hand, "Airlift Card"));  
    deck->setDeck(deckContainer);

    delete(player);
    delete(territorySource);
    delete(territoryDestination);
    delete(airliftOrderPtr);
    player = NULL;
    territorySource = NULL;
    territoryDestination = NULL;
    airliftOrderPtr =NULL;
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
    cout << "Creating " << name << std::endl;
}

//DiplomacyCard destructor
DiplomacyCard::~DiplomacyCard()
{
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
void DiplomacyCard::play(Deck* deck, Hand* hand, Orderlist* orderlist, Player* player, Player* targetPlayer)
{
    vector<Card*> deckContainer = deck->getDeck();

    //create order and add to orderlist
    diplomacyOrderPtr = new Negotiateorder(*player, *targetPlayer);
    orderlist->add(diplomacyOrderPtr);

    //remove card from the hand
    //place card back in deck
    deckContainer.push_back(find(hand, "Diplomacy Card"));
    deck->setDeck(deckContainer);

    delete(player);
    delete(targetPlayer);
    delete(diplomacyOrderPtr);
    player = NULL;
    targetPlayer = NULL;
    diplomacyOrderPtr = NULL;
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
    cout << "Generating Deck..." << std::endl;

    deckOfCardsPtr = new vector<Card*>();

    //Create pointers to card objects 
    bombCrdPtr = new BombCard("Bomb Card");
    reinCrdPtr = new ReinforcementCard("Reinforcement Card");
    alftCrdPtr = new AirliftCard("Airlift Card");
    dpcyCrdPtr = new DiplomacyCard("Diplomacy Card");
    blkdCrdPtr = new BlockadeCard("Blockade Card");

    //push 5 cards into the deck
    deckOfCardsPtr->push_back(bombCrdPtr);
    deckOfCardsPtr->push_back(reinCrdPtr);
    deckOfCardsPtr->push_back(alftCrdPtr);
    deckOfCardsPtr->push_back(dpcyCrdPtr);
    deckOfCardsPtr->push_back(blkdCrdPtr);    
}

//Destructor
Deck::~Deck()
{
    delete(bombCrdPtr);
    delete(reinCrdPtr);
    delete(alftCrdPtr);
    delete(dpcyCrdPtr);
    delete(blkdCrdPtr);

    bombCrdPtr = NULL;
    reinCrdPtr = NULL;
    alftCrdPtr = NULL;
    dpcyCrdPtr = NULL;
    blkdCrdPtr = NULL;
}

/*
* Draw method will randomly pick a card out of a deck structure
* and place the card at the front of a hand structure. 
*
* @Params Deck*, Hand*
*/
void Deck::draw(Hand* hand, Deck* deck)
{
    std::cout << "\nDrawing Card" << std::endl;
    
    //Define the vector/vector arrays containing the hand/deck cards respectively
    vector<Card*> handContainer = hand->getHand();
    vector<Card*> deckContainer = deck->getDeck();
    
    //Random valid index value to be used to draw cards at random
    int randomDeckIdx = rand() % deckContainer.size();
    
    //Draw a card, push it to the hand object's vector array and remove it from the deck object's vector array
    Card* drawnCard = deckContainer[randomDeckIdx];
    std::cout << "Drawn Card: " << *drawnCard << std::endl;
    handContainer.push_back(drawnCard);
    deckContainer.erase(deckContainer.begin() + randomDeckIdx);

    //Set the hand and deck object's arrays to the post-draw container values
    hand->setHand(handContainer);
    deck->setDeck(deckContainer);
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
Deck::Deck(const Deck& d) : deckOfCardsPtr(d.deckOfCardsPtr), itFront(d.itFront)
{
    std::cout << "copy construction of Deck\n";
}

//assignment operator
Deck &Deck::operator = (const Deck& d)
{
    std::cout << "copy assignment of Deck\n";
    deckOfCardsPtr = d.deckOfCardsPtr;
    itFront = d.itFront;
    return *this;
}

//stream i/o operator overloads
istream &operator >> (istream& stream, Deck& o)
{
    if(o.deckOfCardsPtr->size() > 0)
    {
        for(int i=0; i<o.deckOfCardsPtr->size(); i++)
        {
            stream >> *o.deckOfCardsPtr->at(i);
        } 
    }

    return stream;
}

ostream &operator << (ostream &out, const Deck& o)
{
    if(o.deckOfCardsPtr->size() > 0)
    {
        for(int i=0; i<o.deckOfCardsPtr->size(); i++)
        {
            out << *o.deckOfCardsPtr->at(i) << endl;
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
    handOfCardsPtr = new vector<Card*>();
}

//Hand destructor
Hand::~Hand() 
{
    delete(handOfCardsPtr);
    handOfCardsPtr = NULL;
}

//Accessor
vector<Card*> Hand::getHand()
{
    return *this->handOfCardsPtr;
}

//Mutator
void Hand::setHand(vector<Card*> h)
{
    *handOfCardsPtr = h;
}

//copy ocnstructor
Hand::Hand(const Hand& h) : handOfCardsPtr(h.handOfCardsPtr)
{
    std::cout << "copy construction of Hand\n";
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

