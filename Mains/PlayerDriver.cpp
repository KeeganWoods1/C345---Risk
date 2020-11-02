#include "Player.h"
#include <iostream> 
#include <vector>
using namespace std; 

int main() {
    
    // creating a new player with a name
    int* numOfUnits = new int(5);
    Player* a = new Player("John");  
    Territory* t1 = new Territory(1, "t1", a, 1);
    Territory* t2 = new Territory(1, "t2", a, 1);  
    Order* advanceorder = new Advanceorder(numOfUnits, a, t1, t2);
    Order* bombOrder = new Bomborder(a, t1);
    cout << endl << "The current number of players in the game: " << a->getPlayerCount() <<endl;
    
    // demonstrating the player owns a collection of territories
    cout << "The current number of territories owned by " << a->getName() << ": " << a->getNumTerrOwned() << endl<<endl;

    // demonstrating the player owns a hand of cards
    // creating a deck and drawing cards for the player to have a hand of 3 cards
    Deck* deckOfCards = new Deck();
    // 1st draw
    deckOfCards->draw(a->getHand(), deckOfCards);
    cout << "The cards owned by " << a->getName() << " after the 1st draw: " << *(a->getHand());
    // 2nd draw
    deckOfCards->draw(a->getHand(), deckOfCards);
    // 3rd draw
    deckOfCards->draw(a->getHand(), deckOfCards);
    cout << endl << "The cards owned by " << a->getName() << " after the 3rd draw: " << endl << *(a->getHand()) << endl;
    
    // testing toDefend method
    cout << "Territories to be defended: " << endl;
    cout << a->toString(a->toDefend()) << endl;

    // testing toAttack method
    cout << "Territories to be attacked: " << endl;
    cout << a->toString(a->toAttack()) << endl;

    cout << "\nDone displaying ToAttack/Defend Territories" << endl;

    // testing issueOrder method
    a->issueOrder(bombOrder);
    a->issueOrder(advanceorder);
}
