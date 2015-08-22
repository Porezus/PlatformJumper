#include "Player.h"
#include "PhysicsEngine.h"
#include "NodePhysicsPuppeteer.h"

USING_NS_CC;

Player* Player::create(PhysicsEngine *physEngine, Vec2 const& origin, Size const& size)
{
	Player *pRet = new (std::nothrow) Player(physEngine);
	if (pRet && pRet->init(origin, size))
	{
		pRet->autorelease();
	}
	else
	{
		CC_SAFE_DELETE(pRet);
	}
	return pRet;
}

Player::Player(PhysicsEngine *physEngine)
	: m_physEngine(physEngine)
{}

bool Player::init(Vec2 const& origin, Size const& size)
{
	if (!Sprite::initWithFile("player.png"))
		return false;

	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	bodyDef.position.Set(origin.x / m_physEngine->getPtmRatio(),
		origin.y / m_physEngine->getPtmRatio());
	if (!m_physEngine->createBody(bodyDef))
		CCASSERT(false, "Can't create body");

	m_puppeteer = NodePhysicsPuppeteer::create(this, bodyDef, m_physEngine);
	if (!m_puppeteer.Keeps())
		return false;

	b2PolygonShape shape;
	shape.SetAsBox(size.width / 2 / m_physEngine->getPtmRatio(),
		size.height / 2 / m_physEngine->getPtmRatio());

	b2FixtureDef fixtureDef;
	fixtureDef.shape = &shape;
	fixtureDef.density = 1.0f;
	fixtureDef.friction = 0.2f;
	fixtureDef.restitution = 0.0f;
	if (!m_puppeteer->getBody()->CreateFixture(&fixtureDef))
		CCASSERT(false, "Can't create fixture");

	return true;
}
