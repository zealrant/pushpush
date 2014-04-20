#ifndef __PUSHPUSH_GAME_HPP__
#define __PUSHPUSH_GAME_HPP__

#include "ZObjectFactory.hpp"
#include "ZLevelFactory.hpp"

namespace pushpush {

class Game {
    ObjectFactory *objFactory;
    LevelFactory *levelFactory;
    Ball* ball;
    Level* level;
  public:
    Game() {
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
