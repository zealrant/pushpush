#ifndef __PUSHPUSH_ZGRAPHIC_HPP__
#define __PUSHPUSH_ZGRAPHIC_HPP__

USING_NS_CC;

namespace pushpush {

class ZSprite {
  protected:
    CCSprite* sprite;
    CCLayer* layer;

    ZSprite(CCLayer* l, const char* res) : layer(l) {
        sprite = CCSprite::create(res);
        layer->addChild(sprite, 0);
    }

  public:
    CCSprite* getSprite() {
        return sprite;
    }
};

};

#endif
