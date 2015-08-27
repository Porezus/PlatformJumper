#pragma once

#include "cocos2d.h"
#include "ObjectKeeper.h"

class PhysicsEngine;

class GameWorld : public cocos2d::Sprite
{
public:
	static GameWorld* create(PhysicsEngine *physEngine, std::string const& path);

	GameWorld(PhysicsEngine *physEngine);
	bool init(std::string const& path);

private:
	void AddRectBlock(cocos2d::Rect const& rect);
	ObjectKeeper<PhysicsEngine> m_physEngine;
};