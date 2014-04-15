#ifndef __PUSHPUSH_GAME_HPP__
#define __PUSHPUSH_GAME_HPP__

#include "ZObjectFactory.hpp"

namespace pushpush {

class Game {
    ObjectFactory *objFactory;
    Ball* b;
  public:
    Game() {
    }

    void init(CCLayer* l) {
        // TODO. 레벨 객체에서 처리해야 함
        objFactory = new ZObjectFactory(l);
        b = objFactory->createBall();
        srand(time(NULL));
    }

    void heartbeat() {
        int d = rand() % 4;
        b->move((DIRECT)d);
    }
};

};

#endif
