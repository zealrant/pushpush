#ifndef __PUSHPUSH_ZSTORY_FACTORY__
#define __PUSHPUSH_ZSTORY_FACTORY__

#include "Story.hpp"

namespace pushpush {

class ZStory : public Story {
  protected:
    std::function<void()> doneCallback;
  public:
    ZStory() : doneCallback(NULL) {
    }

    virtual void tell() {
    }

    virtual void tell(std::function<void()> c) {
        doneCallback = c;
        tellInner();
    }

    virtual void tellInner() {
    }
};

class ZStoryIntro : public ZStory {
    ZScene* zscene;
    MenuItemFont* textReady;
    MenuItemFont* textGo;
    Sprite* menuBoard;
  public:
    ZStoryIntro(ZScene* s) : zscene(s) {
    }

    virtual void tellInner() {
        // create menu board
        textReady = MenuItemFont::create("Ready~!");
        textGo = MenuItemFont::create("Go~!");
        textGo->setVisible(false);
        Menu* menu = Menu::create(textGo, textReady, NULL);

        menuBoard = Sprite::create("backboard.png");
        menuBoard->addChild(menu, 1);
        zscene->getLayer()->addChild(menuBoard, 1);

        // move to center
        Size s = Director::getInstance()->getWinSize();
        menuBoard->setPosition(0, s.height / 2);

        // Create the actions
        MoveTo* actionIn = MoveTo::create(0.2,
                                          Point(s.width / 2, s.height / 2));
        DelayTime* delayBefore = DelayTime::create(1);
        DelayTime* delayAfter = DelayTime::create(1);
        MoveTo* actionOut = MoveTo::create(0.2,
                                           Point(s.width * 2, s.height / 2));
        CallFunc* introBody = CallFunc::create(
            std::bind(&ZStoryIntro::introBody, this));
        CallFunc* introDone = CallFunc::create(
            std::bind(&ZStoryIntro::introDone, this));

        menuBoard->runAction(Sequence::create(
            actionIn, delayBefore, introBody, delayAfter, actionOut,
            introDone, NULL));
    }

    void introBody() {
        textReady->setVisible(false);
        textGo->setVisible(true);
    }

    void introDone() {
        doneCallback();
    }
};

class ZStoryOutro : public ZStory {
    ZScene* zscene;
    MenuItemFont* textReady;
    MenuItemFont* textGo;
    Sprite* menuBoard;
  public:
    ZStoryOutro(ZScene* s) : zscene(s) {
    }

    virtual void tellInner() {
        // create menu board
        textReady = MenuItemFont::create("Congraturation~!");
        textGo = MenuItemFont::create("Go to next level~!");
        textGo->setVisible(false);
        Menu* menu = Menu::create(textGo, textReady, NULL);

        menuBoard = Sprite::create("backboard.png");
        menuBoard->addChild(menu, 1);
        zscene->getLayer()->addChild(menuBoard, 1);

        // move to center
        Size s = Director::getInstance()->getWinSize();
        menuBoard->setPosition(0, s.height / 2);

        // Create the actions
        MoveTo* actionIn = MoveTo::create(0.2,
                                          Point(s.width / 2, s.height / 2));
        DelayTime* delayBefore = DelayTime::create(1);
        DelayTime* delayAfter = DelayTime::create(1);
        MoveTo* actionOut = MoveTo::create(0.2,
                                           Point(s.width * 2, s.height / 2));
        CallFunc* outroBody = CallFunc::create(
            std::bind(&ZStoryOutro::outroBody, this));
        CallFunc* outroDone = CallFunc::create(
            std::bind(&ZStoryOutro::outroDone, this));

        menuBoard->runAction(Sequence::create(
            actionIn, delayBefore, outroBody, delayAfter, actionOut,
            outroDone, NULL));
    }

    void outroBody() {
        textReady->setVisible(false);
        textGo->setVisible(true);
    }

    void outroDone() {
        doneCallback();
    }
};

class ZStoryFactory : public StoryFactory {
    int levelId;
    ZScene* zscene;

  public:
    ZStoryFactory(ZScene* s, int id) : levelId(id), zscene(s) {
    }

    virtual Story* get(STORY_TYPE type, int storyId) {
        return NULL;
    }

    virtual Story* get(STORY_TYPE type) {
        Story* rtn;
        switch(type) {
            case STAGE_INTRO:
                rtn = new ZStoryIntro(zscene);
                break;
            case STAGE_OUTRO:
                rtn = new ZStoryOutro(zscene);
                break;
            default:
                CCLOG("error case");
                rtn = NULL;
        }
        return rtn;
    }
};

};

#endif

