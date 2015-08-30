#include "Bonus.h"
#include "Physics\PhysicsEngine.h"
#include "BonusPuppeteer.h"

USING_NS_CC;

Bonus* Bonus::create(Texture2D *texture, Rect const& imageRect,
	Vec2 const& origin, PhysicsEngine *physEngine)
{
	Bonus *pRet = new (std::nothrow) Bonus();
	if (pRet && pRet->init(texture, imageRect, origin, physEngine))
	{
		pRet->autorelease();
	}
	else
	{
		CC_SAFE_DELETE(pRet);
	}
	return pRet;
}

bool Bonus::init(Texture2D *texture, Rect const& imageRect,
	Vec2 const& origin, PhysicsEngine *physEngine)
{
	if (!Sprite::initWithTexture(texture, imageRect))
		return false;

	setPosition(origin);

	b2BodyDef bodyDef;
	bodyDef.type = b2_staticBody;
	bodyDef.position.Set(origin.x / physEngine->getPtmRatio(),
		origin.y / physEngine->getPtmRatio());
	if (!physEngine->createBody(bodyDef))
		CCASSERT(false, "Can't create body");

	m_puppeteer = BonusPuppeteer::create(bodyDef, physEngine, this);
	if (!m_puppeteer)
		return false;

	b2PolygonShape shape;
	shape.SetAsBox(imageRect.size.width / 2 / physEngine->getPtmRatio(),
		imageRect.size.height / 2 / physEngine->getPtmRatio());

	b2FixtureDef fixtureDef;
	fixtureDef.shape = &shape;
	fixtureDef.isSensor = true;
	if (!m_puppeteer->getBody()->CreateFixture(&fixtureDef))
		CCASSERT(false, "Can't create fixture");

	return true;
}
