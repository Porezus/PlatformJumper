#include "HelloWorldScene.h"
#include "PhysicsEngine.h"
#include "GameWorld.h"
#include "Player.h"

USING_NS_CC;

Scene* HelloWorld::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();
	if (!scene)
		return nullptr;
	
	// 'layer' is an autorelease object
	auto layer = HelloWorld::create();
	if (!layer)
		return nullptr;

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

HelloWorld::HelloWorld()
{}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
	if (!Layer::init())
		return false;

	//Size visibleSize = Director::getInstance()->getVisibleSize();
	//Vec2 origin = Director::getInstance()->getVisibleOrigin();

	m_physEngine = PhysicsEngine::create(this, 200);
	if (!m_physEngine.Keeps())
		return false;

	auto gameWorld = GameWorld::create(m_physEngine);
	if (!gameWorld)
		return false;
	gameWorld->AddRectBlock(Rect(62, 640 - 589, 200, 588 - 556));
	addChild(gameWorld);

	auto player = Player::create(m_physEngine, Vec2(150, 200), Size(15, 25));
	if (!player)
		return false;
	addChild(player);

	return true;
}

void HelloWorld::update(float dt)
{
	Layer::update(dt);
	m_physEngine->tick(dt);
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
