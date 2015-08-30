#pragma once

#include "cocos2d.h"

class PhysicsEngine;
namespace json11
{
	class Json;
};

class GameWorld : public cocos2d::Sprite
{
public:
	static GameWorld* create(PhysicsEngine *physEngine, std::string const& img, json11::Json const& json);
	bool init(PhysicsEngine *physEngine, std::string const& img, json11::Json const& json);

private:
	void AddRectBlock(cocos2d::Rect const& rect, PhysicsEngine *physEngine);
};
