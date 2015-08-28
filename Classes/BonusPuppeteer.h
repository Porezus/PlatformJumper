#pragma once

#include "PhysicsPuppeteer.h"

class BonusPuppeteer : public PhysicsPuppeteer
{
public:
	static BonusPuppeteer* create(const b2BodyDef &bodyDef, PhysicsEngine *engine, cocos2d::Node *node);
	BonusPuppeteer(cocos2d::Node *node);

	void didUpdatePhysics() override;
	void willUpdatePhysics(float dt) override;

	void didBeginContact(const PhysicsContactInfo &info) override;

private:
	cocos2d::Node *m_node;
};
