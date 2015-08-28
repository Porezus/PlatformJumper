#pragma once

#include "cocos2d.h"
#include "ObjectKeeper.h"

class PhysicsEngine;

class Bonuses : public cocos2d::SpriteBatchNode
{
public:
	static Bonuses* create(PhysicsEngine *physEngine);
	Bonuses(PhysicsEngine *physEngine);
	bool init();

private:
	bool AddBonus(cocos2d::Rect const& imageRect, cocos2d::Vec2 const& origin, int value);
	ObjectKeeper<PhysicsEngine> m_physEngine;
};
