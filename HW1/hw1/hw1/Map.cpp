//
//  Map.cpp
//  hw1
//
//  Created by Jeffrey Ding on 1/17/18.
//  Copyright © 2018 Jeffrey Ding. All rights reserved.
//

#include "Map.h"

Map::Map()
{
    mapSize = 0;
}

bool Map::empty() const
{
    if (mapSize <= 0)
        return true;
    else
        return false;
}

int Map::size() const
{
    return mapSize;
}

bool Map::insert(const std::string& key, const double& value)
{
    if (this->contains(key) && mapSize >= DEFAULT_MAX_ITEMS) {
        return false;
    }
    
    myMap[mapSize].myKey = key;
    myMap[mapSize].myValue = value;
    mapSize++;
    
    return true;
}

bool Map::update(const std::string& key, const double& value)
{
    for (int i = 0; i < mapSize; i++) {
        if (myMap[i].myKey == key) {
            myMap[i].myValue = value;
            return true;
        }
    }
    return false;
}

bool Map::contains(const std::string& key) const
{
    for (int i = 0; i < mapSize; i++) {
        if (myMap[i].myKey == key) {
            return true;
        }
    }
    return false;
}
