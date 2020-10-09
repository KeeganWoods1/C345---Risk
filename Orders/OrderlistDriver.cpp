#pragma once
#include <iostream>
#include "Order.h"
#include "Orderlist.h"
int main() {
    
    Player *b = new Player("alpha");
    Territory *c = new Territory( "Madagascar");
    Territory *d = new Territory("Nile");
    Player *b11 = new Player("beta");
    Territory *c1 = new Territory("antartica");
    Territory *d1 = new Territory("penguin");
    Advanceorder *a = new Advanceorder(13,*b,*c,*d);
    Airliftorder *b1 = new Airliftorder(6, *d, *c1, *b11);
    Blockadeorder *b2 = new Blockadeorder(*b, *c);
    Bomborder *b6 = new Bomborder(*b11, *c1);
    Deployorder *d6 = new Deployorder(*b, 23, *c);
    Negotiateorder *o2 = new Negotiateorder(*b, *b11);
    Reinforcementorder *r1 = new Reinforcementorder(*b);
    Orderlist *ol = new Orderlist();
    Orderlist *ol2;
    ol2 = ol;
    ol->add(*a);
    ol->add(*b1);
    ol->add(*b2);
    ol->add(*b6);
    ol->add(*d6);
    ol->add(*d6);
    ol->add(*o2);
    ol->add(*r1);
    cout << *ol;
    ol->remove(4);
    cout <<"\n"<< *ol;
    ol->move(4, 2);
    cout << "\n" << *ol;
    cout << "\n\nthis is the assignment\n" << *ol2;
    ol->executelist();
    cout << "\n\n" << *ol;
    delete b;
    delete c;
    delete d;
    delete b11;
    delete c1;
    delete d1;
    delete a;
    delete b1;
    delete b2;
    delete b6;
    delete d6;
    delete o2;
    delete r1;
    delete ol;
    //delete ol2;
    return 0;
};