//
//  main.cpp
//  linkedLists
//
//  Created by Jeffrey Ding on 1/24/18.
//  Copyright © 2018 Jeffrey Ding. All rights reserved.
//

#include "LinkedList.h"
#include <iostream>
using namespace std;

int main()
{
    LinkedList myLL;
    myLL.addItem("Louis");
    myLL.addItem("Harry");
    myLL.addItem("Niall");
    myLL.addItem("Zayn");
    myLL.addItem("Liam");
    myLL.printItems();
    
}
