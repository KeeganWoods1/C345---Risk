#include <iostream>
#include "Cards.cpp"
#include <vector>
#include <stdlib.h>

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
