#pragma once

#include "cocos2d.h"
#include "ObjectKeeper.h"

class PhysicsEngine;
namespace json11
{
	class Json;
};

class Bonuses : public cocos2d::SpriteBatchNode
{
public:
	static Bonuses* create(PhysicsEngine *physEngine, json11::Json const& json, int mapHeight);
	Bonuses(PhysicsEngine *physEngine);
	bool init(json11::Json const& json, int mapHeight);

private:
	bool AddBonus(cocos2d::Rect const& imageRect, cocos2d::Vec2 const& origin);
	ObjectKeeper<PhysicsEngine> m_physEngine;
};
