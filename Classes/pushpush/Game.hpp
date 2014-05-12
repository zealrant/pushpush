#ifndef __PUSHPUSH_GAME_HPP__
#define __PUSHPUSH_GAME_HPP__

#include "ZObjectFactory.hpp"
#include "ZLevelFactory.hpp"

USING_NS_CC;

namespace pushpush {

class Game : public IHeartbeat {
    ObjectFactory *objFactory;
    LevelFactory *levelFactory;
    Ball* ball;
    Level* level;
    ZScene* zscene;

  public:
    Game() {
    }

    void start() {
        CCDirector* pDirector = CCDirector::sharedDirector();
        zscene = new ZScene(this);
        loadLevel(zscene->getLayer(), 0);
        pDirector->runWithScene(zscene->getScene());
    }

    void loadLevel(CCLayer* l, int levelNum) {
        levelFactory = new ZLevelFactory(l);
        level = levelFactory->createLevel(levelNum);
    }

    virtual void heartbeat() {
    }
};

};

#endif
