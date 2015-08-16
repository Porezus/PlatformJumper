#include "HelloWorldScene.h"

USING_NS_CC;

Scene* HelloWorld::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

HelloWorld::HelloWorld()
	:_world(nullptr)
	,_playerSprite(nullptr)
	,_ptmRatio(200)
{}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    // add a "close" icon to exit the progress. it's an autorelease object
    auto closeItem = MenuItemImage::create(
                                           "CloseNormal.png",
                                           "CloseSelected.png",
                                           CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));
    
	closeItem->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width/2 ,
                                origin.y + closeItem->getContentSize().height/2));

    // create menu, it's an autorelease object
    auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);

    /////////////////////////////
    // 3. add your codes below...

	_world = WorldPhysics::create(b2Vec2(150.0 / _ptmRatio, 200.0 / _ptmRatio), Vec2(15.0 / _ptmRatio, 25.0 / _ptmRatio));
	addChild(_world);

	b2PolygonShape block;
	block.SetAsBox(0.5, 0.5 * (90 - 55) / _ptmRatio);
	_world->AddWallPolygon(b2Vec2(0.75, 1.0 * (640 - 575) / _ptmRatio), block);

	auto overlay = Sprite::create("map.png");
	overlay->setAnchorPoint(Vec2(0, 0));
	this->addChild(overlay);

	_playerSprite = Sprite::create("player.png");
	UpdatePositions();
	addChild(_playerSprite);

	return true;
}


void HelloWorld::menuCloseCallback(Ref* pSender)
{
    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}

void HelloWorld::UpdatePositions()
{
	_playerSprite->setPosition(_world->GetPlayerPosition().x * _ptmRatio, _world->GetPlayerPosition().y * _ptmRatio);
}

void HelloWorld::update(float dt)
{
	Layer::update(dt);

	_world->Step(dt);
	UpdatePositions();
}

void HelloWorld::onEnter()
{
	Layer::onEnter();
	scheduleUpdate();
}

void HelloWorld::onExit()
{
	unscheduleUpdate();
	Layer::onExit();
}
