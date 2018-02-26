#ifndef STUDENTWORLD_H_
#define STUDENTWORLD_H_

#include "GameWorld.h"
#include "Actor.h"
#include <string>
#include <vector>
using namespace std;

// Students:  Add code to this file, StudentWorld.cpp, Actor.h, and Actor.cpp

class StudentWorld : public GameWorld
{
public:
    StudentWorld(std::string assetDir);
    virtual ~StudentWorld();
    virtual int init();
    virtual int move();
    virtual void cleanUp();
    void removeDeadObjects();
    void killAlien();
    void subtractAlien();
    void toAddNewAlien();
    int maxAliensOnScreen();
    int getRemainingAliensToKill();
    void updateStatusLine();
    void addObject(int ID, double startX, double startY);
    int checkCollision(Actor* actor);
    bool canCollide(Actor* actor1, Actor* actor2);
    NachenBlaster* getPlayer() const;
private:
    vector<Actor*> m_actors;
    int remainingAliensToKill;
    int number_aliens;
    NachenBlaster* m_player;
};

#endif // STUDENTWORLD_H_
