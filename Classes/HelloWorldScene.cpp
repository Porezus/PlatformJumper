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
	,_inputManager(nullptr)
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
    // 3. add your codes below...

	_world = WorldPhysics::create(Vec2(150, 200), Size(15, 25), 200);
	addChild(_world);
	_world->AddWallRect(Rect(62, 640 - 589, 200, 588 - 556));

	auto overlay = Sprite::create("map.png");
	overlay->setAnchorPoint(Vec2(0, 0));
	this->addChild(overlay);

	_playerSprite = Sprite::create("player.png");
	UpdatePositions();
	addChild(_playerSprite);

	_inputManager = InputManager::create();
	addChild(_inputManager);

	auto eventListener = EventListenerKeyboard::create();
	Director::getInstance()->getOpenGLView()->setIMEKeyboardState(true);
	eventListener->onKeyPressed = [=](EventKeyboard::KeyCode keyCode, Event* event) {
		_inputManager->KeyPressed(keyCode);
	};
	eventListener->onKeyReleased = [=](EventKeyboard::KeyCode keyCode, Event* event) {
		_inputManager->KeyReleased(keyCode);
	};
	this->_eventDispatcher->addEventListenerWithSceneGraphPriority(eventListener, this);

	return true;
}

void HelloWorld::UpdatePositions()
{
	_playerSprite->setPosition(_world->GetPlayerPosition());
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
