#include "Cards.cpp"
#include "../Player/Player.cpp"
#include "../Orders/Orders.cpp"
#include "../Map/map.cpp"
#include <iostream>
#include <vector>
#include <stdlib.h>


int main()
{
    //Create a deck of 10 cards
    Deck* deckPtr = new Deck();
    
    //Create a hand of cards
    Hand* handPtr = new Hand();

    //create order list
    Orderlist* orderListPtr = new Orderlist();

    //create player
    Player* playerPtr = new Player("Jon");

    //create territory
    Territory* territory = new Territory(1, "t1", playerPtr, 1);
    
    //Show deck contents  
    std::cout << "\nShowing Deck Contents... " << std::endl;
    std::cout << *deckPtr;

    //Show hand and deck sizes
    std::cout << "Hand Size: " << handPtr->getHand().size() << std::endl;
    std::cout << "Deck Size: " << deckPtr->getDeck().size() << std::endl;

    //Draw 5 cards at random places in the deck, showing the deck/hand sizes after each draw
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
    std::cout << "\nShowing Deck Content... " << std::endl;
    std::cout << *deckPtr;
    std::cout << "\nShowing Hand Content... " << std::endl;
    std::cout << *handPtr;

    //play the bomb card from hand
    BombCard* bombCardSelectedByPlayer = new BombCard("Bomb Card");
    bombCardSelectedByPlayer->play(deckPtr, handPtr, orderListPtr, playerPtr, territory);//problem with arguments! --> seg fault 11

    cout << "Showing orders list contents: ";
    cout << *orderListPtr;

    return 0;
}
