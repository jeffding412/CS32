//
//  main.cpp
//  Cracked
//
//  Created by Zhengfu Ding on 3/10/18.
//  Copyright © 2018 Zhengfu Ding. All rights reserved.
//

#include <iostream>
#include "MyHash.h"
#include <string>
using namespace std;

int main() {
    MyHash<int, int> hashTable(0.01);
    
    cout << hashTable.getLoadFactor() << endl;
    hashTable.associate(2010, 981);
    hashTable.associate(3010, 900);
    hashTable.reset();
    cout << hashTable.getLoadFactor() << endl;
    cout << "Passed all tests" << endl;
}
