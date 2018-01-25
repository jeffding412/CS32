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
    myMap.insertOrUpdate("Jeffrey", 3.80);
    myMap.insertOrUpdate("Niall", 3.79);
    myMap.insertOrUpdate("Sahil", 3.79);
    myMap.insertOrUpdate("Jeff", 3.79);
    myMap.insertOrUpdate("Samuel", 3.79);
    cout << myMap.erase("Sahil") << endl;
    cout << myMap.size() << endl;
    cout << myMap.contains("Jeffrey") << endl;
    cout << myMap.contains("Sahil") << endl;
    cout << myMap.empty() << endl;
}
