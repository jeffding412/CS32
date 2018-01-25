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
    myLL.addToFront("dog");
    myLL.addToFront("cat");
    myLL.addToRear("rat");
    myLL.addItem("fly");
    myLL.deleteItem("rat");
    myLL.printItems();
    cout << myLL.findItem("rat") << endl;
}
