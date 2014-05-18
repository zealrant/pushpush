#ifndef __PUSHPUSH_ZOBJECTFACTORY_HPP__
#define __PUSHPUSH_ZOBJECTFACTORY_HPP__

#include "ObjectFactory.hpp"
#include "ZObject.hpp"

USING_NS_CC;

namespace pushpush {

class ZObjectFactory : public ObjectFactory {
    static const int InitialX = 8;
    static const int InitialY = 8;
    Layer* layer;
  public:
    ZObjectFactory(Layer* l) : layer(l) {
    }

    virtual Ball* createBall(int x, int y) {
        return new ZBall(layer, x, y);
    }

    virtual House* createHouse(int x, int y) {
        return new ZHouse(layer, x, y);
    }

    virtual Hero* createHero(int x, int y) {
        return new ZHero(layer, x, y);
    }
};

};

#endif
