#include <iostream> 
using namespace std; 

#include "Player.h"
#include "Player.cpp"
#include "Map.h"
#include "Map.cpp"

int main() {

    Territory c;
    for(int i =0; i < 2; i++){
        cout<< c.toDefend().at(i)->territory_name <<endl;
    }

    for(int i =0; i < 2; i++){
        cout<< c.toAttack().at(i)->territory_name <<endl;
    }
}