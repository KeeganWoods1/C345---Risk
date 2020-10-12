#include <iostream> 
#include <vector>
#include "Player.cpp"
#include "Map.cpp"
#include "Order.cpp"
#include "Orderlist.cpp"
#include "Cards.cpp"

using namespace std; 

int main() {
    
    // creating a new player with a name
    Player* a = new Player("John");
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
    for(int i =0; i < 4; i++){
        cout<< a->toDefend().at(i)->getTerritoryName() << endl;
    }

    // testing toAttack method
    cout<< "Territories to be attacked: " << endl;
    for(int i = 4; i < 8; i++){
        cout<< a->toAttack().at(i)->getTerritoryName() << endl;
    }

    // testing issueOrder method
    a->issueOrder();

    // deleting created objects to prevent 
    // memory leaks
    delete(a);
    delete(deckOfCards);
    // avoid dangling pointers
    a = NULL;
    deckOfCards = NULL;
}
