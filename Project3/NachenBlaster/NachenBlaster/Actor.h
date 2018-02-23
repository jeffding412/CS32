#ifndef ACTOR_H_
#define ACTOR_H_

#include "GraphObject.h"

// Students:  Add code to this file, Actor.cpp, StudentWorld.h, and StudentWorld.cpp

class StudentWorld;

///////////////////////////////////////////////////
///////////////////// Actor ///////////////////////
///////////////////////////////////////////////////
class Actor : public GraphObject
{
public:
    Actor(int imageID, double startX, double startY, int dir, double size, int depth, StudentWorld* world);
    StudentWorld* getWorld() const;
    bool isAlive() const;
    void setDead();
    virtual void doSomething() = 0;
    virtual void move() = 0;
    int getImageID() const;
private:
    bool m_Status;
    StudentWorld* m_world;
    int m_id;
};

///////////////////////////////////////////////////
////////////////////// Star ///////////////////////
///////////////////////////////////////////////////
class Star : public Actor
{
public:
    Star(double startX, double startY, StudentWorld* world);
    virtual void doSomething();
    virtual void move();
private:
};

///////////////////////////////////////////////////
////////////////////// Ship ///////////////////////
///////////////////////////////////////////////////
class Ship : public Actor
{
public:
    Ship(int imageID, double startX, double startY, int dir, double size, int depth, StudentWorld* world, int startHealth);
    virtual void doSomething() = 0;
    virtual void move() = 0;
    int getHealth();
private:
    int m_Health;
};

///////////////////////////////////////////////////
///////////// NachenBlaster ///////////////////////
///////////////////////////////////////////////////
class NachenBlaster : public Ship
{
public:
    NachenBlaster(StudentWorld* world);
    virtual void doSomething();
    virtual void move();
    int getTorpedoes();
    void addTorpedoes();
    int getCabbage();
private:
    int m_CabbagePoints;
    int m_torpedoes;
    int m_keyValue;
};

///////////////////////////////////////////////////
//////////////// Projectile ///////////////////////
///////////////////////////////////////////////////

class Projectile : public Actor
{
public:
    Projectile(int imageID, double startX, double startY, int dir, StudentWorld* world);
    virtual void doSomething();
    virtual void move() = 0;
    bool isOffScreen();
private:
};

///////////////////////////////////////////////////
/////////////////// Cabbage ///////////////////////
///////////////////////////////////////////////////

class Cabbage : public Projectile
{
public:
    Cabbage(double startX, double startY, StudentWorld* world);
    virtual void move();
private:
};

///////////////////////////////////////////////////
/////////////////// Torpedo ///////////////////////
///////////////////////////////////////////////////

class Torpedo : public Projectile
{
public:
    Torpedo(double startX, double startY, StudentWorld* world);
    virtual void move();
private:
};

#endif // ACTOR_H_
