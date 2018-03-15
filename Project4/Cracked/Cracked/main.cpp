//
//  main.cpp
//  Cracked
//
//  Created by Zhengfu Ding on 3/10/18.
//  Copyright © 2018 Zhengfu Ding. All rights reserved.
//

#include "provided.h"
#include <iostream>
#include <string>
using namespace std;

int main() {
//    MyHash<int, int> hashTable(0.01);
//    
//    cout << hashTable.getLoadFactor() << endl;
//    hashTable.associate(2010, 981);
//    hashTable.associate(3010, 900);
//    cout << hashTable.getLoadFactor() << endl;
    
//    WordList myWordList;
//    cout << myWordList.loadWordList("/Users/zhengfuding/Desktop/cs32/Project4/Cracked/Cracked/wordlist.txt") << endl;

    
//    Translator t;
//    cout << t.pushMapping("DHL", "ERD") << endl;
//    string secret = "Hdqlx!";
//    cout << t.getTranslation(secret) << endl;
//    t.pushMapping("QX", "AY"); // Q->A, X->Y
//    cout << t.getTranslation(secret) << endl;
//    t.popMapping();
//    cout << t.getTranslation(secret) << endl;
//    t.popMapping();
//    cout << t.getTranslation(secret) << endl;
    Decrypter myDecrypter;
    cout << myDecrypter.load("/Users/zhengfuding/Desktop/cs32/Project4/Cracked/Cracked/wordlist.txt") << endl;

//    myDecrypter.crack("Vxgvab sovi jh pjhk cevc andi ngh iobnxdcjnh cn bdttook jb pnio jpfnicvhc cevh vha nceoi nho cejhy.");
    myDecrypter.crack("y qook ra bdttook yqkook.");
    cout << "Passed all tests" << endl;
}
