#ifndef __PUSHPUSH_ZOBJECTFACTORY_HPP__
#define __PUSHPUSH_ZOBJECTFACTORY_HPP__

#include "ObjectFactory.hpp"
#include "ZObject.hpp"

USING_NS_CC;

namespace pushpush {

class ZObjectFactory : public ObjectFactory {
    Layer* layer;
    int initialX;
    int initialY;
  public:
    ZObjectFactory(Layer* l, int initX, int initY)
            : layer(l), initialX(initX), initialY(initY) {
    }

    virtual Ball* createBall(int x, int y) {
        return new ZBall(layer, x, y, initialX, initialY);
    }

    virtual House* createHouse(int x, int y) {
        return new ZHouse(layer, x, y, initialX, initialY);
    }

    virtual Hero* createHero(int x, int y) {
        return new ZHero(layer, x, y, initialX, initialY);
    }
};

};

#endif
