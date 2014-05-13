#ifndef __PUSHPUSH_ZOBJECT_HPP__
#define __PUSHPUSH_ZOBJECT_HPP__

#include "Object.hpp"
#include "ZGraphic.hpp"

USING_NS_CC;

namespace pushpush {

class ZBall : public Ball, public ZSprite {
  private:
    static const float MoveSpeed;
    static const int Magnification;
    inline CCPoint getCurrentPoint() {
        return ccp(p.x * Magnification, (p.y + 1) * Magnification);
    }
  public:
    ZBall(CCLayer* l) : Ball(), ZSprite(l, "box.png") {
        sprite->setPosition(getCurrentPoint());
    }

    ZBall(CCLayer* l, int x, int y) : Ball(x, y), ZSprite(l, "box.png") {
        sprite->setPosition(getCurrentPoint());
    }

    virtual bool move(DIRECT d) {
        bool rtn = Ball::move(d);
        CCFiniteTimeAction* actionMove =
                CCMoveTo::create(MoveSpeed, getCurrentPoint());
        CCFiniteTimeAction* actionMoveDone =
                CCCallFuncN::create(layer, NULL);
        sprite->runAction(CCSequence::create(
            actionMove, actionMoveDone, NULL));
        return rtn;
    }
};

class ZHero : public Hero, public ZSprite {
  private:
    static const float MoveSpeed;
    static const int Magnification;
    inline CCPoint getCurrentPoint() {
        return ccp(p.x * Magnification, (p.y + 1) * Magnification);
    }
  public:
    ZHero(CCLayer* l) : Hero(), ZSprite(l, "forklift.png") {
        sprite->setPosition(getCurrentPoint());
    }

    ZHero(CCLayer* l, int x, int y) : Hero(x, y), ZSprite(l, "forklift.png") {
        sprite->setPosition(getCurrentPoint());
    }

    virtual bool move(DIRECT d) {
        bool rtn = Hero::move(d);
        CCFiniteTimeAction* actionMove =
                CCMoveTo::create(MoveSpeed, getCurrentPoint());
        CCFiniteTimeAction* actionMoveDone =
                CCCallFuncN::create(layer, NULL);
        sprite->runAction(CCSequence::create(
            actionMove, actionMoveDone, NULL));
        return rtn;
    }
};

class ZHouse : public House, public ZSprite {
  private:
    static const int Magnification;
    inline CCPoint getCurrentPoint() {
        return ccp(p.x * Magnification, (p.y + 1) * Magnification);
    }
  public:
    ZHouse(CCLayer* l) : House(), ZSprite(l, "destination.png") {
        sprite->setPosition(getCurrentPoint());
    }

    ZHouse(CCLayer* l, int x, int y) : House(x, y),
                                       ZSprite(l, "destination.png") {
        sprite->setPosition(getCurrentPoint());
    }
};

const float ZBall::MoveSpeed = 0.5;
const int ZBall::Magnification = 35;

const float ZHero::MoveSpeed = 0.5;
const int ZHero::Magnification = 35;

const int ZHouse::Magnification = 35;

};

#endif
