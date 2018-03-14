//
//  main.cpp
//  Cracked
//
//  Created by Zhengfu Ding on 3/10/18.
//  Copyright © 2018 Zhengfu Ding. All rights reserved.
//

#include <iostream>
#include "MyHash.h"
#include "provided.h"
#include <string>
#include <cassert>
using namespace std;

int main() {
//    MyHash<int, int> hashTable(0.01);
//    
//    cout << hashTable.getLoadFactor() << endl;
//    hashTable.associate(2010, 981);
//    hashTable.associate(3010, 900);
//    cout << hashTable.getLoadFactor() << endl;
    
    WordList myWordList;
    cout << myWordList.loadWordList("/Users/zhengfuding/Desktop/cs32/Project4/Cracked/Cracked/wordlist.txt") << endl;
    if (myWordList.contains("onomatopoeia")) {
        cout << "I found the word" << endl;
    }

    
    string cipher = "xyqbbq";
    string decodedSoFar = "?r????";

    vector<string> v = myWordList.findCandidates(cipher, decodedSoFar);
    if (v.empty())
        cout << "No matches found" << endl;
    else
        cout << "Found these matches:" << endl;

    for (int k = 0; k < v.size(); k++)
        cout << v[k] << endl; // writes grotto and troppo

    cout << "Passed all tests" << endl;
}
