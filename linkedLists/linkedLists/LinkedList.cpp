//
//  LinkedList.cpp
//  linkedLists
//
//  Created by Jeffrey Ding on 1/24/18.
//  Copyright © 2018 Jeffrey Ding. All rights reserved.
//

#include "LinkedList.h"
#include <iostream>
using namespace std;

LinkedList::LinkedList()
{
    head = nullptr;
    tail = nullptr;
}

LinkedList::~LinkedList()
{
    Node *p;
    p = head;
    while (p != nullptr)
    {
        Node *n = p->next;
        delete p;
        p = n;
    }
}

void LinkedList::addToFront(std::string v)
{
    Node *p;
    p = new Node;
    p->value = v;
    p->next = head;
    
    head = p;
    if(tail == nullptr)
        tail = p;
}

void LinkedList::addToRear(std::string v)
{
    if (this->head == nullptr) {
        this->addToFront(v);
    }
    else
    {
        Node *n = new Node;
        n->value = v;
        tail->next = n;
        n->next = nullptr;
        tail = n;
    }
}

void LinkedList::addItem(std::string v)
{
    if (this->head == nullptr) {
        this->addToFront(v);
    }
    else if (v < head->value)
    {
        this->addToFront(v);
    }
    else
    {
        Node *p = head;
        while (p->next != nullptr) {
            if (v >= p->value && v <= p->next->value)
                break;
            p = p->next;
        }
        Node *latest = new Node;
        latest->value = v;
        latest->next = p->next;
        p->next = latest;
        if (latest->next == nullptr)
            tail = latest;
    }
}

void LinkedList::deleteItem(std::string v)
{
    if (this->head == nullptr)
        return;
        
    if (v == this->head->value) {
        Node *killMe = head;
        head = killMe->next;
        delete killMe;
        return;
    }
    
    Node *p = head;
    while (p->next != nullptr) {
        if (p->next != nullptr && v == p->next->value)
            break;
        p = p->next;
    }
    
    if (p != nullptr) {
        Node *killMe = p->next;
        p->next = killMe->next;
        delete killMe;
    }
}

void LinkedList::printItems()
{
    Node *p;
    p = head;
    while (p != nullptr) {
        cout << p->value << endl;
        p = p->next;
    }
}

bool LinkedList::findItem(std::string v)
{
    Node *p = head;
    while (p != nullptr) {
        if (v == p->value)
            return true;
        p = p->next;
    }
    return false;
}
