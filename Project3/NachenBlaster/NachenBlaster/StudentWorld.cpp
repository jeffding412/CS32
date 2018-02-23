#include "StudentWorld.h"
#include "GameConstants.h"
#include <string>
#include <sstream>  // defines the type std::ostringstream
using namespace std;

GameWorld* createStudentWorld(string assetDir)
{
	return new StudentWorld(assetDir);
}

// Students:  Add code to this file, StudentWorld.h, Actor.h and Actor.cpp

StudentWorld::StudentWorld(string assetDir)
: GameWorld(assetDir)
{
    remainingAliensToKill = 6 + (4 * getLevel());
    number_aliens = 0;
}

StudentWorld::~StudentWorld()
{
    while (getLives() != 0)
    {
        decLives();
    }
    cleanUp();
}

int StudentWorld::init()
{
    m_player = new NachenBlaster(this);
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
    updateStatusLine();
    if (m_player->isAlive()) {
        m_player->doSomething();
    }
    for (int i = 0; i < m_actors.size(); i++) {
        if (m_actors[i]->isAlive()) {
            m_actors[i]->doSomething();
        }
        if (!m_player->isAlive()) {
            return GWSTATUS_PLAYER_DIED;
        }
    }
    if (randInt(1, 15) == 1) {
        addStar();
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

void StudentWorld::addStar()
{
    double x = (double) VIEW_WIDTH-1;
    double y = (double) randInt(0, VIEW_HEIGHT-1);
    m_actors.push_back(new Star(x, y, this));
}

void StudentWorld::killAlien()
{
    remainingAliensToKill--;
}

int StudentWorld::maxAliensOnScreen()
{
    return 4 + (0.5*getLevel());
}

int StudentWorld::getRemainingAliensToKill()
{
    return remainingAliensToKill;
}

void StudentWorld::updateStatusLine()
{
    int healthPercentage = m_player->getHealth() * 2;
    int cabbagePercentage = (m_player->getCabbage() * 100)/30;
    ostringstream oss;  // oss is a name of our choosing.
    oss << "Lives:  " << getLives() << "  Health:  " << healthPercentage << "%  Score:  " << getScore() << "  Level:  " << getLevel() << "  Cabbage:  " << cabbagePercentage << "%  Torpedoes:  " << m_player->getTorpedoes();
    string statusLine = oss.str();
    setGameStatText(statusLine);
}

void StudentWorld::cleanUp()
{
    vector<Actor*>::iterator it;
    it = m_actors.begin();
    while (it != m_actors.end()) {
        delete (*it);
        it = m_actors.erase(it);
    }
    if (getLives() != 0) {
        delete m_player;
    }
}
