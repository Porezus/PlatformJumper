#include "GameWorld.h"
#include "PhysicsEngine.h"

USING_NS_CC;

GameWorld* GameWorld::create(PhysicsEngine *physEngine)
{
	GameWorld *pRet = new (std::nothrow) GameWorld(physEngine);
	if (pRet && pRet->init())
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

bool GameWorld::init()
{
	if (!Sprite::initWithFile("map.png"))
		return false;

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
