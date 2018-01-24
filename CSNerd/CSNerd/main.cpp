//
//  main.cpp
//  CSNerd
//
//  Created by Jeffrey Ding on 1/24/18.
//  Copyright © 2018 Jeffrey Ding. All rights reserved.
//

#include "CSNerd.h"
#include <iostream>
using namespace std;

int main()
{
    CSNerd a("Jeff");
    CSNerd b("Mark");
    
    a.giveBook("The Intelligent Investor", "Benjamin Graham");
    b.giveBook("The Only Investment Guide You'll Ever Need", "Andrew Tobias");
    a.printBook();
    b.printBook();
    a = b;
    a.printBook();
}
