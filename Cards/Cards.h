#include"../Orders & Orderslist/Order.h"
#include<list>
#include<vector>
#include<iostream>

//TODO: add stream insertion operators

class Card
{
private:
    string name;
public:
    Card();
    Card(string name);
    ~Card();
    void Play();
    string getName();
    Card* findAndRemove(vector<Card*> hand, string cardName);
    friend ostream &operator << (ostream &out, const Card &o)
    {
        out << "Card Type: " << o.name;
    }
};

class BombCard : public Card
{
private:
    string name;
    Bomborder* bombOrderPtr;
public:
    BombCard(string name);
    ~BombCard();
    void play(list<Card*> deck, vector<Card*> hand);
    friend ostream &operator << (ostream &out, const BombCard &o)
    {
        out << "Card Type: " << o.name;
    }
};

class ReinforcementCard : public Card
{
private:
    string name;
    Reinforcementorder* reinforcementOrderPtr;
public:
    ReinforcementCard(string name);
    ~ReinforcementCard();
    void play(list<Card*> deck, vector<Card*> hand);
};

class BlockadeCard : public Card
{
private:
    string name;
    Order* blockadeOrderPtr;
public:
    BlockadeCard(string name);
    ~BlockadeCard();
    void play(list<Card*> deck, vector<Card*> hand);
};

class AirliftCard : public Card
{
private:
    string name;
    Order* airliftOrderPtr;
public:
    AirliftCard(string name);
    ~AirliftCard();
    void play(list<Card*> deck, vector<Card*> hand);
};

class DiplomacyCard : public Card
{
private:
    string name;
    Order* diplomacyOrderPtr;
public:
    DiplomacyCard(string name);
    ~DiplomacyCard();
    void play(list<Card*> deck, vector<Card*> hand);
};

class Hand
{
    private:
        vector<Card*> handOfCards;
    public:
        Hand();
        ~Hand();
        vector<Card*> getHand();
};

class Deck
{
    private:
        list<Card*> deckOfCards;
        list<Card*>::iterator itFront, itBack;
    public:        
        Card* bombCrdPtr;
        Card* reinCrdPtr;
        Card* alftCrdPtr;
        Card* dpcyCrdPtr;
        Card* blkdCrdPtr;
        Deck();
        ~Deck();
        void draw(Hand* handOfCards);
        list<Card*> getDeck();
};



