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
  public:
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
    Movable() {
        p.x = 0;
        p.y = 0;
    }

    Movable(int x, int y) {
        p.x = x;
        p.y = y;
    }

    virtual bool move(DIRECT d, int step) = 0;
};

class Unmovable : public Object {
  protected:
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
    Ball() : Movable() {
    }

    Ball(int x, int y) : Movable(x, y) {
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

class House : public Unmovable {
  public:
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

    void setPosition(int x, int y) {
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
