//
//  main.cpp
//  swap
//
//  Created by Jeffrey Ding on 1/16/18.
//  Copyright © 2018 Jeffrey Ding. All rights reserved.
//

#include <iostream>
using namespace std;

void swap(int *r, int *s)
{
    int temp = *r;
    *r = *s;
    *s = temp;
}

int main()
{
    int a = 5, b = 6;
    
    swap(&a, &b);
    cout << a << endl; //print 6
    cout << b << endl; //print 5
}
