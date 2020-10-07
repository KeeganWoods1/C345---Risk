#include<iostream>
#include"Cards.h"
#include<vector>

using namespace std;

Card::Card()
{
    name = "";
}

Card::Card(string name) :name(){}

Card::~Card(){}

string Card::getName()
{
    return this->name;
}

Card* Card::findAndRemove(vector<Card*> hand, string cardName)
{
    int handSize = hand.size();
    for(int i=0; i<handSize; i++)
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

BombCard::BombCard(string name) : name()
{
    cout << "Creating " << name << std::endl;
}

void BombCard::play(list<Card*> deck, vector<Card*> hand)
{
    //TODO: add to orderList
    //bombOrderPtr = new Bomborder(1,1);

    //remove card from the hand
    //place card back in deck
    deck.push_back(findAndRemove(hand, "Bomb Card"));
}

ReinforcementCard::ReinforcementCard(string name) :name()
{
    cout << "Creating " << name << std::endl;
}

void ReinforcementCard::play(list<Card*> deck, vector<Card*> hand)
{
    //TODO: add to orderList
    //reinforcementOrderPtr = new Reinforcementorder(1);

    //remove card from the hand
    //place card back in deck
    deck.push_back(findAndRemove(hand, "Reinforcement Card"));
}

BlockadeCard::BlockadeCard(string name) :name()
{
    cout << "Creating " << name << std::endl;
}

void BlockadeCard::play(list<Card*> deck, vector<Card*> hand)
{
    //TODO: add to orderList
    //blockadeOrderPtr = new Blockadeorder(1,1);

    //remove card from the hand
    //place card back in deck
    deck.push_back(findAndRemove(hand, "Blockade Card"));
}

AirliftCard::AirliftCard(string name) :name()
{
    cout << "Creating " << name << std::endl;
}

void AirliftCard::play(list<Card*> deck, vector<Card*> hand)
{
    //TODO: add to orderList
    //airliftOrderPtr = new airliftorder(1,1,1,1);

    //remove card from the hand
    //place card back in deck
    deck.push_back(findAndRemove(hand, "Airlift Card"));
}

DiplomacyCard::DiplomacyCard(string name) :name()
{
    cout << "Creating " << name << std::endl;
}

void DiplomacyCard::play(list<Card*> deck, vector<Card*> hand)
{
    //TODO: add to orderList
    //diplomacyOrderPtr = new Negotiateorder(1,1);

    //remove card from the hand
    //place card back in deck
    deck.push_back(findAndRemove(hand, "Diplomacy Card"));
}

Deck::Deck()
{
    cout << "Generating Deck" << std::endl;
     
    bombCrdPtr = new BombCard("Bomb Card");
    reinCrdPtr = new ReinforcementCard("Reinforcement Card");
    alftCrdPtr = new AirliftCard("Airlift Card");
    dpcyCrdPtr = new DiplomacyCard("Diplomacy Card");
    blkdCrdPtr = new BlockadeCard("Blockade Card");

    cout << deckOfCards.size() << std::endl;
    deckOfCards.push_back(bombCrdPtr);
    cout << deckOfCards.size() << std::endl;
    deckOfCards.push_back(reinCrdPtr);
    cout << deckOfCards.size() << std::endl;
    deckOfCards.push_back(alftCrdPtr);
    cout << deckOfCards.size() << std::endl;
    deckOfCards.push_back(dpcyCrdPtr);
    cout << deckOfCards.size() << std::endl;
    deckOfCards.push_back(blkdCrdPtr); 
    cout << deckOfCards.size() << std::endl;

    Card card = *bombCrdPtr;

    cout << card << std::endl;
}

Deck::~Deck(){}

void Deck::draw(Hand* hand)
{
    vector<Card*> handOfCards = hand->getHand();
    Card* drawnCard = *itFront;
    handOfCards.erase(handOfCards.begin());
    itFront = deckOfCards.erase(itFront);
}

list<Card*> Deck::getDeck()
{
    return deckOfCards;
}

Hand::Hand()
{
    vector<Card*> handOfCards;
}

vector<Card*> Hand::getHand()
{
    return handOfCards;
}

int main()
{
    Deck deck;
    list<Card*> deckList = deck.getDeck();
    list<Card*>::iterator iterator = deckList.begin();
    Card card = **iterator;

    std::cout << card << std::endl;

    return 0;
}
