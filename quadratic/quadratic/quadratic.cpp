//
//  quadratic.cpp
//  quadratic
//
//  Created by Jeffrey Ding on 1/12/18.
//  Copyright © 2018 Jeffrey Ding. All rights reserved.
//

#include "quadratic.h"
#include <iostream>
using namespace std;

quadratic::quadratic(int newA, int newB, int newC)
{
    a = newA;
    b = newB;
    c = newC;
}

quadratic::~quadratic()
{
    cout << "goodbye" << endl;
}

int quadratic::evaluate(int x)
{
    return ((a * x * x) + (b * x) + c);
}
