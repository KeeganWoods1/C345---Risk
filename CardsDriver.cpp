#include "Cards.h"
#include <iostream>
#include <vector>
#include <stdlib.h>
#include <crtdbg.h>


int main()
{
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
    //Create a deck of 10 cards
    Deck* deckPtr = new Deck();

    //create order list
    Orderlist* orderListPtr = new Orderlist();

    //create player
    Player* playerPtr = new Player("Jon");
    //create player
    Player* player2Ptr = new Player("Jill");

    //create territory
    Territory* territoryPtr = new Territory(1, "t1", playerPtr, 1);
    //create territory
    Territory* territory2Ptr = new Territory(1, "t2", playerPtr, 1);

    int* numOfUnits = new int(5);
    
    //Show deck contents  
    std::cout << "\nShowing Deck Contents... " << std::endl;
    std::cout << *deckPtr;

    //Show hand and deck sizes
    std::cout << "Hand Size: " << playerPtr->getHand()->getHandContainer().size() << std::endl;

    //Draw 5 cards at random places in the deck, showing the deck/hand sizes after each draw
    deckPtr->draw(playerPtr->getHand());
    std::cout << "Hand Size: " << playerPtr->getHand()->getHandContainer().size() << std::endl;
    std::cout << "Deck Size: " << deckPtr->getDeck().size() << std::endl;

    deckPtr->draw(playerPtr->getHand());
    std::cout << "Hand Size: " << playerPtr->getHand()->getHandContainer().size() << std::endl;
    std::cout << "Deck Size: " << deckPtr->getDeck().size() << std::endl;

    deckPtr->draw(playerPtr->getHand());
    std::cout << "Hand Size: " << playerPtr->getHand()->getHandContainer().size() << std::endl;
    std::cout << "Deck Size: " << deckPtr->getDeck().size() << std::endl;

    deckPtr->draw(playerPtr->getHand());
    std::cout << "Hand Size: " << playerPtr->getHand()->getHandContainer().size() << std::endl;
    std::cout << "Deck Size: " << deckPtr->getDeck().size() << std::endl;

    deckPtr->draw(playerPtr->getHand());
    std::cout << "Hand Size: " << playerPtr->getHand()->getHandContainer().size() << std::endl;
    std::cout << "Deck Size: " << deckPtr->getDeck().size() << std::endl;

    //Show deck/hand contents after drawing phase
    std::cout << "\nShowing Deck Content... " << std::endl;
    std::cout << *deckPtr;
    std::cout << "\nShowing Hand Content... " << std::endl;
    std::cout << *playerPtr->getHand();

    //play the bomb card from hand
    for(int i=0; i<playerPtr->getHand()->getHandContainer().size(); i++)
    {
        if(playerPtr->getHand()->getHandContainer().at(i)->getName() == "Bomb Card")
        {
            BombCard* bombCard = (BombCard*)playerPtr->getHand()->getHandContainer().at(i);
            bombCard->play(deckPtr, playerPtr, territoryPtr);
        }
    }  

    //play the airlift card from hand
    for(int i=0; i<playerPtr->getHand()->getHandContainer().size(); i++)
    {
        if(playerPtr->getHand()->getHandContainer().at(i)->getName() == "Airlift Card")
        {
            AirliftCard* airliftCard = (AirliftCard*)playerPtr->getHand()->getHandContainer().at(i);
            airliftCard->play(deckPtr, playerPtr, territoryPtr, territory2Ptr, numOfUnits);
        }
    } 

    //play the reinforcement card from hand
    for(int i=0; i<playerPtr->getHand()->getHandContainer().size(); i++)
    {
        if(playerPtr->getHand()->getHandContainer().at(i)->getName() == "Reinforcement Card")
        {
            ReinforcementCard* reinfCard = (ReinforcementCard*)playerPtr->getHand()->getHandContainer().at(i);
            reinfCard->play(deckPtr, playerPtr);
        }
    }   

    //play the Blockade card from hand
    for(int i=0; i<playerPtr->getHand()->getHandContainer().size(); i++)
    {
        if(playerPtr->getHand()->getHandContainer().at(i)->getName() == "Blockade Card")
        {
            BlockadeCard* blockadeCard = (BlockadeCard*)playerPtr->getHand()->getHandContainer().at(i);
            blockadeCard->play(deckPtr, playerPtr, territoryPtr);
        }
    } 

    //play the Diplomacy card from hand
    for(int i=0; i<playerPtr->getHand()->getHandContainer().size(); i++)
    {
        if(playerPtr->getHand()->getHandContainer().at(i)->getName() == "Diplomacy Card")
        {
            DiplomacyCard* diploCard = (DiplomacyCard*)playerPtr->getHand()->getHandContainer().at(i);
            diploCard->play(deckPtr, playerPtr, player2Ptr);
        }
    } 

    cout << "Showing orders list contents: " << endl;
    cout << *playerPtr->getPlayerlist();

    cout << "Showing Hand Content:" << endl;
    cout << *playerPtr->getHand();
    delete deckPtr;
    delete orderListPtr;
    delete playerPtr;
    delete player2Ptr;
    delete territoryPtr;
    delete territory2Ptr;
    delete numOfUnits;
    return 0;
}
