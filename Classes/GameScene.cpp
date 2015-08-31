#include "GameScene.h"
#include "Physics\PhysicsEngine.h"
#include "GameWorld.h"
#include "Player\Player.h"
#include "InputManager.h"
#include "Bonus\Bonuses.h"
#include "Json\JsonUtils.h"
#include "CameraControl.h"

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
{}

// on "init" you need to initialize your instance
bool GameScene::init(std::string const& mapName)
{
	if (!Layer::init())
		return false;

	m_curMap = mapName;

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

	m_player = Player::create(m_physEngine, dataJson["player"], m_gameWorld->getContentSize().height);
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

	m_cameraControl = std::make_unique<CameraControl>(m_gameWorld->getContentSize());
	return true;
}

void GameScene::update(float dt)
{
	Layer::update(dt);
	m_physEngine->tick(dt);

	const float MOVE_SPEED = 0.14f;
	if (m_inputManager->IsLeft())
	{
		m_player->Move(-MOVE_SPEED * dt);
	}
	else if (m_inputManager->IsRight())
	{
		m_player->Move(MOVE_SPEED * dt);
	}
	else
	{
		m_player->Stop();
	}

	if (m_inputManager->IsJump())
	{
		m_player->Jump();
	}

	m_cameraControl->Update(m_player->GetSpritePosition(), m_player->IsFacingLeft(), dt);
	setPosition(m_cameraControl->GetPosition());

	if (!PlayerIsInsideMap())
		LoadMap(m_curMap);
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

void GameScene::LoadMap(std::string const& mapName)
{
	if (mapName.empty())
	{
		MessageBox("You've completed the game", "Congratulations!");
		Director::getInstance()->end();
		return;
	}

	auto scene = GameScene::createScene(mapName);
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
		LoadMap(m_nextMap);
}

bool GameScene::PlayerIsInsideMap() const
{
	auto pos = m_player->GetSpritePosition();
	auto size = m_gameWorld->getContentSize();
	const float OUT_DEPTH = 100;

	return (pos.x > -OUT_DEPTH && pos.y > -OUT_DEPTH &&
		pos.x < size.width + OUT_DEPTH && pos.y < size.height + OUT_DEPTH);
}
