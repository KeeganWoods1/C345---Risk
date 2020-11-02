#include "Orders.h"
#include <iostream>

using namespace std;


int main() {
    int* numOfTroops = new int(5);
    Player *player1 = new Player("alpha");
    Player *player2 = new Player("beta");
    Territory *madagascar = new Territory(1, "Madagascar", player1, 1);
    Territory *nile = new Territory(1, "Nile", player1, 1);  
    Territory *antartica = new Territory(1, "antartica", player2, 1);
    Territory *penguin = new Territory(1, "penguin", player2, 1);
    Advanceorder *advanceOrder = new Advanceorder(numOfTroops,player1,madagascar,nile);
    Airliftorder *airliftOrder = new Airliftorder(numOfTroops, antartica, penguin, player2);
    Blockadeorder *blockadeOrder = new Blockadeorder(player1, antartica);
    Bomborder *bombOrder = new Bomborder(player2, nile);
    Deployorder *deployOrder = new Deployorder(player1, numOfTroops, nile);
    Negotiateorder *negotiateOrder = new Negotiateorder(player1, player2);
    Reinforcementorder *reinfOrder = new Reinforcementorder(player1);
    Orderlist *orderList1 = new Orderlist();
    Orderlist *orderList2;
    orderList2 = orderList1;
    orderList1->add(advanceOrder);
    orderList1->add(airliftOrder);
    orderList1->add(blockadeOrder);
    orderList1->add(bombOrder);
    orderList1->add(deployOrder);
    orderList1->add(deployOrder);
    orderList1->add(negotiateOrder);
    orderList1->add(reinfOrder);
    cout << *orderList1;
    orderList1->remove(4);
    cout <<"\n"<< *orderList1;
    orderList1->move(4, 2);
    cout << "\n" << *orderList1;
    cout << "\n\nthis is the assignment\n" << *orderList2;
    orderList1->executelist();
    cout << "\n\n" << *orderList1;
    
    return 0;
};