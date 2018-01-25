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
    myMap.insert("Jeffrey", 3.80);
    myMap.insert("Sahil", 3.79);
    cout << myMap.size() << endl;
    cout << myMap.contains("Jeffrey") << endl;
    cout << myMap.contains("Sahil") << endl;
    cout << myMap.empty() << endl;
}
