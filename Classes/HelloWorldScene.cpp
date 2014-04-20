#include "HelloWorldScene.h"
#include "pushpush/Game.hpp"

USING_NS_CC;

int x = 0;
int y = 100;

pushpush::Game game;


CCScene* HelloWorld::scene()
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // 'layer' is an autorelease object
    HelloWorld *layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !CCLayer::init() )
    {
        return false;
    }
    
    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();

    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    // add a "close" icon to exit the progress. it's an autorelease object
    CCMenuItemImage *pCloseItem = CCMenuItemImage::create(
                                        "CloseNormal.png",
                                        "CloseSelected.png",
                                        this,
                                        menu_selector(HelloWorld::menuCloseCallback));
    
	pCloseItem->setPosition(ccp(origin.x + visibleSize.width - pCloseItem->getContentSize().width/2 ,
                                origin.y + pCloseItem->getContentSize().height/2));

    // create menu, it's an autorelease object
    CCMenu* pMenu = CCMenu::create(pCloseItem, NULL);
    pMenu->setPosition(CCPointZero);
    this->addChild(pMenu, 1);

    /////////////////////////////
    // 3. add your codes below...

    // add a label shows "Hello World"
    // create and initialize a label
    
    CCLabelTTF* pLabel = CCLabelTTF::create("Hello World", "Arial", 24);
    
    // position the label on the center of the screen
    pLabel->setPosition(ccp(origin.x + visibleSize.width/2,
                            origin.y + visibleSize.height - pLabel->getContentSize().height));


    // CCTMXTiledMap* map = CCTMXTiledMap::create("stage1.tmx");
    // this->addChild(map, 0, 100);

    // add the label as a child to this layer
    // this->addChild(pLabel, 1);

    game.init(this);
    onStartTimer();

    return true;
}

void HelloWorld::onStartTimer()
{
    CCLOG("%s", __func__);
    this->schedule(schedule_selector(HelloWorld::LogicTick), 0.0f);
    this->schedule(schedule_selector(HelloWorld::BlockTick), 1.0f);
}

void HelloWorld::onStopTimer()
{
    CCLOG("%s", __func__);
    this->unschedule(schedule_selector(HelloWorld::LogicTick));
    this->unschedule(schedule_selector(HelloWorld::BlockTick));
}

void HelloWorld::LogicTick(float f)
{
    // CCLOG("%s", __func__);
}

void HelloWorld::BlockTick(float f)
{
    game.heartbeat();
    CCLOG("%s", __func__);
}


void HelloWorld::menuCloseCallback(CCObject* pSender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT) || (CC_TARGET_PLATFORM == CC_PLATFORM_WP8)
	CCMessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
#else
    CCDirector::sharedDirector()->end();
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
#endif
}
