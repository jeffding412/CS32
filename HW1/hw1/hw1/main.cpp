//
//  main.cpp
//  hw1
//
//  Created by Jeffrey Ding on 1/17/18.
//  Copyright © 2018 Jeffrey Ding. All rights reserved.
//

#include <iostream>
#include "Map.h"
using namespace std;

int main()
{
    Map newMap;
    string name = "George";
    double GPA = 3.99;
    newMap.insert(name, GPA);
    cout << newMap.contains("George") << endl;
}
