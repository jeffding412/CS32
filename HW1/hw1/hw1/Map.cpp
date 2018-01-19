//
//  Map.cpp
//  hw1
//
//  Created by Jeffrey Ding on 1/17/18.
//  Copyright © 2018 Jeffrey Ding. All rights reserved.
//

#include "Map.h"

// Create an empty map (i.e., one with no key/value pairs)
Map::Map()
{
    mapSize = 0;    //sets array size to 0
}

// Return true if the map is empty, otherwise false.
bool Map::empty() const
{
    if (mapSize <= 0)   //return true if array is empty, return false if not
        return true;
    else
        return false;
}

// Return the number of key/value pairs in the map.
int Map::size() const
{
    return mapSize;
}

// If key is not equal to any key currently in the map, and if the
// key/value pair can be added to the map, then do so and return true.
// Otherwise, make no change to the map and return false (indicating
// that either the key is already in the map, or the map has a fixed
// capacity and is full).
bool Map::insert(const KeyType& key, const ValueType& value)
{
    if (this->contains(key) && mapSize >= DEFAULT_MAX_ITEMS)    //return false if key is already in the array or if the array is already full
        return false;
    
    myMap[mapSize].myKey = key;         //set current key to key
    myMap[mapSize].myValue = value;     //set current key value to value
    mapSize++;                          //move on to next element of array
    
    return true;
}

// If key is equal to a key currently in the map, then make that key no
// longer map to the value it currently maps to, but instead map to
// the value of the second parameter; return true in this case.
// Otherwise, make no change to the map and return false.
bool Map::update(const KeyType& key, const ValueType& value)
{
    for (int i = 0; i < mapSize; i++)   //iterate through the array
    {
        if (myMap[i].myKey == key)      //if the current element's key is equal to the key passed in
        {
            myMap[i].myValue = value;   //set the element's value to the passed in value
            return true;
        }
    }
    
    return false;                       //if not in array, return false
}

// If key is equal to a key currently in the map, then make that key no
// longer map to the value it currently maps to, but instead map to
// the value of the second parameter; return true in this case.
// If key is not equal to any key currently in the map and if the
// key/value pair can be added to the map, then do so and return true.
// Otherwise, make no change to the map and return false (indicating
// that the key is not already in the map and the map has a fixed
// capacity and is full).
bool Map::insertOrUpdate(const KeyType& key, const ValueType& value)
{
    if (this->update(key, value))       //if the key is updated, return true
        return true;
    else if (this->insert(key, value))  //if the key is inserted, return true
        return true;
    else
        return false;                   //if can't insert or update, return false
}

// If key is equal to a key currently in the map, remove the key/value
// pair with that key from the map and return true.  Otherwise, make
// no change to the map and return false.
bool Map::erase(const KeyType& key)
{
    for (int i = 0; i < mapSize; i++)                       //iterate through the array
    {
        if (myMap[i].myKey == key)                          //if the current element's key is the same as the key passed in
        {
            myMap[i].myKey = myMap[mapSize-1].myKey;        //set the current element's key to the last key
            myMap[i].myValue = myMap[mapSize-1].myValue;    //set the current element's key's value to the last key's value
            mapSize--;                                      //make the map smaller
            return true;
        }
    }
    return false;                                           //if the key isn't found and erased, return false
}

// Return true if key is equal to a key currently in the map, otherwise
// false.
bool Map::contains(const KeyType& key) const        
{
    for (int i = 0; i < mapSize; i++)               //iterate through the array
    {
        if (myMap[i].myKey == key)                  //if the current element's key is equal to the key passed in, return true
            return true;
    }
    
    return false;                                   //if key not in the array, return false
}

// If key is equal to a key currently in the map, set value to the
// value in the map that that key maps to, and return true.  Otherwise,
// make no change to the value parameter of this function and return
// false.
bool Map::get(const KeyType& key, ValueType& value) const
{
    for (int i = 0; i < mapSize; i++)       //iterate through the array
    {
        if (myMap[i].myKey == key)          //if the current element's key is equal to the key passed in
        {
            value = myMap[i].myValue;       //set the value passed in to the key's value and return true
            return true;
        }
    }
    return false;                           //if key not in array, return false
}

// If 0 <= i < size(), copy into the key and value parameters the
// key and value of one of the key/value pairs in the map and return
// true.  Otherwise, leave the key and value parameters unchanged and
// return false.  (See below for details about this function.)
bool Map::get(int i, KeyType& key, ValueType& value) const
{
    if (i < 0 || i >= this->size())     //if i is not in the current array, return false
        return false;
    
    key = myMap[i].myKey;               //set passed in key to key at element i
    value = myMap[i].myValue;           //set passed in value to value at element i
    
    return true;
}

// Exchange the contents of this map with the other one.
void Map::swap(Map& other)
{
    Map temporaryMap;
    for (int i = 0; i < mapSize; i++)
    {
        temporaryMap.myMap[i] = this->myMap[i];
    }
    temporaryMap.mapSize = this->mapSize;
    
    for (int i = 0; i < other.size(); i++)
    {
        this->myMap[i] = other.myMap[i];
    }
    this->mapSize = other.size();
    
    for (int i = 0; i < temporaryMap.size(); i++)
    {
        other.myMap[i] = temporaryMap.myMap[i];
    }
    other.mapSize = temporaryMap.mapSize;
}
