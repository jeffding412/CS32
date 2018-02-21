#include "Actor.h"
#include "StudentWorld.h"

// Students:  Add code to this file, Actor.h, StudentWorld.h, and StudentWorld.cpp

Actor::Actor(int imageID, double startX, double startY, int dir, double size, int depth, StudentWorld* world)
:GraphObject(imageID, startX, startY, dir, size, depth)
{
    m_world = world;
    m_Status = true;
}

StudentWorld* Actor::getWorld() const
{
    return m_world;
}

bool Actor::isAlive() const
{
    return m_Status;
}

void Actor::setDead()
{
    m_Status = false;
}

Star::Star(double startX, double startY, StudentWorld* world)
:Actor(IID_STAR, startX, startY, 0, 0.01*randInt(5, 50), 3, world)
{}

void Star::move()
{
    moveTo(getX()-1, getY());
    if (getX() <= -1) {
        setDead();
    }
}

void Star::doSomething()
{
    move();
}


