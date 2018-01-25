//
//  LinkedList.h
//  linkedLists
//
//  Created by Jeffrey Ding on 1/24/18.
//  Copyright © 2018 Jeffrey Ding. All rights reserved.
//

#ifndef LinkedList_h
#define LinkedList_h

#include <string>

class LinkedList
{
public:
    LinkedList();
    void addToFront(std::string v);
    void addToRear(std::string v);
    void addItem(std::string v);
    void deleteItem(std::string v);
    bool findItem(std::string v);
    void printItems();
    ~LinkedList();
private:
    struct Node
    {
        std::string value;
        Node *next;
    };
    Node *head;
    Node *tail;
};

#endif /* LinkedList_h */
