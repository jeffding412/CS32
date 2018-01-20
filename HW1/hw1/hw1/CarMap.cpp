//
//  CarMap.cpp
//  hw1
//
//  Created by Jeffrey Ding on 1/18/18.
//  Copyright © 2018 Jeffrey Ding. All rights reserved.
//

#include "CarMap.h"
#include <iostream>
using namespace std;

// Create an empty car map.
CarMap::CarMap()
{
    
}

// If a car with the given license plate is not currently in the map,
// and there is room in the map, add an entry for that car recording
// that it has 0 gallons of gas in it, and return true.  Otherwise,
// make no change to the map and return false.
bool CarMap::addCar(string license)
{
    if (myCarMap.insert(license, 0))    //if myCarMap adds the car, return true
        return true;
    else                                //if no car is added, return false
        return false;
}

// If a car with the given license plate is in the map, return the
// number of gallons of gas in its tank; otherwise, return -1.
double CarMap::gas(string license) const
{
    double gallons;                         //double gallon to hold gas
    if (myCarMap.get(license, gallons))     //if gallons is given number of gallons of car, return gallons
        return gallons;
    else
        return -1;                          //if car not in map, return -1
}

// If no car with the given license plate is in the map or if
// gallons is negative, make no change to the map and return
// false.  Otherwise, increase the number of gallons of gas in the
// indicated car by the gallons parameter and return true.
bool CarMap::addGas(string license, double gallons)
{
    if (gallons > 0 && myCarMap.update(license, gallons))   //if gallons is postive and the licensed car is updated, return true
        return true;
    else                                                    //if car not in map or gallons is negative, return false
        return false;
}

// If no car with the given license plate is in the map or if
// gallons is negative or if gallons > gas(), make no change to the
// map and return false.  Otherwise, decrease the number of gallons
// of gas in the indicated car by the gallons parameter and return
// true.
bool CarMap::useGas(string license, double gallons)
{
    if (gallons > 0 && gallons <= this->gas(license) && myCarMap.update(license, (this->gas(license)) - gallons))   //if gallons is postive and can be consumed and the licensed car is updated, return true
        return true;
    else                                                                                                            //if car not in map or gallons is negative or can't be consumed, return false
        return false;
}

// Return the number of cars in the CarMap.
int CarMap::fleetSize() const
{
    return myCarMap.size();
}

// Write to cout one line for every car in the map.  Each line
// consists of the car's license plate, followed by one space,
// followed by the number of gallons in that car's tank.  Write
// no other text.
void CarMap::print() const
{
    string license;     //holds license
    double gallons;     //holds gallons of gas
    for (int i = 0; i < this->fleetSize(); i++) {   //iterated through the fleet of cars
        myCarMap.get(i, license, gallons);          //store license and gallons into passed values
        cout << license << " " << gallons << endl;  //prints statement
    }
}
