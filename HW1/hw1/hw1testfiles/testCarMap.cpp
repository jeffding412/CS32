//
//  testCarMap.cpp
//  hw1
//
//  Created by Jeffrey Ding on 1/19/18.
//  Copyright © 2018 Jeffrey Ding. All rights reserved.
//

#include "CarMap.h"
#include <iostream>
#include <cassert>
using namespace std;

int main()
{
    CarMap m;
    
    //adds five cars to map and checks if they are added
    assert(m.addCar("286 DXW"));
    assert(m.addCar("862 LHY"));
    assert(m.addCar("671 KKV"));
    assert(m.addCar("775 BWB"));
    assert(m.addCar("997 GEW"));
    
    assert(m.fleetSize() == 5);     //checks if there are 5 cars
    assert(!(m.fleetSize() == 4));  //checks if there aren't 4 cars
    
    assert(!m.addCar("862 LHY"));   //checks if car isn't added
    
    assert(m.gas("862 LHY") == 0);  //checks if car has no gas
    assert(m.gas("123") == -1);     //checks if car doesn't exist so it can't have gas
    
    assert(m.addGas("862 LHY", 10.7));    //checks if gas was added
    assert(m.gas("862 LHY") == 10.7);     //checks if car has 10.7 gallons of gas
    
    //adds gas to multiple cars
    m.addGas("286 DXW", 7.4);
    m.addGas("671 KKV", 21.2);
    m.addGas("775 BWB", 17.1);
    m.addGas("997 GEW", 4.8);
    
    assert(m.useGas("671 KKV", 1.7));       //checks if gas is taken out
    assert(m.gas("671 KKV") == 19.5);       //checks if gas is at 19.5 gallons
    assert(m.useGas("286 DXW", 7.4));       //checks if gas is taken out
    assert(m.gas("286 DXW") == 0);          //checks if gas is empty
    assert(!(m.useGas("997 GEW", 5.1)));    //checks if gas can't be used
    assert(m.gas("997 GEW") == 4.8);        //checks if gas is still the same as before
    
    m.print();  //prints out license and gallons of gas
    
    cout << "Passed all tests" << endl;
}