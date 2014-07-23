#ifndef __PUSHPUSH_ZGRAPHIC_HPP__
#define __PUSHPUSH_ZGRAPHIC_HPP__

USING_NS_CC;

#include "LevelFactory.hpp"

namespace pushpush {

class ZSprite {
  protected:
    Sprite* sprite;
    Layer* layer;

    ZSprite(Layer* l, const char* res) : layer(l) {
        sprite = Sprite::create(res);
        layer->addChild(sprite, 0);
    }

  public:
    Sprite* getSprite() {
        return sprite;
    }
};

class HeartBeatLayer : public cocos2d::LayerColor {
  private:
    IHeartbeat *beat;
    IKeyListener *keyListener;
    EventListenerKeyboard* listener;
    EventListenerTouchOneByOne* touchListener;
    Point touchStartPos;

    static const int KEY_LEFT = 4177;
    static const int KEY_UP = 4178;
    static const int KEY_RIGHT = 4179;
    static const int KEY_DOWN = 4180;

  public:
    virtual ~HeartBeatLayer() {
        _eventDispatcher->removeEventListener(listener);
        _eventDispatcher->removeEventListener(touchListener);
        onStopTimer();
    }

    void setupKeyListener(IKeyListener* l) {
        // key listener
        keyListener = l;
        listener = EventListenerKeyboard::create();
        listener->onKeyPressed = CC_CALLBACK_2(HeartBeatLayer::onKeyPressed,
                                               this);
        listener->onKeyReleased = CC_CALLBACK_2(HeartBeatLayer::onKeyReleased,
                                                this);
        _eventDispatcher->addEventListenerWithSceneGraphPriority(listener,
                                                                 this);
        touchListener = EventListenerTouchOneByOne::create();
        touchListener->setSwallowTouches(true);
        touchListener->onTouchBegan = CC_CALLBACK_2(
            HeartBeatLayer::onTouchBegan, this);
        touchListener->onTouchCancelled = CC_CALLBACK_2(
            HeartBeatLayer::onTouchCancelled, this);
        touchListener->onTouchEnded = CC_CALLBACK_2(
            HeartBeatLayer::onTouchEnded, this);

        _eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener,
                                                                 this);
    }

    virtual void onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event) {
        keyListener->onKey((int)keyCode);
    }

    virtual void onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event) {
    }

    virtual bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event) {
        touchStartPos = touch->getLocation();
        return true;
    }

    virtual void onTouchCancelled(cocos2d::Touch* touch, cocos2d::Event* event) {
    }

    virtual void onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* event) {
        Point touchEndPos = touch->getLocation();
        int xDiff = touchStartPos.x - touchEndPos.x;
        int yDiff = touchStartPos.y - touchEndPos.y;
        CCLOG("DIFF : %d, %d", xDiff, yDiff);
        if(abs(xDiff) > 200 && abs(yDiff) > 200) {
            CCLOG("Too large motion");
            return;
        } else if(abs(xDiff) < 80 && abs(yDiff) < 80) {
            CCLOG("Too small motion");
            return;
        } else if(abs(xDiff) > 80) {
            if(xDiff > 0) {
                keyListener->onKey(KEY_LEFT);
            } else {
                keyListener->onKey(KEY_RIGHT);
            }
        } else if(abs(yDiff) > 80) {
            if(yDiff > 0) {
                keyListener->onKey(KEY_DOWN);
            } else {
                keyListener->onKey(KEY_UP);
            }
        }
    }

    void setupHeartBeat(IHeartbeat* b) {
        beat = b;
        onStartTimer();
    }

    void LogicTick(float f) {
        beat->heartbeat();
    }

    void onStartTimer() {
        this->schedule(schedule_selector(HeartBeatLayer::LogicTick), 1.0f);
    }

    void onStopTimer() {
        this->unschedule(schedule_selector(HeartBeatLayer::LogicTick));
    }

    CREATE_FUNC(HeartBeatLayer);
};

class ZScene {
  protected:
    Scene* scene;
    HeartBeatLayer* layer;

  public:
    ZScene(IHeartbeat* beat, IKeyListener* listener) {
        scene = Scene::create();
        layer = HeartBeatLayer::create();
        layer->setupHeartBeat(beat);
        layer->setupKeyListener(listener);
        scene->addChild(layer);
    }

    Scene* getScene() {
        return scene;
    }

    Layer* getLayer() {
        return layer;
    }
};

};

#endif
