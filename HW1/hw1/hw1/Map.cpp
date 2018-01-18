//
//  Map.cpp
//  hw1
//
//  Created by Jeffrey Ding on 1/17/18.
//  Copyright © 2018 Jeffrey Ding. All rights reserved.
//

#include "Map.h"

Map::Map()          //map constructor
{
    mapSize = 0;    //sets array size to 0
}

bool Map::empty() const //checks if map array is empty
{
    if (mapSize <= 0)   //return true if array is empty, return false if not
        return true;
    else
        return false;
}

int Map::size() const   //returns size of the array
{
    return mapSize;
}

bool Map::insert(const KeyType& key, const ValueType& value)   //adds a key into the map array
{
    if (this->contains(key) && mapSize >= DEFAULT_MAX_ITEMS)    //return false if key is already in the array or if the array is already full
    {
        return false;
    }
    
    myMap[mapSize].myKey = key;         //set current key to key
    myMap[mapSize].myValue = value;     //set current key value to value
    mapSize++;
    
    return true;
}

bool Map::update(const KeyType& key, const ValueType& value)
{
    for (int i = 0; i < mapSize; i++) {
        if (myMap[i].myKey == key) {
            myMap[i].myValue = value;
            return true;
        }
    }
    return false;
}

bool Map::contains(const KeyType& key) const
{
    for (int i = 0; i < mapSize; i++) {
        if (myMap[i].myKey == key) {
            return true;
        }
    }
    return false;
}

bool Map::get(const KeyType& key, ValueType& value) const
{
    for (int i = 0; i < mapSize; i++) {
        if (myMap[i].myKey == key) {
            value = myMap[i].myValue;
            return true;
        }
    }
    return false;
}
