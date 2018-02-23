#include "Actor.h"
#include "StudentWorld.h"

// Students:  Add code to this file, Actor.h, StudentWorld.h, and StudentWorld.cpp

///////////////////////////////////////////////////
////////////////////// Actor //////////////////////
///////////////////////////////////////////////////
Actor::Actor(int imageID, double startX, double startY, int dir, double size, int depth, StudentWorld* world)
:GraphObject(imageID, startX, startY, dir, size, depth)
{
    m_id = imageID;
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

int Actor::getImageID() const
{
    return m_id;
}

///////////////////////////////////////////////////
////////////////////// Star ///////////////////////
///////////////////////////////////////////////////
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

///////////////////////////////////////////////////
////////////////////// Ship ///////////////////////
///////////////////////////////////////////////////
Ship::Ship(int imageID, double startX, double startY, int dir, double size, int depth, StudentWorld* world, int startHealth)
:Actor(imageID, startX, startY, dir, size, depth, world)
{
    m_Health = startHealth;
}

int Ship::getHealth()
{
    return m_Health;
}

///////////////////////////////////////////////////
///////////// NachenBlaster ///////////////////////
///////////////////////////////////////////////////
NachenBlaster::NachenBlaster(StudentWorld* world)
:Ship(IID_NACHENBLASTER, 0, 128, 0, 1.0, 0, world, 50)
{
    m_CabbagePoints = 30;
    m_torpedoes = 0;
}

void NachenBlaster::doSomething()
{
    if (isAlive()) {
        if (getWorld()->getKey(m_keyValue)) {
            move();
        }
        if (getCabbage() < 30) {
            m_CabbagePoints++;
        }
    }
}

void NachenBlaster::move()
{
    switch (m_keyValue) {
        case KEY_PRESS_UP:
            if (getY()+6 < VIEW_HEIGHT) {
                moveTo(getX(), getY()+6);
            }
            break;
        case KEY_PRESS_DOWN:
            if (getY()-6 >= 0) {
                moveTo(getX(), getY()-6);
            }
            break;
        case KEY_PRESS_LEFT:
            if (getX()-6 >= 0) {
                moveTo(getX()-6, getY());
            }
            break;
        case KEY_PRESS_RIGHT:
            if (getX()+6 < VIEW_WIDTH) {
                moveTo(getX()+6, getY());
            }
            break;
        case KEY_PRESS_SPACE:
            if (getCabbage() >= 5) {
                m_CabbagePoints -= 5;
                getWorld()->addProjectile(IID_CABBAGE, getX(), getY());
            }
            break;
        case KEY_PRESS_TAB:
            if (getTorpedoes() != 0) {
                m_torpedoes--;
                getWorld()->addProjectile(IID_TORPEDO, getX()+12, getY());
            }
            break;
        default:
            break;
    }
}

int NachenBlaster::getTorpedoes()
{
    return m_torpedoes;
}

void NachenBlaster::addTorpedoes()
{
    m_torpedoes += 5;
}

int NachenBlaster::getCabbage()
{
    return m_CabbagePoints;
}

///////////////////////////////////////////////////
//////////////// Projectile ///////////////////////
///////////////////////////////////////////////////

Projectile::Projectile(int imageID, double startX, double startY, int dir, StudentWorld* world)
:Actor(imageID, startX, startY, dir, 0.5, 1, world)
{}

void Projectile::doSomething()
{
    if (isAlive()) {
        if (isOffScreen()) {
            setDead();
        }
        //todo: collision detection
        move();
        //todo: collision detection
    }
}

bool Projectile::isOffScreen()
{
    if (getX() >= VIEW_WIDTH || getY() < 0) {
        return true;
    }
    return false;
}

///////////////////////////////////////////////////
/////////////////// Cabbage ///////////////////////
///////////////////////////////////////////////////

Cabbage::Cabbage(double startX, double startY, StudentWorld* world)
:Projectile(IID_CABBAGE, startX, startY, 0, world)
{}

void Cabbage::move()
{
    moveTo(getX()+8, getY());
    setDirection(getDirection()+20);
}

///////////////////////////////////////////////////
/////////////////// Torpedo ///////////////////////
///////////////////////////////////////////////////

Torpedo::Torpedo(double startX, double startY, StudentWorld* world)
:Projectile(IID_TORPEDO, startX, startY, 0, world)
{}

void Torpedo::move()
{
    if (getDirection() == 0) {
        moveTo(getX()+8, getY());
    }
    else {
        moveTo(getX()-8, getY());
    }
}
