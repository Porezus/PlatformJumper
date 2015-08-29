#include "Bonus.h"
#include "PhysicsEngine.h"
#include "BonusPuppeteer.h"

USING_NS_CC;

Bonus* Bonus::create(Texture2D *texture, Rect const& imageRect, Vec2 const& origin, int value, PhysicsEngine *physEngine)
{
	Bonus *pRet = new (std::nothrow) Bonus(physEngine);
	if (pRet && pRet->init(texture, imageRect, origin, value))
	{
		pRet->autorelease();
	}
	else
	{
		CC_SAFE_DELETE(pRet);
	}
	return pRet;
}

Bonus::Bonus(PhysicsEngine *physEngine)
	: m_physEngine(physEngine)
{}

bool Bonus::init(Texture2D *texture, Rect const& imageRect, Vec2 const& origin, int value)
{
	if (!Sprite::initWithTexture(texture, imageRect))
		return false;

	setPosition(origin);

	b2BodyDef bodyDef;
	bodyDef.type = b2_staticBody;
	bodyDef.position.Set(origin.x / m_physEngine->getPtmRatio(),
		origin.y / m_physEngine->getPtmRatio());
	if (!m_physEngine->createBody(bodyDef))
		CCASSERT(false, "Can't create body");

	m_puppeteer = BonusPuppeteer::create(bodyDef, m_physEngine, this);
	if (!m_puppeteer)
		return false;

	b2PolygonShape shape;
	shape.SetAsBox(imageRect.size.width / 2 / m_physEngine->getPtmRatio(),
		imageRect.size.height / 2 / m_physEngine->getPtmRatio());

	b2FixtureDef fixtureDef;
	fixtureDef.shape = &shape;
	fixtureDef.density = 1.0f;
	fixtureDef.friction = 0.2f;
	fixtureDef.restitution = 0.0f;
	if (!m_puppeteer->getBody()->CreateFixture(&fixtureDef))
		CCASSERT(false, "Can't create fixture");

	return true;
}