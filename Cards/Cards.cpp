#include <iostream>
#include "Cards.h"
#include <vector>
#include <stdlib.h>

using namespace std;

Card::Card()
{
    name = "test";
}

Card::Card(string name) :name(){}

Card::~Card(){}

void Card::play(list<Card*>* deck, vector<Card*>* hand){std::cout << "Playing Default Card" << std::endl;}

string Card::getName()
{
    return this->name;
}

Card* Card::find(vector<Card*> hand, string cardName)
{
    std::cout << "Finding " << cardName << std::endl;

    for(int i=0; i<hand.size(); i++)
    {
        if(hand[i]->getName() == cardName)
        {
            Card* cardToReturn = hand[i];
            hand.erase(hand.begin() + i);
            
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

//assignmnet operator
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

BombCard::BombCard(string n)
{
    name = n;
    cout << "Creating " << name << std::endl;
}

void BombCard::play(list<Card*>* deck, vector<Card*>* hand)
{
    //TODO: add to orderList
    //bombOrderPtr = new Bomborder(1,1);

    //remove card from the hand
    //place card back in deck
    deck->push_back(find(*hand, "Bomb Card"));
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

ReinforcementCard::ReinforcementCard(string n)
{
    name = n;
    cout << "Creating " << name << std::endl;
}
//try friend class with deck/hand instead of params
void ReinforcementCard::play(list<Card*>* deck, vector<Card*>* hand)
{
    //TODO: add to orderList
    //reinforcementOrderPtr = new Reinforcementorder(1);

    //remove card from the hand
    //place card back in deck
    deck->push_back(find(*hand, "Reinforcement Card"));
}

//copy ocnstructor
ReinforcementCard::ReinforcementCard(const ReinforcementCard& c) : reinforcementOrderPtr(c.reinforcementOrderPtr) 
{
    std::cout << "copy construction of Reinforcement Card\n";
}

//assignment operator
ReinforcementCard &ReinforcementCard::operator = (const ReinforcementCard& o)
{
    std::cout << "copy assignment of BombCard\n";
    name = o.name;
    reinforcementOrderPtr = o.reinforcementOrderPtr;
    return *this;
}

BlockadeCard::BlockadeCard(string n)
{
    name = n;
    cout << "Creating " << name << std::endl;
}

void BlockadeCard::play(list<Card*>* deck, vector<Card*>* hand)
{
    //TODO: add to orderList
    //blockadeOrderPtr = new Blockadeorder(1,1);

    //remove card from the hand
    //place card back in deck
    deck->push_back(find(*hand, "Blockade Card"));
}

//copy ocnstructor
BlockadeCard::BlockadeCard(const BlockadeCard& c) : blockadeOrderPtr(c.blockadeOrderPtr) 
{
    std::cout << "copy construction of Card\n";
}

//assignment operator
BlockadeCard &BlockadeCard::operator = (const BlockadeCard& o)
{
    std::cout << "copy assignment of BombCard\n";
    name = o.name;
    blockadeOrderPtr = o.blockadeOrderPtr;
    return *this;
}

AirliftCard::AirliftCard(string n)
{
    name = n;
    cout << "Creating " << name << std::endl;
}

void AirliftCard::play(list<Card*>* deck, vector<Card*>* hand)
{
    //TODO: add to orderList
    //airliftOrderPtr = new airliftorder(1,1,1,1);

    //remove card from the hand
    //place card back in deck
    deck->push_back(find(*hand, "Airlift Card"));    
}

//copy ocnstructor
AirliftCard::AirliftCard(const AirliftCard& c) : airliftOrderPtr(c.airliftOrderPtr) 
{
    std::cout << "copy construction of Card\n";
}

//assignment operator
AirliftCard &AirliftCard::operator = (const AirliftCard& o)
{
    std::cout << "copy assignment of BombCard\n";
    name = o.name;
    airliftOrderPtr = o.airliftOrderPtr;
    return *this;
}

DiplomacyCard::DiplomacyCard(string n) 
{
    name = n;
    cout << "Creating " << name << std::endl;
}

void DiplomacyCard::play(list<Card*>* deck, vector<Card*>* hand)
{
    //TODO: add to orderList
    //diplomacyOrderPtr = new Negotiateorder(1,1);

    //remove card from the hand
    //place card back in deck
    deck->push_back(find(*hand, "Diplomacy Card"));
}

//copy ocnstructor
DiplomacyCard::DiplomacyCard(const DiplomacyCard& c) : diplomacyOrderPtr(c.diplomacyOrderPtr) 
{
    std::cout << "copy construction of Card\n";
}

//assignment operator
DiplomacyCard &DiplomacyCard::operator = (const DiplomacyCard& o)
{
    std::cout << "copy assignment of BombCard\n";
    name = o.name;
    diplomacyOrderPtr = o.diplomacyOrderPtr;
    return *this;
}

Deck::Deck()
{
    cout << "Generating Deck..." << std::endl;

    //Create pointers to card objects 
    bombCrdPtr = new BombCard("Bomb Card");
    reinCrdPtr = new ReinforcementCard("Reinforcement Card");
    alftCrdPtr = new AirliftCard("Airlift Card");
    dpcyCrdPtr = new DiplomacyCard("Diplomacy Card");
    blkdCrdPtr = new BlockadeCard("Blockade Card");

    //push 5 cards into the deck
    deckOfCards.push_back(bombCrdPtr);
    deckOfCards.push_back(reinCrdPtr);
    deckOfCards.push_back(alftCrdPtr);
    deckOfCards.push_back(dpcyCrdPtr);
    deckOfCards.push_back(blkdCrdPtr);    
}

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

void Deck::draw(Hand* hand, Deck* deck)
{
    std::cout << "\nDrawing Card" << std::endl;
    
    //Define the vector/list arrays containing the hand/deck cards respectively
    vector<Card*> handContainer = hand->getHand();
    list<Card*> deckContainer = deck->getDeck();
    
    //Random valid index value to be used to draw cards at random
    int randomDeckIdx = rand() % deckContainer.size();

    //Set iterator pointer to beginning of list and advance by a random number of indices
    itFront = deckContainer.begin();
    advance(itFront,randomDeckIdx);
    
    //Draw a card, push it to the hand object's vector array and remove it from the deck object's list array
    Card* drawnCard = *itFront;
    std::cout << "Drawn Card: " << *drawnCard << std::endl;
    handContainer.push_back(drawnCard);
    itFront = deckContainer.erase(itFront);

    //Set the hand and deck object's arrays to the post-draw container values
    hand->setHand(handContainer);
    deck->setDeck(deckContainer);
}

list<Card*> Deck::getDeck()
{
    return this->deckOfCards;
}

void Deck::setDeck(list<Card*> d)
{
    deckOfCards = d;
}

//copy ocnstructor
Deck::Deck(const Deck& d) : deckOfCards(d.deckOfCards), itFront(d.itFront)
{
    std::cout << "copy construction of Deck\n";
}

//assignment operator
Deck &Deck::operator = (const Deck& d)
{
    std::cout << "copy assignment of Deck\n";
    deckOfCards = d.deckOfCards;
    itFront = d.itFront;
    return *this;
}

//stream i/o operator overloads
istream &operator >> (istream& stream, Deck& o)
{

}

ostream &operator << (ostream &out, const Deck& o)
{

}

Hand::Hand()
{
    vector<Card*> handOfCards;
}

vector<Card*> Hand::getHand()
{
    return this->handOfCards;
}

void Hand::setHand(vector<Card*> h)
{
    handOfCards = h;
}

//copy ocnstructor
Hand::Hand(const Hand& h) : handOfCards(h.handOfCards)
{
    std::cout << "copy construction of Hand\n";
}

//assignment operator
Hand &Hand::operator = (const Hand& h)
{
    std::cout << "copy assignment of Deck\n";
    handOfCards = h.handOfCards;
    return *this;
}

//stream i/o operator overloads
istream &operator >> (istream& stream, Hand& o)
{   

}

ostream &operator << (ostream &out, const Hand& o)
{

}

int main()
{
    //Create a deck of 10 cards
    Deck* deckPtr = new Deck();
    list<Card*> deckList = deckPtr->getDeck();
    list<Card*>::iterator iterator = deckList.begin();

    //Show deck contents  
    std::cout << "\nPrinting Deck Contents: " << std::endl;
    for(int i=0; i<deckPtr->getDeck().size(); i++)
    {
        std::cout << **iterator << std::endl;
        advance(iterator,1); 
    }
    
    //Create a hand of cards
    Hand* handPtr = new Hand();
    vector<Card*> handList = handPtr->getHand();

    //Show hand and deck sizes
    std::cout << "Hand Size: " << handList.size() << std::endl;
    std::cout << "Deck Size: " << deckList.size() << std::endl;

    //Draw 5 cards, showing the deck/hand sizes after each draw
    deckPtr->draw(handPtr, deckPtr);
    std::cout << "Hand Size: " << handPtr->getHand().size() << std::endl;
    std::cout << "Deck Size: " << deckPtr->getDeck().size() << std::endl;

    deckPtr->draw(handPtr, deckPtr);
    std::cout << "Hand Size: " << handPtr->getHand().size() << std::endl;
    std::cout << "Deck Size: " << deckPtr->getDeck().size() << std::endl;

    deckPtr->draw(handPtr, deckPtr);
    std::cout << "Hand Size: " << handPtr->getHand().size() << std::endl;
    std::cout << "Deck Size: " << deckPtr->getDeck().size() << std::endl;

    deckPtr->draw(handPtr, deckPtr);
    std::cout << "Hand Size: " << handPtr->getHand().size() << std::endl;
    std::cout << "Deck Size: " << deckPtr->getDeck().size() << std::endl;

    deckPtr->draw(handPtr, deckPtr);
    std::cout << "Hand Size: " << handPtr->getHand().size() << std::endl;
    std::cout << "Deck Size: " << deckPtr->getDeck().size() << std::endl;

    //Show deck/hand contents after drawing phase
    std::cout << "\nShowing Deck Content: " << std::endl;
    if(deckPtr->getDeck().size() > 0)
    {
        deckList = deckPtr->getDeck();
        iterator = deckList.begin();

        for(int i=0; i<deckPtr->getDeck().size(); i++)
        {
            std::cout << **iterator << std::endl;
            advance(iterator,1); 
        } 
    }
    else
    {
        cout << "Deck is empty";
    }

    std::cout << "\nShowing Hand Content: " << std::endl;
    
    handList = handPtr->getHand();

    for(int i=0; i<handPtr->getHand().size(); i++)
    {
        std::cout << *handList[i] << std::endl;
    }

    //Play all 5 cards in the hand, showing the card played and the hand/deck sizes after each card played
    std::cout << "\nPlaying each card in hand: \n" << std::endl;

    vector<Card*>* handContainerPtr = &handList;
    list<Card*>* deckContainerPtr = &deckList;

    for(int i=0; i<handList.size(); i++)
    {
        handPtr->getHand()[i]->play(deckContainerPtr, handContainerPtr);
        std::cout << "Playing " << *handList[i]<< "\n" << std::endl;
    }
       
    return 0;
}
