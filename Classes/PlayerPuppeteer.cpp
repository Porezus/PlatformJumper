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
	, m_onGround(true)
{}

void PlayerPuppeteer::didBeginContact(const PhysicsContactInfo &info)
{
	if (info.myFixture->GetUserData() == (void*)1)
		m_onGround = true;
}

void PlayerPuppeteer::didEndContact(const PhysicsContactInfo &info)
{
	if (info.myFixture->GetUserData() == (void*)1)
		m_onGround = false;
}

bool PlayerPuppeteer::OnGround() const
{
	return m_onGround;
}
