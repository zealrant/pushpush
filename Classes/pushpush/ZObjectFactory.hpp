#ifndef __PUSHPUSH_ZOBJECTFACTORY_HPP__
#define __PUSHPUSH_ZOBJECTFACTORY_HPP__

#include "ObjectFactory.hpp"
#include "ZObject.hpp"

USING_NS_CC;

namespace pushpush {

class ZObjectFactory : public ObjectFactory {
    const int InitialX;
    const int InitialY;
    CCLayer* layer;
  public:
    ZObjectFactory(CCLayer* l) : layer(l), InitialX(8), InitialY(8) {
    }

    virtual Ball* createBall() {
        return new ZBall(layer, InitialX, InitialY);
    }
};

};

#endif
