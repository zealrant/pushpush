#ifndef __PUSHPUSH_GAME_HPP__
#define __PUSHPUSH_GAME_HPP__

#include "ZObjectFactory.hpp"
#include "ZLevelFactory.hpp"

USING_NS_CC;

namespace pushpush {

class Game : public IHeartbeat, public IKeyListener {
    ObjectFactory *objFactory;
    LevelFactory *levelFactory;
    Level* level;
    ZScene* zscene;
    static const int KEY_LEFT = 4177;
    static const int KEY_UP = 4178;
    static const int KEY_RIGHT = 4179;
    static const int KEY_DOWN = 4180;

  public:
    Game() : level(NULL) {
    }

    void start() {
        Director* pDirector = Director::getInstance();
        zscene = new ZScene(this, this);
        loadLevel(zscene->getLayer(), 0);
        pDirector->runWithScene(zscene->getScene());
    }

    void loadLevel(Layer* l, int levelNum) {
        levelFactory = new ZLevelFactory(l);
        level = levelFactory->createLevel(levelNum);
    }

    virtual void heartbeat() {
    }

    virtual void checkFinish() {
        if(level->checkFinish()) {
        }
    }

    virtual void onKey(int keyCode) {
        if(level != NULL) {
            switch(keyCode) {
                case KEY_UP:
                    level->doKeyEvent(DIRECT::UP);
                    break;
                case KEY_RIGHT:
                    level->doKeyEvent(DIRECT::RIGHT);
                    break;
                case KEY_DOWN:
                    level->doKeyEvent(DIRECT::DOWN);
                    break;
                case KEY_LEFT:
                    level->doKeyEvent(DIRECT::LEFT);
                    break;
            }
            checkFinish();
        } else {
            CCLOG("Level is null");
        }
    }
};

};

#endif
