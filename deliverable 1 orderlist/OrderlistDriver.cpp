#pragma once
#include <iostream>
#include "Order.h"
#include "Orderlist.h"
int main() {
    
    Player b = Player("alpha");
    Territory c = Territory( "Madagascar");
    Territory d = Territory("Nile");
    Player b11 = Player("beta");
    Territory c1 = Territory("antartica");
    Territory d1 = Territory("penguin");
    Advanceorder a = Advanceorder(13,b,c,d);
    airliftorder b1 = airliftorder(6, d, c1, b11);
    Blockadeorder b2 = Blockadeorder(b, c);
    Bomborder b6 = Bomborder(b11, c1);
    Deployorder d6 = Deployorder(b, 23, c);
    Negotiateorder o2 = Negotiateorder(b, b11);
    Reinforcementorder r1 = Reinforcementorder(b);
    Orderlist ol = Orderlist();
    Orderlist ol2;
    ol2 = ol;
    ol.add(a);
    ol.add(b1);
    ol.add(b2);
    ol.add(b6);
    ol.add(d6);
    ol.add(d6);
    ol.add(o2);
    ol.add(r1);
    cout << ol;
    ol.remove(4);
    cout <<"\n"<< ol;
    ol.move(4, 2);
    cout << "\n" << ol;
    cout << "\n\nthis is the assignment\n" << ol2;
    ol.executelist();
    cout << "\n\n" << ol;
    ol.~Orderlist();
    return 0;
};