#include "GameWorld.h"
#include "PhysicsEngine.h"
#include <fstream>
#include "Utils.h"

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

	std::string curLine;
	while (std::getline(obsFile, curLine))
	{
		auto parts = SplitString(curLine, " ");
		if (parts.size() != 4)
			return false;

		try
		{
			AddRectBlock(Rect(std::stoi(parts[0]), std::stoi(parts[1]),
				std::stoi(parts[2]), std::stoi(parts[3])));
		}
		catch (std::exception const&)
		{
			return false;
		}
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
