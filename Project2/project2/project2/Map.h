//
//  Map.h
//  project2
//
//  Created by Jeffrey Ding on 1/24/18.
//  Copyright © 2018 Jeffrey Ding. All rights reserved.
//

#ifndef Map_h
#define Map_h

#include <string>

using KeyType = std::string;
using ValueType = double;

class Map
{
public:
    Map();
    //creates an empty Linked List
    
    Map(const Map &anotherMap);
    //creates a replica of another Linked List
    
    ~Map();
    //destruct a Linked List
    
    Map &operator= (const Map &anotherMap);
    //copies a Linked List into another Linked List
    
    bool empty() const;
    //returns true if Linked List is empty, false otherwise
    
    int size() const;
    //returns size of the Linked List
    
    bool insert(const KeyType& key, const ValueType& value);
    //returns true if inserts key into Linked List, false otherwise
    
    bool update(const KeyType& key, const ValueType& value);
    //returns true if updates key in Linked List, false otherwise
    
    bool insertOrUpdate(const KeyType& key, const ValueType& value);
    //(always) return true if inserts key into or updates key in Linked List
    
    bool erase(const KeyType& key);
    //returns true if key is erased from Linked List, false otherwise
    
    bool contains(const KeyType& key) const;
    //return true if key is in Linked List, false otherwise
    
    bool get(const KeyType& key, ValueType& value) const;
    //return true if key's value in LinkedList is stored into value, false otherwise
    
    bool get(int i, KeyType& key, ValueType& value) const;
    //return true if key and the key's value at index i is stored into key and value, false otherwise
    
    void swap(Map& other);
    //swaps a Linked List with another Linked List
private:
    struct Node {           
        KeyType myKey;
        ValueType myValue;
        Node *prev;
        Node *next;
    };
    Node *head;
    Node *tail;
    int mapSize;
};

#endif /* Map_h */
