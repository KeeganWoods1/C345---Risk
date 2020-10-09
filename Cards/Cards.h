#include"../Orders & Orderslist/Order.h"
#include<list>
#include<vector>
#include<iostream>

//TODO: add stream insertion operators

class Card
{
protected:
    string name;
public:
    Card();
    Card(string name);
    ~Card();
    virtual void play(list<Card*>* deck, vector<Card*>* hand);
    string getName();
    Card* find(vector<Card*> hand, string cardName);
    //copy ocnstructor
	Card(const Card& c);
	//assignment operator
	Card& operator = (const Card& o);
    friend istream &operator >> (istream& stream, Card& o);
    friend ostream &operator << (ostream &out, const Card &o);
};

class BombCard : public Card
{
private:
    Bomborder* bombOrderPtr;
public:
    BombCard(string name);
    ~BombCard();
    void play(list<Card*>* deck, vector<Card*>* hand);
    //copy ocnstructor
	BombCard(const BombCard& c);
	//assignment operator
	BombCard& operator = (const BombCard& o);
};

class ReinforcementCard : public Card
{
private:
    Reinforcementorder* reinforcementOrderPtr;
public:
    ReinforcementCard(string name);
    ~ReinforcementCard();
    void play(list<Card*>* deck, vector<Card*>* hand);
    //copy ocnstructor
	ReinforcementCard(const ReinforcementCard& c);
	//assignment operator
	ReinforcementCard& operator = (const ReinforcementCard& o);
};

class BlockadeCard : public Card
{
private:
    Order* blockadeOrderPtr;
public:
    BlockadeCard(string name);
    ~BlockadeCard();
    void play(list<Card*>* deck, vector<Card*>* hand);
    //copy ocnstructor
	BlockadeCard(const BlockadeCard& c);
	//assignment operator
	BlockadeCard& operator = (const BlockadeCard& o);
};

class AirliftCard : public Card
{
private:
    Order* airliftOrderPtr;
public:
    AirliftCard(string name);
    ~AirliftCard();
    void play(list<Card*>* deck, vector<Card*>* hand);
    //copy ocnstructor
	AirliftCard(const AirliftCard& c);
	//assignment operator
	AirliftCard& operator = (const AirliftCard& o);
};

class DiplomacyCard : public Card
{
private:
    Order* diplomacyOrderPtr;
public:
    DiplomacyCard(string name);
    ~DiplomacyCard();
    void play(list<Card*>* deck, vector<Card*>* hand);
    //copy ocnstructor
	DiplomacyCard(const DiplomacyCard& c);
	//assignment operator
	DiplomacyCard& operator = (const DiplomacyCard& o);
};

class Hand
{
    private:
        vector<Card*> handOfCards;
    public:
        Hand();
        ~Hand();
        vector<Card*> getHand();
        void setHand(vector<Card*> h);
        //copy ocnstructor
        Hand(const Hand& h);
        //assignment operator
        Hand& operator = (const Hand& h);
        friend istream &operator >> (istream& stream, Hand& o);
        friend ostream &operator << (ostream &out, const Hand& o);
};

class Deck
{
    private: 
        list<Card*> deckOfCards;
        list<Card*>::iterator itFront;
    public:    
        Card* bombCrdPtr;
        Card* reinCrdPtr;
        Card* alftCrdPtr;
        Card* dpcyCrdPtr;
        Card* blkdCrdPtr;
        Deck();
        ~Deck();
        void draw(Hand* hand, Deck* deck);
        list<Card*> getDeck();
        void setDeck(list<Card*> h);
        //copy ocnstructor
	    Deck(const Deck& d);
	    //assignment operator
	    Deck& operator = (const Deck& d);
        friend istream &operator >> (istream& stream, Deck& o);
        friend ostream &operator << (ostream &out, const Deck& o);
};



