#include <iostream> 
using namespace std; 

#include "Player.h"
#include "Player.cpp"
#include "Map.h"
#include "Map.cpp"

int main() {
    
    // setting player's name
    Player a;
    cout << "Please enter your name: ";
    string input;
    cin >> input;
    a.setName(input);
    cout << "Hello, " << a.getName() << endl;

    // testing toDefend method
    Territory c;
    for(int i =0; i < 2; i++){
        cout<< c.toDefend().at(i)->territory_name <<endl;
    }

    // testing to Attack method
    for(int i =0; i < 2; i++){
        cout<< c.toAttack().at(i)->territory_name <<endl;
    }
}
