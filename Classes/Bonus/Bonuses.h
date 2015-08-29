#pragma once

#include "cocos2d.h"
#include "ObjectKeeper.h"

class PhysicsEngine;

class Bonuses : public cocos2d::SpriteBatchNode
{
public:
	static Bonuses* create(PhysicsEngine *physEngine, std::istream &in, int mapHeight);
	Bonuses(PhysicsEngine *physEngine);
	bool init(std::istream &in, int mapHeight);

private:
	bool AddBonus(cocos2d::Rect const& imageRect, cocos2d::Vec2 const& origin, int value);
	ObjectKeeper<PhysicsEngine> m_physEngine;
};
