#ifndef __PUSHPUSH_OBJECT_HPP__
#define __PUSHPUSH_OBJECT_HPP__

#include "Util.hpp"

namespace pushpush {

enum DIRECT {
    UP, RIGHT, DOWN, LEFT
};

class Object {
  protected:
    ZPoint p;
  public:
    virtual ~Object() {}
    int getX() {
        return p.x;
    }

    int getY() {
        return p.y;
    }

    bool equals(Object o) {
        return p.x == o.getX() && p.y == o.getY();
    }
};

class Movable : public Object {
  protected:
    virtual ~Movable() {}
    Movable() {
        p.x = 0;
        p.y = 0;
    }

  public:
    Movable(int x, int y) {
        p.x = x;
        p.y = y;
    }

    virtual bool move(DIRECT d, int step) {
        ZPoint z;
        getMovePoint(&z, d, step);
        p.x = z.x;
        p.y = z.y;
        return true;
    }

    void getMovePoint(ZPoint* rtn, DIRECT d, int step) {
        rtn->x = p.x;
        rtn->y = p.y;
        switch(d) {
            case UP:
                rtn->y++;
                break;
            case RIGHT:
                rtn->x++;
                break;
            case DOWN:
                rtn->y--;
                break;
            case LEFT:
                rtn->x--;
                break;
        }
    }

    virtual bool move(DIRECT d) {
        return this->move(d, 1);
    }

    void setPosition(int x, int y) {
        p.x = x;
        p.y = y;
    }
};

class Unmovable : public Object {
  protected:
    virtual ~Unmovable() {}
    Unmovable() {
        p.x = 0;
        p.y = 0;
    }

    Unmovable(int x, int y) {
        p.x = x;
        p.y = y;
    }
};

class Ball : public Movable {
  public:
    virtual ~Ball() {}
    Ball() : Movable() {
    }

    Ball(int x, int y) : Movable(x, y) {
    }
};

class House : public Unmovable {
  public:
    virtual ~House() {}
    House() : Unmovable() {
    }

    House(int x, int y) : Unmovable(x, y) {
    }
};

class Hero : public Movable {
  public:
    Hero() : Movable() {
    }

    Hero(int x, int y) : Movable(x, y) {
    }

    virtual ~Hero() { }
};

};

#endif
