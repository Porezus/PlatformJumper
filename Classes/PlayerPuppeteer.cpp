#include "PlayerPuppeteer.h"

USING_NS_CC;

PlayerPuppeteer* PlayerPuppeteer::create(Node *node, const b2BodyDef &bodyDef, PhysicsEngine *engine)
{
	PlayerPuppeteer *pRet = new (std::nothrow) PlayerPuppeteer(node);
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

PlayerPuppeteer::PlayerPuppeteer(Node *node)
	: NodePhysicsPuppeteer(node)
{}

void PlayerPuppeteer::didBeginContact(const PhysicsContactInfo &info)
{}

void PlayerPuppeteer::didEndContact(const PhysicsContactInfo &info)
{}
