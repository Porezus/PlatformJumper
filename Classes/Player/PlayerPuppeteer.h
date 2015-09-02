#pragma once

#include "Physics\NodePhysicsPuppeteer.h"

class PlayerPuppeteer : public NodePhysicsPuppeteer
{
public:
	static PlayerPuppeteer* create(cocos2d::Node *node, const b2BodyDef &bodyDef, PhysicsEngine *engine);
	PlayerPuppeteer(cocos2d::Node *node);

	void didBeginContact(const PhysicsContactInfo &info) override;
	void didEndContact(const PhysicsContactInfo &info) override;
	void willUpdatePhysics(float dt) override;

	bool NearGround() const;
	bool CanJump() const;
	void ResetJumpTimeout();

private:
	bool m_nearGround;
	float m_jumpTimeout;
};
