//
//  testMap.cpp
//  hw1
//
//  Created by Jeffrey Ding on 1/19/18.
//  Copyright © 2018 Jeffrey Ding. All rights reserved.
//

#include "Map.h"
#include <iostream>
#include <cassert>
using namespace std;

int main()
{
    Map m;                  // maps strings to doubles
    assert(m.empty());      //checks if Map m is empty
    assert(m.size() == 0);  //checks if Map m is size zero
    
    //adds five keys to Map m and checks if they were added
    assert(m.insert("George", 4.00));
    assert(m.insert("Steve", 2.34));
    assert(m.insert("Roger", 3.17));
    assert(m.insert("Henry", 2.87));
    assert(m.insert("Billy", 3.82));
    
    assert(!m.insert("Steve", 2.11));   //checks if Key isn't added
    
    assert(!m.empty()); //checks if Map m isn't empty
    assert(m.size() == 5); //checks if Map m is size five
    
    assert(m.update("George", 3.91));           //checks if George was updated
    assert(!m.update("Carey", 0.21));           //checks if Carey can't be updated
    assert(m.insertOrUpdate("David", 4.78));    //checks if David was inserted
    assert(m.insertOrUpdate("David", 5.00));    //checks if David was updated
    
    assert(m.size() == 6);  //checks if Map m is size 6
    
    assert(m.erase("Roger"));   //checks if Roger was deleted
    assert(!m.erase("Mark"));   //checks if Mark can't be deleted
    assert(m.contains("David"));    //checks if David is in Map m
    assert(!m.contains("Carey"));   //checks if Carey isn't in Map m
    
    KeyType name;
    ValueType GPA;
    
    assert(m.get("David", GPA) && GPA == 5.00); //checks if GPA has David's value
    
    for (int x = 0; x < m.size(); x++) {
        assert(m.get(x, name, GPA));            //checks if name and GPA have received new values
        switch (x) {
            case 0:
                assert(name == "George" && GPA == 3.91);    //checks if name and GPA match first key
                break;
            case 1:
                assert(name == "Steve" && GPA == 2.34);     //checks if name and GPA match second key
                break;
            case 2:
                assert(name == "David" && GPA == 5.00);     //checks if name and GPA match third key
                break;
            case 3:
                assert(name == "Henry" && GPA == 2.87);     //checks if name and GPA match fourth key
                break;
            case 4:
                assert(name == "Billy" && GPA == 3.82);     //checks if name and GPA match fifth key
                break;
            default:
                break;
        }
    }
    
    assert(m.size() == 5);  //checks if Map m is size 5
    
    Map dykstra644;         //creates new Map
    
    //checks if new keys and values were added
    assert(dykstra644.insert("Jeff", 3.80));
    assert(dykstra644.insert("Matt", 3.85));
    assert(dykstra644.insert("Jeffrey", 3.75));
    
    assert(dykstra644.size() == 3);     //checks if Map dykstra644 is size 3
    
    m.swap(dykstra644);                 //swaps m and dykstra644 content
    
    assert(m.size() == 3);              //checks if m now has dykstra644 size
    assert(dykstra644.size() == 5);     //checks if dykstra644 now has m size
    
    //checks if dykstra644 now has Map m content
    for (int x = 0; x < dykstra644.size(); x++) {
        assert(dykstra644.get(x, name, GPA));            //checks if name and GPA have received new values
        switch (x) {
            case 0:
                assert(name == "George" && GPA == 3.91);    //checks if name and GPA match first key
                break;
            case 1:
                assert(name == "Steve" && GPA == 2.34);     //checks if name and GPA match second key
                break;
            case 2:
                assert(name == "David" && GPA == 5.00);     //checks if name and GPA match third key
                break;
            case 3:
                assert(name == "Henry" && GPA == 2.87);     //checks if name and GPA match fourth key
                break;
            case 4:
                assert(name == "Billy" && GPA == 3.82);     //checks if name and GPA match fifth key
                break;
            default:
                break;
        }
    }
    
    cout << "Passed all tests" << endl;
}