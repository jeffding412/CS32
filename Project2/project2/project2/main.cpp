//
//  main.cpp
//  project2
//
//  Created by Jeffrey Ding on 1/24/18.
//  Copyright © 2018 Jeffrey Ding. All rights reserved.
//

#include "Map.h"
#include <iostream>
#include <cassert>
using namespace std;

int main()
{
    //deafult constructor
    Map m1;
    KeyType name;
    ValueType GPA;
    
    assert(m1.size() == 0);             //check if map is empty
    assert(m1.empty());                 //check if map is empty
    assert(!m1.erase("Sahil"));         //map shouldn't erase anything
    assert(!m1.get(1, name, GPA));      //map shouldn't return false because index is larger than list size
    assert(!m1.get(-10, name, GPA));    //map shouldn't return false because index is negative
    
    assert(m1.insert("Louis", 4.21));       //check if inserted
    assert(!m1.update("Niall", 3.87));      //check if can't update
    assert(m1.insert("Niall", 3.98));       //check if inserted
    assert(m1.update("Louis", 4.25));       //check if updated
    assert(m1.size() == 2);                 //size should be two
    assert(!m1.empty());                    //map shouldn't be empty
    assert(m1.get(0, name, GPA));           //check if node was read
    assert(!m1.get(2, name, GPA));          //check if node can't be read
    assert(name == "Louis" && GPA == 4.25); //check if 1st node was used
    
    Map m2 = m1;                                //copy constructs m2 from m1
    assert(m2.size() == 2);                     //check if size is same as m1
    assert(m2.insertOrUpdate("Harry", 2.23));   //check if inserted
    assert(m2.insertOrUpdate("Niall", 3.87));   //check if updated
    assert(m2.get("Niall", GPA));               //check if node is read
    assert(name == "Louis" && GPA == 3.87);     //check if GPA is changed but name isn't
    
    m2 = m1;                            //copies m1 nodes into m2
    assert(m2.size() == 2);             //check if size is same as m1
    assert(m2.insert("Liam", 1.89));    //check if inserted
    assert(m2.insert("Harry", 2.11));   //check if inserted
    assert(m2.insert("Zayn", 3.56));    //check if inserted
    assert(m2.erase("Niall"));          //check if erased
    assert(m2.erase("Louis"));          //check if erased
    assert(m2.size() == 3);             //check if size is 3
    
    Map result;
    assert(result.insertOrUpdate("Ed", 5.00));  //check if inserted
    assert(combine(m1, m2, result));            //check if m1 and m2 were combined into result
    assert(result.size() == 5);                 //check if size is now sum of both
    assert(result.get(0, name, GPA));           //check if node is read
    assert(name == "Louis" && GPA == 4.25);     //check if first node was read
    assert(result.get(2, name, GPA));           //check if node is read
    assert(name == "Liam" && GPA == 1.89);      //check if 3rd node was read
    assert(result.get(4, name, GPA));           //check if final node is read
    assert(name == "Zayn" && GPA == 3.56);      //check if final node was read
    
    assert(m2.erase("Liam"));           //checks if erased
    assert(m2.erase("Harry"));          //checks if erased
    assert(m2.size() == 1);             //checks if List contains only Zayn
    subtract(result, m2, result);       //subtracts m2 from result and puts the resulting list into result
    assert(result.size() == 4);         //check if result only has four nodes
    assert(!result.contains("Zayn"));   //checks if Zayn is no longer part of One Direction
    
    m1.swap(result);            //swaps result and m1
    assert(m1.size() == 4);     //check if m1 is now the size of result
    assert(result.size() == 2); //check if result is now the size of m1
    
    cout << "Passed all tests" << endl;
}
