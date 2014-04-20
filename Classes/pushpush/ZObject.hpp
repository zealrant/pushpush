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
        return ccp(p.x * Magnification, p.y * Magnification);
    }
  public:
    ZBall(CCLayer* l) : Ball(), ZSprite(l, "Target.png") {
        sprite->setPosition(getCurrentPoint());
    }

    ZBall(CCLayer* l, int x, int y) : Ball(x, y), ZSprite(l, "Target.png") {
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

const float ZBall::MoveSpeed = 0.5;
const int ZBall::Magnification = 30;

};

#endif
