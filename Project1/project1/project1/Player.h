//
//  Player.h
//  project1
//
//  Created by Jeffrey Ding on 1/11/18.
//  Copyright © 2018 Jeffrey Ding. All rights reserved.
//

#ifndef Player_h
#define Player_h

class City;  // This is needed to let the compiler know that City is a
// type name, since it's mentioned in the Player declaration.

class Player
{
public:
    // Constructor
    Player(City *cp, int r, int c);
    
    // Accessors
    int  row() const;
    int  col() const;
    int  age() const;
    int  health() const;
    bool isPassedOut() const;
    
    // Mutators
    void  preach();
    void  move(int dir);
    void  getGassed();
    
private:
    City* m_city;
    int   m_row;
    int   m_col;
    int   m_health;
    int   m_age;
};

#endif /* Player_h */
