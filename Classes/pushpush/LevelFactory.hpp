#ifndef __LEVEL_FACTORY_HPP__
#define __LEVEL_FACTORY_HPP__

#include <vector>
#include <functional>
#include "Tiles.hpp"
#include "Object.hpp"

namespace pushpush {

class IHeartbeat {
  public:
    virtual void heartbeat() = 0;
};

class Level {
    Size size;
    Point posStart;
    Hero* hero;
    std::vector<House*> houses;
    std::vector<Ball*> balls;
    std::vector<Tile*> tiles;

  public:
    Level(Size s, Point p, Hero* hero_, std::vector<House*> house,
          std::vector<Ball*> b, std::vector<Tile*> t)
            : size(s), posStart(p), hero(hero_), houses(house), balls(b),
              tiles(t) {
    }

    virtual ~Level() {
        Deletor<Tile> deletorTile;
        for_each(tiles.begin(), tiles.end(), deletorTile);

        Deletor<House> deletorHouse;
        for_each(houses.begin(), houses.end(), deletorHouse);

        Deletor<Ball> deletorBall;
        for_each(balls.begin(), balls.end(), deletorBall);

        delete hero;
    }

    Tile* getTileAtPos(int x, int y) {
        return tiles[y * size.width + y];
    }
};

class LevelBuilder {
  private:
    Size size;
    Point posStart;
    Hero* hero;
    std::vector<House*> houses;
    std::vector<Ball*> balls;
    std::vector<Tile*> tiles;
  public:
    LevelBuilder() : hero(NULL) {
    }

    virtual ~LevelBuilder() {
    }

    LevelBuilder* setSize(int width, int height) {
        size.width = width;
        size.height = height;
        return this;
    }

    virtual LevelBuilder* setHero(Hero* h) {
        hero = h;
        return this;
    }

    virtual LevelBuilder* setHeroPos(int x, int y) {
        if(hero != NULL) {
            hero->setPosition(x, y);
            posStart.set(x, y);
        }
        return this;
    }

    virtual LevelBuilder* addBall(Ball* b) {
        balls.push_back(b);
        return this;
    }

    virtual LevelBuilder* addHouse(House* h) {
        houses.push_back(h);
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
        return new Level(size, posStart, hero, houses, balls, tiles);
    }
};

class LevelFactory {
  public:
    virtual Level* createLevel(int levelId) = 0;
};

};

#endif
