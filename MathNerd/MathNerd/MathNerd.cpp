//
//  MathNerd.cpp
//  MathNerd
//
//  Created by Jeffrey Ding on 1/12/18.
//  Copyright © 2018 Jeffrey Ding. All rights reserved.
//

#include "MathNerd.h"

MathNerd::MathNerd(int newA, int newB)
{
    a = newA;
    b = newB;
}

int MathNerd::getMyValue(int x)
{
    return ((a * x * x) + (b * x));
}
