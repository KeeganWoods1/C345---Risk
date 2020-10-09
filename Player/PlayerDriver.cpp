#include <iostream> 
#include "Player.cpp"
#include "Map.cpp"
#include "Order.cpp"
#include "Orderlist.cpp"
#include "Card.cpp"
using namespace std; 

int main() {
    
    // setting player's name
    Player* a = new Player();
    cout << "Please enter your name: ";
    string input;
    cin >> input;
    a->setName(input);
    cout << "Hello, player " << a->getName() << endl;
   
    // demonstrating the player owns a collection of territories
    cout << "The current number of territories owned by " << a->getName() << ": " << a->getNumTerrOwned() << endl;

    // testing toDefend method
    Territory c;
    cout << "Territories to be defended: " << endl;
    for(int i =0; i < 2; i++){
        cout<< c.toDefend().at(i)->getTerritoryName() << endl;
    }

    // testing to Attack method
    cout<< "Territories to be attacked: " << endl;
    for(int i =0; i < 2; i++){
        cout<< c.toAttack().at(i)->getTerritoryName() << endl;
    }

    // testing issueOrder method
    
}
