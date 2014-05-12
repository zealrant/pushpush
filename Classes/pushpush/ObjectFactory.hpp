#ifndef __PUSHPUSH_OBJECT_FACTORY_HPP__
#define __PUSHPUSH_OBJECT_FACTORY_HPP__

#include "Object.hpp"

namespace pushpush {

class ObjectFactory {
  public:
    virtual Ball* createBall(int x, int y) = 0;
    virtual House* createHouse(int x, int y) = 0;
    virtual Hero* createHero(int x, int y) = 0;
};

};

#endif
