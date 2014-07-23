#ifndef __PUSHPUSH_GAME_HPP__
#define __PUSHPUSH_GAME_HPP__

#include "ZObjectFactory.hpp"
#include "ZLevelFactory.hpp"
#include "ZStory.hpp"

USING_NS_CC;

namespace pushpush {

class Game : public IHeartbeat, public IKeyListener {
    ObjectFactory *objFactory;
    LevelFactory *levelFactory;
    Level* level;
    ZScene* zscene;
    int levelIndex;
    std::function<void()> levelDoneCallback;

  public:
    static const int KEY_LEFT = 4177;
    static const int KEY_UP = 4178;
    static const int KEY_RIGHT = 4179;
    static const int KEY_DOWN = 4180;

    Game() : level(NULL), levelIndex(0) {
        levelDoneCallback = std::bind(&Game::doneLevel, this);
    }

    void start() {
        Director* pDirector = Director::getInstance();
        zscene = new ZScene(this, this);
        pDirector->runWithScene(zscene->getScene());
        level = loadLevel(zscene, levelIndex);
        level->start();
    }

    Level* loadLevel(ZScene* s, int levelIndex) {
        StoryFactory* sf = new ZStoryFactory(s, levelIndex);
        levelFactory = new ZLevelFactory(s->getLayer(), sf, levelDoneCallback);
        return levelFactory->createLevel(levelIndex);
    }

    virtual void doneLevel() {
        CCLOG("LevelDone!");
        levelIndex++;
        Director* pDirector = Director::getInstance();
        ZScene* newScene = new ZScene(this, this);
        auto transition = TransitionFade::create(1.0f, newScene->getScene());
        pDirector->replaceScene(transition);
        level = loadLevel(newScene, levelIndex);
        level->start();
        delete zscene;
        zscene = newScene;
    }

    virtual void heartbeat() {
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
        } else {
            CCLOG("Level is null");
        }
    }
};

};

#endif
