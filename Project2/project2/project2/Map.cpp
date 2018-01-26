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

//creates a replica of another Linked List
Map::Map(const Map &anotherMap)
{
    mapSize = 0;
    head = nullptr;
    tail = nullptr;

    KeyType anotherKey;
    ValueType anotherValue;
    
    //add the nodes of anotherMap into current Linked List
    for (int x = 0; x < anotherMap.size(); x++) {
        anotherMap.get(x, anotherKey, anotherValue);
        this->insert(anotherKey, anotherValue);
    }
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

//copies a Linked List into another Linked List
Map& Map::operator= (const Map &anotherMap)
{
    if (this != &anotherMap) {  //make no changes if current Linked List is anotherMap
        //traverse the Linked List and delete all nodes
        Node *p = head;
        while (p != nullptr) {
            Node *n = p->next;
            delete p;
            p = n;
        }
        //reset the Linked List
        mapSize = 0;
        head = nullptr;
        tail = nullptr;
        
        KeyType anotherKey;
        ValueType anotherValue;
        
        //add the nodes of anotherMap into current Linked List
        for (int x = 0; x < anotherMap.size(); x++) {
            anotherMap.get(x, anotherKey, anotherValue);
            this->insert(anotherKey, anotherValue);
        }
    }
    return *this;
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
    if (this->contains(key)) {      //if the Linked List contains the key, return false
        return false;
    }
    else {
        Node *n = new Node;         //create a new node
        n->myKey = key;             //set the new node key and value
        n->myValue = value;
        n->next = nullptr;          //put the node at the end of the Linked List
        n->prev = tail;
        
        if (this->empty()) {        //if the Linked List was empty, make the head and tail point to the only node
            head = n;
            tail = n;
        }
        else {                      //if adding node to the end, make the previous node point to the new node and make tail point to the new node
            tail->next = n;
            tail = n;
        }
        

        mapSize++;
        return true;
    }
}

//returns true if updates key in Linked List, false otherwise
bool Map::update(const KeyType& key, const ValueType& value)
{
    Node *p = head;             //make a node pointer that traverses the Linked List
    while (p != nullptr) {
        if (p->myKey == key) {  //if the current node's key is the target key, set it's value to the passed in value
            p->myValue = value;
            return true;
        }
        p = p->next;            //move on to the next node
    }
    return false;
}

//(always) return true if inserts key into or updates key in Linked List
bool Map::insertOrUpdate(const KeyType& key, const ValueType& value)
{
    if (this->update(key, value)) {
        return true;
    }
    return (this->insert(key, value));
}

//returns true if key is erased from Linked List, false otherwise
bool Map::erase(const KeyType& key)
{
    if (this->empty()) {
        return false;
    }
    
    if (head->myKey == key && this->size() == 1) {  //if the Linked List has only one node and it's to be erased, delete the node and set the head and tail to nullptr
        delete head;
        head = nullptr;
        tail = nullptr;
        mapSize--;
        return true;
    }
    
    if (head->myKey == key) {               //if the erased node is the head node
        Node *killMe = head;                //create a Node pointer to the head node
        head->next->prev = killMe->prev;    //set the next node's prev pointer to nullptr
        head = killMe->next;                //set head to the next node
        delete killMe;                      //delete the current node
        mapSize--;
        return true;
    }
    
    if (tail->myKey == key) {               //if the erased node is the tail node
        Node *killMe = tail;                //create a Node pointer to the tail node
        tail->prev->next = killMe->next;    //set the prev node's next pointer to nullptr
        tail = killMe->prev;                //set the tail to the prev node
        delete killMe;                      //delete the current node
        mapSize--;
        return true;
    }
    
    //traverse the Linked List and point to the node above the to be deleted node
    Node *p = head;
    while (p != nullptr) {
        if (p->next != nullptr && p->next->myKey == key) {
            break;
        }
        p = p->next;
    }

    if (p != nullptr) {                     //if pointing to a valid node
        Node *killMe = p->next;             //create a Node pointer to the targeted node
        p->next = killMe->next;             //set the previous node's next pointer to targeted node's next node
        killMe->next->prev = killMe->prev;  //set the next node's prev pointer to the targeted node's prev node
        delete killMe;                      //delete the targeted node
        mapSize--;
        return true;
    }
    
    return false;
}

//return true if key is in Linked List, false otherwise
bool Map::contains(const KeyType& key) const
{
    //traverse the Linked List and return true if the key is in the Linked List
    Node *p = head;
    while (p != nullptr) {
        if (p->myKey == key) {
            return true;
        }
        p = p->next;
    }
    return false;
}

//return true if key's value in LinkedList is stored into value, false otherwise
bool Map::get(const KeyType& key, ValueType& value) const
{
    //traverse the Linked List and if the current node's key is the target key, put key's value into the passed value
    Node *p = head;
    while (p != nullptr) {
        if (p->myKey == key) {
            value = p->myValue;
            return true;
        }
        p = p->next;
    }
    return false;
}

//return true if key and the key's value at index i is stored into key and value, false otherwise
bool Map::get(int i, KeyType& key, ValueType& value) const
{
    if (i < 0 || i >= size()) { //return true if i is negative or i is not accessible
        return false;
    }
    
    Node *p = head;
    for (int x = 0; x < i; x++) {   //goes to the ith node
        p = p->next;
    }
    //stores the current node's key and value into passed parameters
    key = p->myKey;
    value = p->myValue;
    return true;
}

//swaps a Linked List with another Linked List
void Map::swap(Map& other)
{
    Map temp = other;   //Create a temporary Map and copies Map other into it
    other = *this;      //Assigns current Linked List into other
    *this = temp;       //Assigns temporary Map into current Linked List
}
