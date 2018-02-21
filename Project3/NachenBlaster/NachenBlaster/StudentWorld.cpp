#include "StudentWorld.h"
#include "GameConstants.h"
#include <string>
using namespace std;

GameWorld* createStudentWorld(string assetDir)
{
	return new StudentWorld(assetDir);
}

// Students:  Add code to this file, StudentWorld.h, Actor.h and Actor.cpp

StudentWorld::StudentWorld(string assetDir)
: GameWorld(assetDir)
{
}

int StudentWorld::init()
{
    for (int i = 0; i < 30; i++) {
        double x = (double) randInt(0, VIEW_WIDTH-1);
        double y = (double) randInt(0, VIEW_HEIGHT-1);
        m_actors.push_back(new Star(x, y, this));
    }
    return GWSTATUS_CONTINUE_GAME;
}

int StudentWorld::move()
{
    // This code is here merely to allow the game to build, run, and terminate after you hit enter.
    // Notice that the return value GWSTATUS_PLAYER_DIED will cause our framework to end the current level.
    decLives();
    for (int i = 0; i < m_actors.size(); i++) {
        if (m_actors[i]->isAlive()) {
            m_actors[i]->doSomething();
        }
    }
    removeDeadObjects();
    return GWSTATUS_CONTINUE_GAME;
}

void StudentWorld::removeDeadObjects()
{
    vector<Actor*>::iterator it;
    it = m_actors.begin();
    while (it != m_actors.end()) {
        if ((*it)->isAlive() == false) {
            delete (*it);
            it = m_actors.erase(it);
        }
        else {
            it++;
        }
    }
}

void StudentWorld::cleanUp()
{
}
