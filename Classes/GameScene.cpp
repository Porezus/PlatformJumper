#include "GameScene.h"
#include "Physics\PhysicsEngine.h"
#include "GameWorld.h"
#include "Player.h"
#include "InputManager.h"
#include "Bonus\Bonuses.h"
#include "Json\JsonUtils.h"

USING_NS_CC;

Scene* GameScene::createScene(std::string const& mapName)
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();
	if (!scene)
		return nullptr;
	
	// 'layer' is an autorelease object
	auto layer = GameScene::create(mapName);
	if (!layer)
		return nullptr;

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

GameScene* GameScene::create(std::string const& mapName)
{
	GameScene *pRet = new (std::nothrow) GameScene();
	if (pRet && pRet->init(mapName))
	{
		pRet->autorelease();
	}
	else
	{
		CC_SAFE_DELETE(pRet);
	}
	return pRet;
}

GameScene::GameScene()
	: m_cameraSize(Director::getInstance()->getOpenGLView()->getFrameSize())
	, m_targetPosX(0)
{}

// on "init" you need to initialize your instance
bool GameScene::init(std::string const& mapName)
{
	if (!Layer::init())
		return false;

	m_physEngine = PhysicsEngine::create(this, 200);
	if (!m_physEngine)
		return false;

	auto dataJson = JsonUtils::LoadFromFile(mapName + ".dat");
	m_bonusesLeft = dataJson["bonus"].array_items().size();
	m_nextMap = dataJson["nextMap"].string_value();

	m_gameWorld = GameWorld::create(m_physEngine, mapName + ".png", dataJson["world"]);
	if (!m_gameWorld)
		return false;
	addChild(m_gameWorld);

	m_player = Player::create(m_physEngine, dataJson["player"]);
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

void GameScene::update(float dt)
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

void GameScene::onEnter()
{
	Layer::onEnter();
	scheduleUpdate();
}

void GameScene::onExit()
{
	unscheduleUpdate();
	Layer::onExit();
}

Vec2 GameScene::GetPositionInCamera(Vec2 const& scenePos) const
{
	return scenePos + getPosition();
}

float GameScene::BindCameraPositionXWithinMap(float x) const
{
	if (x > 0)
		return 0;

	if (-x + m_cameraSize.width > m_gameWorld->getContentSize().width)
		return -(m_gameWorld->getContentSize().width - m_cameraSize.width);

	return x;
}

float GameScene::BindCameraPositionYWithinMap(float y) const
{
	if (y > 0)
		return 0;

	if (-y + m_cameraSize.height > m_gameWorld->getContentSize().height)
		return -(m_gameWorld->getContentSize().height - m_cameraSize.height);

	return y;
}

void GameScene::LoadNextMap()
{
	if (m_nextMap.empty())
	{
		MessageBox("You've completed the game", "Congratulations!");
		Director::getInstance()->end();
		return;
	}

	auto scene = GameScene::createScene(m_nextMap);
	if (!scene)
	{
		MessageBox("Can't create scene", "Fatal error");
		Director::getInstance()->end();
		return;
	}
	Director::getInstance()->replaceScene(scene);
}

void GameScene::GrabBonus()
{
	CCASSERT(m_bonusesLeft > 0, "There should be some bonus to grab");
	--m_bonusesLeft;

	if (m_bonusesLeft == 0)
		LoadNextMap();
}
