#ifndef __LEVEL_FACTORY_HPP__
#define __LEVEL_FACTORY_HPP__

#include <vector>
#include <functional>
#include "Tiles.hpp"

namespace pushpush {

class IHeartbeat {
  public:
    virtual void heartbeat() = 0;
};

class Level {
    Size size;
    Point posStart;
    std::vector<Point*> houses;
    std::vector<Point*> balls;
    std::vector<Tile*> tiles;

  public:
    Level(Size s, Point p, std::vector<Point*> h,
          std::vector<Point*> b, std::vector<Tile*> t)
            : size(s), posStart(p), houses(h), balls(b), tiles(t) {
    }

    virtual ~Level() {
        Deletor<Tile> deletorTile;
        for_each(tiles.begin(), tiles.end(), deletorTile);
        for_each(houses.begin(), houses.end(), deletorPoint);
        for_each(balls.begin(), balls.end(), deletorPoint);
    }

    Tile* getTileAtPos(int x, int y) {
        return tiles[y * size.width + y];
    }
};

class LevelBuilder {
  private:
    Size size;
    Point posStart;
    std::vector<Point*> houses;
    std::vector<Point*> balls;
    std::vector<Tile*> tiles;
  public:
    virtual ~LevelBuilder() {
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
        return new Level(size, posStart, houses, balls, tiles);
    }
};

class LevelFactory {
  public:
    virtual Level* createLevel(int levelId) = 0;
};

};

#endif
