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

    virtual Ball* createBall() {
        return new ZBall(layer, InitialX, InitialY);
    }
};

const int ZObjectFactory::InitialX = 8;
const int ZObjectFactory::InitialY = 8;

};

#endif
