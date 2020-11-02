#pragma once
#include "Orders.h"
#include "Player.h"
#include "map.h"
#include<vector>
#include<iostream>

class Deck;
class Hand;
class Order;
class Orderlist;
class Advanceorder;
class Airliftorder;
class Bomborder;
class Blockadeorder;
class Negotiateorder;


class Card
{
protected:
    string name;
public:
    Card();
    Card(string name);
    virtual ~Card();
    virtual void play(Deck* deck, Hand* hand, Orderlist* orderList);
    string getName();
    Card* find(Hand* hand, string cardName);
    //copy ocnstructor
	Card(const Card& c);
	//assignment operator
	Card& operator = (const Card& o);
    friend istream &operator >> (istream &stream, Card& o);
    friend ostream &operator << (ostream &out, const Card &o);
};

class BombCard : public Card
{
private:
    Bomborder* bombOrderPtr;
public:
    BombCard(string name);
    ~BombCard();
    void play(Deck* deck, Player* player, Territory* territory);
    //copy ocnstructor
	BombCard(const BombCard& c);
	//assignment operator
	BombCard& operator = (const BombCard& o);
};

class ReinforcementCard : public Card
{
private:
    Order* reinforcementOrderPtr;
public:
    ReinforcementCard(string name);
    ~ReinforcementCard();
    void play(Deck* deck, Player* player);
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
    void play(Deck* deck, Player* player, Territory* territory);
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
    void play( Deck* deck, Player* player, Territory* territorySource, Territory* territoryDestination, int* i);
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
    void play(Deck* deck, Player* player, Player* targetPlayer);
    //copy ocnstructor
	DiplomacyCard(const DiplomacyCard& c);
	//assignment operator
	DiplomacyCard& operator = (const DiplomacyCard& o);
};

class Hand
{
    private:
        vector<Card*>* handOfCardsPtr;
    public:
        Hand();
        ~Hand();
        vector<Card*> getHandContainer();
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
        vector<Card*>* deckOfCardsPtr;
        vector<Card*>::iterator itFront;
    public:    
        Card* bombCrdPtr;
        Card* reinCrdPtr;
        Card* alftCrdPtr;
        Card* dpcyCrdPtr;
        Card* blkdCrdPtr;
        Deck();
        Deck(int);
        ~Deck();
        void draw(Hand* hand, Deck* deck);
        vector<Card*> getDeck();
        void setDeck(vector<Card*> h);
        //copy ocnstructor
	    Deck(const Deck& d);
	    //assignment operator
	    Deck& operator = (const Deck& d);
        friend istream &operator >> (istream& stream, Deck& o);
        friend ostream &operator << (ostream &out, const Deck& o);
};



