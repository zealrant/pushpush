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
    inline Point getCurrentPoint() const {
        return Point(p.x * Magnification, (p.y + 1) * Magnification);
    }
  public:
    ZBall(Layer* l) : Ball(), ZSprite(l, "box.png") {
        sprite->setPosition(getCurrentPoint());
    }

    ZBall(Layer* l, int x, int y) : Ball(x, y), ZSprite(l, "box.png") {
        sprite->setPosition(getCurrentPoint());
    }

    virtual bool move(DIRECT d) {
        if(sprite->getNumberOfRunningActions() == 0 && Ball::move(d)) {
            auto move = MoveTo::create(MoveSpeed, getCurrentPoint());
            auto done = CallFunc::create(CC_CALLBACK_0(ZBall::moveDone, this));
            auto *seq = Sequence::create(move, done, NULL);
            sprite->runAction(seq);
        }
        return true;
    }

    void moveDone() {
        return;
    }
};

class ZHero : public Hero, public ZSprite {
  private:
    static const float MoveSpeed;
    static const int Magnification;
    inline Point getCurrentPoint() const {
        return Point(p.x * Magnification, (p.y + 1) * Magnification);
    }
  public:
    ZHero(Layer* l) : Hero(), ZSprite(l, "forklift.png") {
        sprite->setPosition(getCurrentPoint());
    }

    ZHero(Layer* l, int x, int y) : Hero(x, y), ZSprite(l, "forklift.png") {
        sprite->setPosition(getCurrentPoint());
    }

    virtual bool move(DIRECT d) {
        if(sprite->getNumberOfRunningActions() == 0 && Hero::move(d)) {
            MoveTo* move = MoveTo::create(MoveSpeed, getCurrentPoint());
            CallFunc* done = NULL;
            if(moveCallback != NULL) {
                done = CallFunc::create(moveCallback);
            }
            auto *seq = Sequence::create(move, done, NULL);
            sprite->runAction(seq);
        }
        return true;
    }
};

class ZHouse : public House, public ZSprite {
  private:
    static const int Magnification;
    inline Point getCurrentPoint() const {
        return Point(p.x * Magnification, (p.y + 1) * Magnification);
    }
  public:
    ZHouse(Layer* l) : House(), ZSprite(l, "destination.png") {
        sprite->setPosition(getCurrentPoint());
    }

    ZHouse(Layer* l, int x, int y) : House(x, y),
                                       ZSprite(l, "destination.png") {
        sprite->setPosition(getCurrentPoint());
    }
};

const float ZBall::MoveSpeed = 0.2;
const int ZBall::Magnification = 35;
const float ZHero::MoveSpeed = 0.2;
const int ZHero::Magnification = 35;
const int ZHouse::Magnification = 35;

};

#endif
