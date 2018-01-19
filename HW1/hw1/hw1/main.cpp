//
//  main.cpp
//  hw1
//
//  Created by Jeffrey Ding on 1/17/18.
//  Copyright © 2018 Jeffrey Ding. All rights reserved.
//

#include <iostream>
#include <cassert>
#include "Map.h"
using namespace std;

int main()
{
    string name = "None";
    double value = 0;
    Map m1;
    m1.insert("Fred", 2.956);
    Map m2;
    m2.insert("Ethel", 3.538);
    m2.insert("Lucy", 2.956);
    m1.swap(m2);
    
    m2.get(1, name, value);
    cout << name << " " << value << endl;
}
