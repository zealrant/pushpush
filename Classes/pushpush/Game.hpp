#ifndef __PUSHPUSH_GAME_HPP__
#define __PUSHPUSH_GAME_HPP__

#include "ZObjectFactory.hpp"
#include "ZLevelFactory.hpp"

USING_NS_CC;

namespace pushpush {

class Game {
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
        zscene = new pushpush::ZScene();
        pDirector->runWithScene(zscene->getScene());
        init(zscene->getLayer());
    }

    void init(CCLayer* l) {
        levelFactory = new ZLevelFactory(l);
        level = levelFactory->createLevel(0);

        objFactory = new ZObjectFactory(l);
        ball = objFactory->createBall();
    }

    void heartbeat() {
        int d = rand() % 4;
        ball->move((DIRECT)d);
    }
};

};

#endif
