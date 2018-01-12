//
//  main.cpp
//  Cylinder
//
//  Created by Jeffrey Ding on 1/12/18.
//  Copyright © 2018 Jeffrey Ding. All rights reserved.
//

#include <iostream>
#include "Cylinder.cpp"
using namespace std;

int main()
{
    Cylinder c;
    
    c.Initialize(10, 20);
    
    cout << "The volume is: " << c.getVolume();
}
