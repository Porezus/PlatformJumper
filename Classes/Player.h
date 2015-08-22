#pragma once

#include "cocos2d.h"
#include "ObjectKeeper.h"

class PhysicsEngine;
class NodePhysicsPuppeteer;

class Player : public cocos2d::Sprite
{
public:
	static Player* create(PhysicsEngine *physEngine, cocos2d::Vec2 const& origin, cocos2d::Size const& size);
	
	Player(PhysicsEngine *physEngine);
	bool init(cocos2d::Vec2 const& origin, cocos2d::Size const& size);

	void Move(float dx);

private:
	ObjectKeeper<PhysicsEngine> m_physEngine;
	ObjectKeeper<NodePhysicsPuppeteer> m_puppeteer;
};
