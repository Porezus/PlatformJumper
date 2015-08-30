#include "HelloWorldScene.h"
#include "Physics\PhysicsEngine.h"
#include "GameWorld.h"
#include "Player.h"
#include "InputManager.h"
#include "Bonus\Bonuses.h"
#include "Json\JsonUtils.h"

USING_NS_CC;

Scene* HelloWorld::createScene(Destination const& destination)
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();
	if (!scene)
		return nullptr;
	
	// 'layer' is an autorelease object
	auto layer = HelloWorld::create(destination);
	if (!layer)
		return nullptr;

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

HelloWorld* HelloWorld::create(Destination const& destination)
{
	HelloWorld *pRet = new (std::nothrow) HelloWorld();
	if (pRet && pRet->init(destination))
	{
		pRet->autorelease();
	}
	else
	{
		CC_SAFE_DELETE(pRet);
	}
	return pRet;
}

HelloWorld::HelloWorld()
	: m_cameraSize(Director::getInstance()->getOpenGLView()->getFrameSize())
	, m_targetPosX(0)
{}

// on "init" you need to initialize your instance
bool HelloWorld::init(Destination const& destination)
{
	if (!Layer::init())
		return false;

	//Size visibleSize = Director::getInstance()->getVisibleSize();
	//Vec2 origin = Director::getInstance()->getVisibleOrigin();

	m_physEngine = PhysicsEngine::create(this, 200);
	if (!m_physEngine)
		return false;

	auto dataJson = JsonUtils::LoadFromFile(destination.mapName + ".dat");

	m_gameWorld = GameWorld::create(m_physEngine, destination.mapName + ".png", dataJson["world"]);
	if (!m_gameWorld)
		return false;
	addChild(m_gameWorld);

	m_player = Player::create(m_physEngine, destination.position, false);
	if (!m_player)
		return false;
	addChild(m_player);

	auto bonuses = Bonuses::create(m_physEngine, dataJson["bonus"], m_gameWorld->getContentSize().height);
	if (!bonuses)
		return false;
	addChild(bonuses);

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

	const float MOVE_STEP = 0.4f;
	if (m_inputManager->IsLeft())
	{
		m_player->Move(-MOVE_STEP * dt);
	}
	else if (m_inputManager->IsRight())
	{
		m_player->Move(MOVE_STEP * dt);
	}
	else
	{
		m_player->Stop();
	}

	if (m_inputManager->IsJump())
	{
		m_player->Jump();
	}

	const float DEAD_ZONE_WIDTH = m_cameraSize.width * 0.25f;
	if (GetPositionInCamera(m_player->GetSpritePosition()).x < DEAD_ZONE_WIDTH)
	{
		setPositionX(BindCameraPositionXWithinMap(
			getPositionX() + (DEAD_ZONE_WIDTH - GetPositionInCamera(m_player->GetSpritePosition()).x)
		));
	}
	if (GetPositionInCamera(m_player->GetSpritePosition()).x > m_cameraSize.width - DEAD_ZONE_WIDTH)
	{
		setPositionX(BindCameraPositionXWithinMap(
			getPositionX() - (GetPositionInCamera(m_player->GetSpritePosition()).x - (m_cameraSize.width - DEAD_ZONE_WIDTH))
		));
	}

	const float KEEP_VISIBLE_GAP = m_cameraSize.width * 0.7f;
	if (!m_player->IsFacingLeft() && m_cameraSize.width - GetPositionInCamera(m_player->GetSpritePosition()).x < KEEP_VISIBLE_GAP)
	{
		m_targetPosX = BindCameraPositionXWithinMap(
			getPosition().x - (KEEP_VISIBLE_GAP - (m_cameraSize.width - GetPositionInCamera(m_player->GetSpritePosition()).x))
		);
	}
	if (m_player->IsFacingLeft() && GetPositionInCamera(m_player->GetSpritePosition()).x < KEEP_VISIBLE_GAP)
	{
		m_targetPosX = BindCameraPositionXWithinMap(
			getPosition().x + (KEEP_VISIBLE_GAP - GetPositionInCamera(m_player->GetSpritePosition()).x)
		);
	}

	const float CAM_MOVE_STEP = 200.0f;
	if (getPositionX() < m_targetPosX)
	{
		setPositionX(getPositionX() + CAM_MOVE_STEP * dt);
	}
	if (getPositionX() > m_targetPosX)
	{
		setPositionX(getPositionX() - CAM_MOVE_STEP * dt);
	}

	const float UPPER_DEAD_ZONE_HEIGHT = 0.1f * m_cameraSize.height;
	if (m_cameraSize.height - GetPositionInCamera(m_player->GetSpritePosition()).y < UPPER_DEAD_ZONE_HEIGHT)
	{
		setPositionY(BindCameraPositionYWithinMap(
			getPositionY() - (UPPER_DEAD_ZONE_HEIGHT - (m_cameraSize.height - GetPositionInCamera(m_player->GetSpritePosition()).y))
		));
	}
	const float LOWER_DEAD_ZONE_HEIGHT = 0.3f * m_cameraSize.height;
	if (GetPositionInCamera(m_player->GetSpritePosition()).y < LOWER_DEAD_ZONE_HEIGHT)
	{
		setPositionY(BindCameraPositionYWithinMap(
			getPositionY() + (LOWER_DEAD_ZONE_HEIGHT - GetPositionInCamera(m_player->GetSpritePosition()).y)
		));
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

Vec2 HelloWorld::GetPositionInCamera(Vec2 const& scenePos) const
{
	return scenePos + getPosition();
}

float HelloWorld::BindCameraPositionXWithinMap(float x) const
{
	if (x > 0)
		return 0;

	if (-x + m_cameraSize.width > m_gameWorld->getContentSize().width)
		return -(m_gameWorld->getContentSize().width - m_cameraSize.width);

	return x;
}

float HelloWorld::BindCameraPositionYWithinMap(float y) const
{
	if (y > 0)
		return 0;

	if (-y + m_cameraSize.height > m_gameWorld->getContentSize().height)
		return -(m_gameWorld->getContentSize().height - m_cameraSize.height);

	return y;
}

void HelloWorld::ChangeMap(Destination const& destination)
{
	auto scene = HelloWorld::createScene(destination);
	if (!scene)
	{
		MessageBox("Can't create scene", "Fatal error");
		Director::getInstance()->end();
	}
	Director::getInstance()->replaceScene(scene);
}

void HelloWorld::EndGame()
{
	Director::getInstance()->end();
}
