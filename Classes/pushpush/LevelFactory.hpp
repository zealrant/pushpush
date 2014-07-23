#ifndef __LEVEL_FACTORY_HPP__
#define __LEVEL_FACTORY_HPP__

#include <vector>
#include <functional>
#include "Tiles.hpp"
#include "Object.hpp"
#include "Story.hpp"
#include "Story.hpp"

namespace pushpush {

class IHeartbeat {
  public:
    virtual void heartbeat() = 0;
};

class IKeyListener {
  public:
    virtual void onKey(int keyCode) = 0;
};

class Level {
  private:
    ZSize size;
    StoryFactory* storyFactory;
    std::function<void()> levelDoneCallback;
    ZPoint posStart;
    Hero* hero;
    std::vector<House*> houses;
    std::vector<Ball*> balls;
    std::vector<Tile*> tiles;

    bool inputEnabled;

  private:
    void startInner() {
        inputEnabled = true;
    }

    void finishInner() {
        levelDoneCallback();
    }

  public:
    Level(ZSize s, StoryFactory* sf, std::function<void()> cb, ZPoint p,
          Hero* hero_, std::vector<House*> house, std::vector<Ball*> b,
          std::vector<Tile*> t)
            : size(s), storyFactory(sf), levelDoneCallback(cb), posStart(p),
              hero(hero_), houses(house), balls(b), tiles(t),
              inputEnabled(false) {
        hero->setMoveCallback(std::bind(&Level::checkFinish, this));
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

    void start() {
        Story* story = storyFactory->get(STORY_TYPE::STAGE_INTRO);
        story->tell(std::bind(&Level::startInner, this));
    }


    void finish() {
        inputEnabled = false;
        Story* story = storyFactory->get(STORY_TYPE::STAGE_OUTRO);
        story->tell(std::bind(&Level::finishInner, this));
    }

    Tile* getTileAtPos(int x, int y) {
        return tiles[y * size.width + y];
    }

    Ball* getBallAtPos(int x, int y) {
        Ball* rtn = NULL;
        for_each(balls.begin(), balls.end(), [&rtn, &x, &y] (Ball* b) {
                if(b->getX() == x && b->getY() == y) {
                    rtn = b;
                }
        });
        return rtn;
    }

    void checkFinish() {
        bool finishState = true;
        for(auto b = balls.begin(); b != balls.end(); b++) {
            bool found = false;
            for(auto h = houses.begin(); h != houses.end(); h++) {
                if((*b)->getX() == (*h)->getX() &&
                   (*b)->getY() == (*h)->getY()) {
                    found = true;
                }
            }
            if(!found) {
                finishState = false;
            }
        }
        if(finishState) {
            finish();
        }
    }

    virtual void doKeyEvent(DIRECT d) {
        if(!inputEnabled) {
            return;
        }

        ZPoint moved;
        hero->getMovePoint(&moved, d, 1);
        if(moved.x < 0 || moved.y < 0
           || (size_t)moved.x >= size.width
           || (size_t) moved.y >= size.height) {
            return;
        }

        Tile* tile = getTileAtPos(moved.x, moved.y);
        if(!tile->checkMovable()) {
            return;
        }

        Ball* ball = getBallAtPos(moved.x, moved.y);
        if(ball != NULL) {
            ball->getMovePoint(&moved, d, 1);
            Ball* anotherBall = getBallAtPos(moved.x, moved.y);
            if(anotherBall != NULL) {
                return;
            }
            if(moved.x < 0 || moved.y < 0
               || (size_t) moved.x >= size.width
               || (size_t) moved.y >= size.height) {
                return;
            }
            tile = getTileAtPos(moved.x, moved.y);
            if(!tile->checkMovable()) {
                return;
            }
            ball->move(d);
        }
        hero->move(d);
    }
};

class LevelBuilder {
  private:
    ZSize size;
    ZPoint posStart;
    Hero* hero;
    StoryFactory* storyFactory;
    std::function<void()> levelDoneCallback;
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

    virtual LevelBuilder* setLevelDoneCallback(std::function<void()> cb) {
        levelDoneCallback = cb;
        return this;
    }

    virtual LevelBuilder* setStoryFactory(StoryFactory* sf) {
        storyFactory = sf;
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
        Level* l = new Level(size, storyFactory, levelDoneCallback, posStart,
                             hero, houses, balls, tiles);
        return l;
    }
};

class LevelFactory {
  public:
    virtual Level* createLevel(int levelId) = 0;
};

};

#endif
