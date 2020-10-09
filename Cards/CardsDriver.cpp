#include <iostream>
#include "Cards.cpp"
#include <vector>
#include <stdlib.h>
#include "../Orders/Orderlist.cpp"
#include "../Orders/dummy.cpp"
#include "../Orders/Order.cpp"

int main()
{
    //Create a deck of 10 cards
    Deck* deckPtr = new Deck();
    
    //Create a hand of cards
    Hand* handPtr = new Hand();
    
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

    //Play all 5 cards in the hand, showing the card played and the hand/deck sizes after each card played
    std::cout << "\nPlaying each card in hand... \n" << std::endl;
    Orderlist* orderListPtr = new Orderlist();
    for(int i=0; i<5; i++)
    {
        handPtr->getHand()[0]->play(deckPtr, handPtr, orderListPtr);
    }

    //Show contents of orders list after cards have been played
    std:cout << "\nDisplaying Orderlist contents... \n" <<std::endl;
    std::cout << *orderListPtr;

    //Show deck contents after crads have been played
    std::cout << "\nShowing Deck Content... \n" << std::endl;
    std:: cout << *deckPtr;

    //Show hand contents after cards have been played
    std::cout << "\nShowing hand content...\n" << std::endl;
    std::cout << *handPtr;

    delete(deckPtr);
    delete(handPtr);
    delete(orderListPtr);
    deckPtr = NULL;
    handPtr = NULL;
    orderListPtr = NULL;

    return 0;
}
