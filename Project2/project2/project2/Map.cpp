//
//  Map.cpp
//  project2
//
//  Created by Jeffrey Ding on 1/24/18.
//  Copyright © 2018 Jeffrey Ding. All rights reserved.
//

#include "Map.h"

//creates an empty Linked List
Map::Map()
{
    head = nullptr;
    tail = nullptr;
    mapSize = 0;
}

//destruct a Linked List
Map::~Map()
{
    Node *p = head;         //Node pointer p points to head
    while (p != nullptr) {  //while pointer p points to a valid pointer
        Node *n = p->next;  //create a Node pointer n that points to the next Node
        delete p;           //delete current Node
        p = n;              //Node pointer p now points to the next Node
    }
}

//returns true if Linked List is empty, false otherwise
bool Map::empty() const
{
    if (size() == 0)
        return true;
    else
        return false;
}

//returns size of the Linked List
int Map::size() const
{
    return mapSize;
}

//returns true if inserts key into Linked List, false otherwise
bool Map::insert(const KeyType& key, const ValueType& value)
{
    if (head == nullptr) {
        Node *p = new Node;
        p->myKey = key;
        p->myValue = value;
        p->next = head;
        p->prev = nullptr;
        head = p;
        mapSize++;
    }
    return true;
}
