#pragma once

#include "cocos2d.h"
#include "ObjectKeeper.h"

class PhysicsEngine;
class NodePhysicsPuppeteer;

class Player : public cocos2d::Sprite
{
public:
	static Player* create(PhysicsEngine *physEngine, cocos2d::Vec2 const& origin, cocos2d::Size const& size, bool facingLeft);
	
	Player(PhysicsEngine *physEngine);
	bool init(cocos2d::Vec2 const& origin, cocos2d::Size const& size, bool facingLeft);

	void Move(float dx);
	void Jump();

private:
	void SetFacing(bool facingLeft);
	bool IsFacingLeft() const;

	ObjectKeeper<PhysicsEngine> m_physEngine;
	ObjectKeeper<NodePhysicsPuppeteer> m_puppeteer;
	bool m_facingLeft;
};
