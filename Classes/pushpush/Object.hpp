#ifndef __PUSHPUSH_OBJECT_HPP__
#define __PUSHPUSH_OBJECT_HPP__

#include "Util.hpp"

namespace pushpush {

enum DIRECT {
    UP, RIGHT, DOWN, LEFT
};

class Object {
  protected:
    Point p;
};

class Movable : public Object {
  protected:
    virtual bool move(DIRECT d, int step) = 0;
};

class Ball : public Movable {
  public:
    Ball() {
        p.x = 0;
        p.y = 0;
    }

    Ball(int x, int y) {
        p.x = x;
        p.y = y;
    }

    virtual bool move(DIRECT d, int step) {
        switch(d) {
            case UP:
                p.y++;
                break;
            case RIGHT:
                p.x++;
                break;
            case DOWN:
                p.y--;
                break;
            case LEFT:
                p.x--;
                break;
        }
        return true;
    }

    virtual bool move(DIRECT d) {
        return this->move(d, 1);
    }
};

};

#endif
