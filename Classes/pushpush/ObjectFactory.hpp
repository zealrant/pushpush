#ifndef __PUSHPUSH_OBJECT_FACTORY_HPP__
#define __PUSHPUSH_OBJECT_FACTORY_HPP__

#include "Object.hpp"

namespace pushpush {

class ObjectFactory {
  public:
     virtual Ball* createBall() = 0;
};

};

#endif
