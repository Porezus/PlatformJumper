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
	, m_nearGround(false)
{}

void PlayerPuppeteer::didBeginContact(const PhysicsContactInfo &info)
{
	if (info.myFixture->GetUserData() == (void*)1)
		m_nearGround = true;
}

void PlayerPuppeteer::didEndContact(const PhysicsContactInfo &info)
{
	if (info.myFixture->GetUserData() == (void*)1)
		m_nearGround = false;
}

bool PlayerPuppeteer::NearGround() const
{
	return m_nearGround;
}
