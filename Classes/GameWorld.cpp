#include "GameWorld.h"
#include "PhysicsEngine.h"
#include <fstream>
#include "RawDataUtils.h"

USING_NS_CC;

GameWorld* GameWorld::create(PhysicsEngine *physEngine, std::string const& path)
{
	GameWorld *pRet = new (std::nothrow) GameWorld(physEngine);
	if (pRet && pRet->init(path))
	{
		pRet->autorelease();
	}
	else
	{
		CC_SAFE_DELETE(pRet);
	}
	return pRet;
}

GameWorld::GameWorld(PhysicsEngine *physEngine)
	: m_physEngine(physEngine)
{}

bool GameWorld::init(std::string const& path)
{
	if (!Sprite::initWithFile(path + ".png"))
		return false;

	std::ifstream obsFile(path + ".obs");
	if (!obsFile.is_open())
		return false;

	try
	{
		const size_t blockCnt = RawData::ReadSizeT(obsFile);
		for (size_t i = 0; i < blockCnt; ++i)
		{
			AddRectBlock(RawData::ReadRect(obsFile));
		}
	}
	catch (std::exception const&)
	{
		return false;
	}

	setAnchorPoint(Vec2());
	return true;
}

void GameWorld::AddRectBlock(Rect const& rect)
{
	b2BodyDef bodyDef;
	bodyDef.type = b2_staticBody;
	bodyDef.position.Set(rect.getMidX() / m_physEngine->getPtmRatio(),
		rect.getMidY() / m_physEngine->getPtmRatio());

	b2PolygonShape rectShape;
	rectShape.SetAsBox(rect.size.width / 2 / m_physEngine->getPtmRatio(),
		rect.size.height / 2 / m_physEngine->getPtmRatio());

	b2FixtureDef fixtureDef;
	fixtureDef.shape = &rectShape;
	fixtureDef.density = 1.0f;
	fixtureDef.friction = 0.2f;
	fixtureDef.restitution = 0.0f;

	auto body = m_physEngine->createBody(bodyDef);
	CCASSERT(body, "Can't create body");
	body->CreateFixture(&fixtureDef);
}
