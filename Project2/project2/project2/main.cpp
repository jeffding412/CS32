//
//  main.cpp
//  project2
//
//  Created by Jeffrey Ding on 1/24/18.
//  Copyright © 2018 Jeffrey Ding. All rights reserved.
//

#include "Map.h"
#include <iostream>
using namespace std;

int main()
{
    Map myMap;
    KeyType Name = "John";
    ValueType GPA = 1.00;
    myMap.insertOrUpdate("Jeffrey", 3.80);
    myMap.insertOrUpdate("Niall", 4.00);
    myMap.insertOrUpdate("Sahil", 3.79);
    myMap.insertOrUpdate("Jeff", 3.67);
    myMap.insertOrUpdate("Samuel", 3.21);
    
    Map anotherMap = myMap;
    
    cout << anotherMap.get(0, Name, GPA) << " " << Name << " " << GPA << endl;
    cout << anotherMap.get(1, Name, GPA) << " " << Name << " " << GPA << endl;
    cout << anotherMap.get(2, Name, GPA) << " " << Name << " " << GPA << endl;
    cout << anotherMap.get(3, Name, GPA) << " " << Name << " " << GPA << endl;
    cout << anotherMap.get(4, Name, GPA) << " " << Name << " " << GPA << endl;
    cout << anotherMap.size() << endl;
}
