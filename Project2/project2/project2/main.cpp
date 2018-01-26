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
    KeyType Name;
    ValueType GPA;
    myMap.insertOrUpdate("Fred", 1.23);
    myMap.insertOrUpdate("Ethel", 4.56);
    myMap.insertOrUpdate("Lucy", 7.89);
 
    Map anotherMap;
    anotherMap.insertOrUpdate("Lucy", 4.56);
    anotherMap.insertOrUpdate("Rick", 3.21);
    
    Map resultMap;
    resultMap.insertOrUpdate("David", 4.00);
    
    cout << combine(myMap, anotherMap, resultMap) << endl;
    
    for (int x = 0; x <= resultMap.size(); x++) {
        cout << resultMap.get(x, Name, GPA) << " " << Name << " " << GPA << endl;
    }
    cout << resultMap.size() << endl;
}
