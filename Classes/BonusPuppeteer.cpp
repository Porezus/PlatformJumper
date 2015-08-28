#include "BonusPuppeteer.h"
#include "PhysicsEngine.h"

BonusPuppeteer* BonusPuppeteer::create(const b2BodyDef &bodyDef, PhysicsEngine *engine)
{
	BonusPuppeteer *pRet = new (std::nothrow) BonusPuppeteer();
	if (pRet && pRet->init(bodyDef, engine))
	{
		pRet->autorelease();
	}
	else
	{
		CC_SAFE_DELETE(pRet);
	}
	return pRet;
}

void BonusPuppeteer::didUpdatePhysics()
{}

void BonusPuppeteer::willUpdatePhysics(float dt)
{}

void BonusPuppeteer::didBeginContact(const PhysicsContactInfo &info)
{}
