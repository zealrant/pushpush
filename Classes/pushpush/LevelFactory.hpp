#ifndef __LEVEL_FACTORY_HPP__
#define __LEVEL_FACTORY_HPP__

#include <vector>
#include "Level.hpp"

namespace pushpush {

class LevelBuilder {
  private:
    Point size;
    Point posStart;
    std::vector<Point*> houses;
    std::vector<Point*> balls;

  public:
    virtual ~LevelBuilder() {
        // std::for_each(houses.begin(), houses.end(),
        //               [&](X& item) { delete item; });
    }

    LevelBuilder* setSize(int width, int height) {
        size.x = width;
        size.y = height;
        return this;
    }

    LevelBuilder* setHeroPos(int x, int y) {
        return this;
    }

    LevelBuilder* addBall(int x, int y) {
        balls.push_back(new Point(x, y));
        return this;
    }

    LevelBuilder* addHouse(int x, int y) {
        houses.push_back(new Point(x, y));
        return this;
    }

    Level* build() {
        return NULL;
    }
};

class LevelFactory {
  public:
    virtual Level* createLevel(int levelId) = 0;
};

};

#endif
