#include "HelloWorldScene.h"
#include "PhysicsEngine.h"
#include "GameWorld.h"
#include "Player.h"
#include "InputManager.h"

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

	m_player = Player::create(m_physEngine, Vec2(150, 200), Size(15, 25));
	if (!m_player)
		return false;
	addChild(m_player);

	m_inputManager = InputManager::create();
	if (!m_inputManager)
		return false;
	addChild(m_inputManager);

	return true;
}

void HelloWorld::update(float dt)
{
	Layer::update(dt);
	m_physEngine->tick(dt);

	const float MOVE_STEP = 0.06f;
	if (m_inputManager->IsLeft())
	{
		m_player->Move(-MOVE_STEP * dt);
	}
	if (m_inputManager->IsRight())
	{
		m_player->Move(MOVE_STEP * dt);
	}
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
