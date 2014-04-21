#ifndef __LEVEL_FACTORY_HPP__
#define __LEVEL_FACTORY_HPP__

#include <vector>
#include <functional>
#include "Level.hpp"

namespace pushpush {

class LevelBuilder {
  private:
    Size size;
    Point posStart;
    std::vector<Point*> houses;
    std::vector<Point*> balls;
    std::vector<Tile*> tiles;
  public:
    virtual ~LevelBuilder() {
        // std::for_each(houses.begin(), houses.end(),
        //               [&](X& item) { delete item; });
    }

    LevelBuilder* setSize(int width, int height) {
        size.width = width;
        size.height = height;
        return this;
    }

    LevelBuilder* setHeroPos(int x, int y) {
        posStart.x = x;
        posStart.y = y;
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

    LevelBuilder* setTiles(unsigned int* layerValues,
                           Tile* (*tileFactory)(int)) {
        for(size_t i = 0; i < size.height; i++) {
            for(size_t j = 0; j < size.width; j++) {
                int value = layerValues[i * size.width + j];
                Tile* t = tileFactory(value);
                tiles.push_back(t);
            }
        }
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
