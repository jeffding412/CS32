//
//  testnewMap.cpp
//  hw1
//
//  Created by Jeffrey Ding on 1/20/18.
//  Copyright © 2018 Jeffrey Ding. All rights reserved.
//

#include "newMap.h"
#include <iostream>
#include <cassert>
using namespace std;

int main()
{
    Map a(5);   //a can hold at most 5 key/value pairs
    Map b;      //b can hold the max number of key/value pairs
    
    //insert 5 keys into a
    assert(a.insert("George", 4.00));
    assert(a.insert("Kenny", 3.43));
    assert(a.insert("Mark", 3.21));
    assert(a.insert("Steve", 3.87));
    assert(a.insert("Mike", 2.87));
    
    assert(!a.insert("Adam", 2.11));    //checks if a can't insert 6th key
    
    
    //insert 2 keys into b
    assert(b.insert("Adam", 2.11));
    assert(b.insert("David", 4.98));
    
    //copy constructor
    Map c(b);                           //c is the same as b
    assert(!c.insert("Adam", 2.11));    //checks if c can't insert key
    assert(!c.insert("David", 5.00));   //checks if c can't insert key
    
    //assignment operator
    c = a;                              //c is the same as a
    assert(c.update("George", 3.99));   //checks if c updates key
    assert(!c.insert("Carey", 1.87));   //checks if c can't insert key
    
    //swap a and b
    a.swap(b);                          //a has b and b has a
    assert(a.insert("Carey", 1.78));    //checks if a inserts key
    assert(!b.insert("Carey", 1.22));   //checks if b can't insert key
    assert(b.update("Mark", 2.98));     //checks if b updates key
    assert(a.update("Adam", 2.98));     //checks if a updates key
    
    cout << "Passed all tests" << endl;
}
