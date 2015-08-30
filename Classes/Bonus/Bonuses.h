#pragma once

#include "cocos2d.h"

class PhysicsEngine;
namespace json11
{
	class Json;
};

class Bonuses : public cocos2d::SpriteBatchNode
{
public:
	static Bonuses* create(PhysicsEngine *physEngine, json11::Json const& json, int mapHeight);
	bool init(PhysicsEngine *physEngine, json11::Json const& json, int mapHeight);
};
