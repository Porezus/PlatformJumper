#include "BonusPuppeteer.h"
#include "PhysicsEngine.h"

USING_NS_CC;

BonusPuppeteer* BonusPuppeteer::create(const b2BodyDef &bodyDef, PhysicsEngine *engine, Node *node)
{
	BonusPuppeteer *pRet = new (std::nothrow) BonusPuppeteer(node);
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

BonusPuppeteer::BonusPuppeteer(Node *node)
	: m_node(node)
{}

void BonusPuppeteer::didUpdatePhysics()
{}

void BonusPuppeteer::willUpdatePhysics(float dt)
{}

void BonusPuppeteer::didBeginContact(const PhysicsContactInfo &info)
{
	m_node->getParent()->removeChild(m_node);
}
