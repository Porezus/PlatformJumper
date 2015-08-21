#include "NodePhysicsPuppeteer.h"
#include "PhysicsEngine.h"

USING_NS_CC;

NodePhysicsPuppeteer *NodePhysicsPuppeteer::create(Node *node, const b2BodyDef &bodyDef, PhysicsEngine *engine)
{
	NodePhysicsPuppeteer *pRet = new (std::nothrow) NodePhysicsPuppeteer(node);
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

void NodePhysicsPuppeteer::didUpdatePhysics()
{
	m_node->setPosition(getEngine()->getBodyPosition(getBody()));
	m_node->setRotation(getEngine()->getBodyRotation(getBody()));
}

void NodePhysicsPuppeteer::willUpdatePhysics(float dt)
{}

NodePhysicsPuppeteer::NodePhysicsPuppeteer(Node *node)
	: m_node(node)
{}

Node *NodePhysicsPuppeteer::getNode() const
{
	return m_node;
}
