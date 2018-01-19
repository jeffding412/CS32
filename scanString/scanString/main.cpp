//
//  main.cpp
//  scanString
//
//  Created by Jeffrey Ding on 1/19/18.
//  Copyright © 2018 Jeffrey Ding. All rights reserved.
//

#include <iostream>
#include <string>
using namespace std;

char *search(char *x, char d, int len)
{
    for(int i = 0; *x != '\0'; i++)
    {
        if(*x==d)
            return x;
        x++;
    }
    return NULL;
}

int main()
{
    int len;
    char str[20], ch, *f;
    cout << "Enter two things: ";
    cin >> str >> ch;
    len = strlen(str);
    f = search(str, ch, len);
    if(f != NULL)
        cout << "Character found\n";
    else
        cout << "Character not found\n";
}
