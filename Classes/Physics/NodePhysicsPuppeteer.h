#pragma once

#include "PhysicsPuppeteer.h"

class NodePhysicsPuppeteer : public PhysicsPuppeteer
{
public:
	static NodePhysicsPuppeteer *create(cocos2d::Node *node, const b2BodyDef &bodyDef, PhysicsEngine *engine);
	void didUpdatePhysics() override;
	void willUpdatePhysics(float dt) override;

protected:
	NodePhysicsPuppeteer(cocos2d::Node *node);
	cocos2d::Node *getNode() const;

private:
	cocos2d::Node *m_node;
};
