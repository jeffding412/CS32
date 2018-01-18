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
