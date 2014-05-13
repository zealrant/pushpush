#ifndef __PUSHPUSH_ZOBJECTFACTORY_HPP__
#define __PUSHPUSH_ZOBJECTFACTORY_HPP__

#include "ObjectFactory.hpp"
#include "ZObject.hpp"

USING_NS_CC;

namespace pushpush {

class ZObjectFactory : public ObjectFactory {
    static const int InitialX;
    static const int InitialY;
    CCLayer* layer;
  public:
    ZObjectFactory(CCLayer* l) : layer(l) {
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

const int ZObjectFactory::InitialX = 8;
const int ZObjectFactory::InitialY = 8;

};

#endif
