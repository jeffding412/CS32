#include "StudentWorld.h"
#include "GameConstants.h"
#include <string>
#include <sstream>  // defines the type std::ostringstream
#include <cmath>
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
    updateStatusLine();
    if (m_player->isAlive()) {
        m_player->doSomething();
    }
    for (int i = 0; i < m_actors.size(); i++) {
        if (m_actors[i]->isAlive()) {
            m_actors[i]->doSomething();
        }
        if (!m_player->isAlive()) {
            decLives();
            return GWSTATUS_PLAYER_DIED;
        }
        if (getRemainingAliensToKill() == 0) {
            return GWSTATUS_FINISHED_LEVEL;
        }
    }
    if (randInt(1, 15) == 1) {
        addObject(IID_STAR, VIEW_WIDTH-1, randInt(0, VIEW_HEIGHT-1));
    }
    toAddNewAlien();
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

void StudentWorld::killAlien()
{
    remainingAliensToKill--;
    number_aliens--;
}

void StudentWorld::subtractAlien()
{
    number_aliens--;
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

void StudentWorld::addObject(int ID, double startX, double startY)
{
    switch (ID) {
        case IID_CABBAGE:
            m_actors.push_back(new Cabbage(startX+12, startY, this));
            playSound(SOUND_PLAYER_SHOOT);
            break;
        case IID_TORPEDO:
            m_actors.push_back(new Torpedo(startX+12, startY, 0, this));
            playSound(SOUND_TORPEDO);
            break;
        case IID_TURNIP:
            m_actors.push_back(new Turnip(startX-14, startY, this));
            playSound(SOUND_ALIEN_SHOOT);
            break;
        case IID_EXPLOSION:
            m_actors.push_back(new Explosion(startX, startY, this));
            break;
        case IID_LIFE_GOODIE:
            m_actors.push_back(new ExtraLifeGoodie(startX, startY, this));
            break;
        case IID_REPAIR_GOODIE:
            m_actors.push_back(new RepairGoodie(startX, startY, this));
            break;
        case IID_TORPEDO_GOODIE:
            m_actors.push_back(new TorpedoGoodie(startX, startY, this));
            break;
        case IID_STAR:
            m_actors.push_back(new Star(startX, startY, this));
            break;
        case IID_SMALLGON:
            m_actors.push_back(new Smallgon(startX, startY, this));
            number_aliens++;
            break;
        case IID_SMOREGON:
            m_actors.push_back(new Smoregon(startX, startY, this));
            number_aliens++;
            break;
        case IID_SNAGGLEGON:
            m_actors.push_back(new Snagglegon(startX, startY, this));
            number_aliens++;
            break;
        case -1:
            m_actors.push_back(new Torpedo(startX-14, startY, 180, this));
            playSound(SOUND_TORPEDO);
            break;
        default:
            break;
    }
}

void StudentWorld::toAddNewAlien()
{
    int M = maxAliensOnScreen();
    int R = getRemainingAliensToKill();
    int MRmin;
    if (M < R) {
        MRmin = M;
    }
    else {
        MRmin = R;
    }
    if (number_aliens < MRmin)
    {
        int s1 = 60;
        int s2 = 20 + getLevel() * 5;
        int s3 = 5 + getLevel() * 10;
        int s = s1 + s2 + s3;
        int randomInt = randInt(1, s);
        if (randomInt <= s1) {
            addObject(IID_SMALLGON, VIEW_WIDTH-1, randInt(0, VIEW_HEIGHT-1));
        }
        else if (randomInt <= (s1+s2)) {
            addObject(IID_SMOREGON, VIEW_WIDTH-1, randInt(0, VIEW_HEIGHT-1));
        }
        else {
            addObject(IID_SNAGGLEGON, VIEW_WIDTH-1, randInt(0, VIEW_HEIGHT-1));
        }
    }
}

NachenBlaster* StudentWorld::getPlayer() const
{
    return m_player;
}

bool StudentWorld::canCollide(Actor* actor1, Actor* actor2)
{
    int actor1ID = actor1->getImageID();
    int actor2ID = actor2->getImageID();
    switch (actor1ID) {
        case IID_SMALLGON:
        case IID_SMOREGON:
        case IID_SNAGGLEGON:
            switch (actor2ID) {
                case IID_NACHENBLASTER:
                case IID_TORPEDO:
                case IID_CABBAGE:
                    if (actor2ID == IID_TORPEDO && actor2->getDirection() == 180) {
                        return false;
                    }
                    return true;
                    break;
                default:
                    return false;
                    break;
            }
            break;
        case IID_NACHENBLASTER:
            switch (actor2ID) {
                case IID_TURNIP:
                case IID_LIFE_GOODIE:
                case IID_REPAIR_GOODIE:
                case IID_TORPEDO_GOODIE:
                case IID_TORPEDO:
                    if (actor2ID == IID_TORPEDO && actor2->getDirection() == 0) {
                        return false;
                    }
                    return true;
                    break;
                default:
                    return false;
                    break;
            }
            break;
        default:
            return false;
            break;
    }
}

int StudentWorld::checkCollision(Actor* actor)
{
    double x1 = actor->getX();
    double y1 = actor->getY();
    double r1 = actor->getRadius();
    
    double x2;
    double y2;
    double r2;
    
    if (canCollide(actor, getPlayer())) {
        x2 = m_player->getX();
        y2 = m_player->getY();
        r2 = m_player->getRadius();
        double distance = sqrt(pow((x2-x1), 2)+pow((y2-y1), 2));
        if (distance < 0.75*(r1+r2)) {
            return IID_NACHENBLASTER;
        }
    }
    
    if (actor == getPlayer()) {
        for (int i = 0; i < m_actors.size(); i++) {
            if (canCollide(actor, m_actors[i])) {
                x2 = m_actors[i]->getX();
                y2 = m_actors[i]->getY();
                r2 = m_actors[i]->getRadius();
                double distance = sqrt(pow((x2-x1), 2)+pow((y2-y1), 2));
                if (distance < 0.75*(r1+r2)) {
                    switch (m_actors[i]->getImageID()) {
                        case IID_TORPEDO:
                        case IID_TURNIP:
                        case IID_LIFE_GOODIE:
                        case IID_REPAIR_GOODIE:
                        case IID_TORPEDO_GOODIE:
                            m_actors[i]->setDead();
                            break;
                        default:
                            break;
                    }
                    return m_actors[i]->getImageID();
                }
            }
        }
    }
    
    for (int i = 0; i < m_actors.size(); i++) {
        if (m_actors[i] != actor && canCollide(actor, m_actors[i])) {
            x2 = m_actors[i]->getX();
            y2 = m_actors[i]->getY();
            r2 = m_actors[i]->getRadius();
            double distance = sqrt(pow((x2-x1), 2)+pow((y2-y1), 2));
            if (distance < 0.75*(r1+r2)) {
                switch (m_actors[i]->getImageID()) {
                    case IID_TORPEDO:
                    case IID_CABBAGE:
                        m_actors[i]->setDead();
                        break;
                    default:
                        break;
                }
                return m_actors[i]->getImageID();
            }
        }
    }
    
    return -1;
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
    remainingAliensToKill = 6 + (4 * getLevel());
    number_aliens = 0;
}
