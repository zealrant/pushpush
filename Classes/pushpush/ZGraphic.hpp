#ifndef __PUSHPUSH_ZGRAPHIC_HPP__
#define __PUSHPUSH_ZGRAPHIC_HPP__

USING_NS_CC;

#include "LevelFactory.hpp"

namespace pushpush {

class ZSprite {
  protected:
    CCSprite* sprite;
    CCLayer* layer;

    ZSprite(CCLayer* l, const char* res) : layer(l) {
        sprite = CCSprite::create(res);
        layer->addChild(sprite, 0);
    }

  public:
    CCSprite* getSprite() {
        return sprite;
    }
};

class HeartBeatLayer : public cocos2d::CCLayer {
  private:
    IHeartbeat *beat;

  public:
    virtual ~HeartBeatLayer() {
        onStopTimer();
    }

    void setupHeartBeat(IHeartbeat* b) {
        beat = b;
        onStartTimer();
    }

    void LogicTick(float f) {
        beat->heartbeat();
    }

    void onStartTimer() {
        CCLOG("%s", __func__);
        this->schedule(schedule_selector(HeartBeatLayer::LogicTick), 1.0f);
    }

    void onStopTimer() {
        CCLOG("%s", __func__);
        this->unschedule(schedule_selector(HeartBeatLayer::LogicTick));
    }


    CREATE_FUNC(HeartBeatLayer);
};

class ZScene {
  protected:
    CCScene* scene;
    HeartBeatLayer* layer;

  public:
    ZScene(IHeartbeat* beat) {
        scene = CCScene::create();
        layer = HeartBeatLayer::create();
        layer->setupHeartBeat(beat);
        scene->addChild(layer);
    }

    CCScene* getScene() {
        return scene;
    }

    CCLayer* getLayer() {
        return layer;
    }
};

};

#endif
