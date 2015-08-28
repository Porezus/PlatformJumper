#pragma once

#include "PhysicsPuppeteer.h"

class BonusPuppeteer : public PhysicsPuppeteer
{
public:
	static BonusPuppeteer* create(const b2BodyDef &bodyDef, PhysicsEngine *engine);

	void didUpdatePhysics() override;
	void willUpdatePhysics(float dt) override;

	void didBeginContact(const PhysicsContactInfo &info) override;
};
