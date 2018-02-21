#ifndef ACTOR_H_
#define ACTOR_H_

#include "GraphObject.h"

// Students:  Add code to this file, Actor.cpp, StudentWorld.h, and StudentWorld.cpp

class StudentWorld;

class Actor : public GraphObject
{
public:
    Actor(int imageID, double startX, double startY, int dir, double size, int depth, StudentWorld* world);
    StudentWorld* getWorld() const;
    bool isAlive() const;
    void setDead();
    virtual void doSomething() = 0;
    virtual void move() = 0;
private:
    bool m_Status;
    StudentWorld* m_world;
};

class Star : public Actor
{
public:
    Star(double startX, double startY, StudentWorld* world);
    virtual void doSomething();
    virtual void move();
private:
};

#endif // ACTOR_H_
