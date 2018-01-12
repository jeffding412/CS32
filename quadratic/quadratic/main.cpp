//
//  main.cpp
//  quadratic
//
//  Created by Jeffrey Ding on 1/12/18.
//  Copyright © 2018 Jeffrey Ding. All rights reserved.
//

#include <iostream>
#include "quadratic.h"
using namespace std;

int main()
{
    quadratic q(4, 3, 5);
    cout << q.evaluate(2) << endl;
}
