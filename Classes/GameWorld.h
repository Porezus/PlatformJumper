#pragma once

#include "cocos2d.h"
#include "ObjectKeeper.h"

class PhysicsEngine;
namespace json11
{
	class Json;
};

class GameWorld : public cocos2d::Sprite
{
public:
	static GameWorld* create(PhysicsEngine *physEngine, std::string const& img, json11::Json const& json);
	GameWorld(PhysicsEngine *physEngine);
	bool init(std::string const& img, json11::Json const& json);

private:
	void AddRectBlock(cocos2d::Rect const& rect);
	ObjectKeeper<PhysicsEngine> m_physEngine;
};
