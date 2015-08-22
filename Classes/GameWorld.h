#pragma once

#include "cocos2d.h"
#include "ObjectKeeper.h"

class PhysicsEngine;

class GameWorld : public cocos2d::Sprite
{
public:
	static GameWorld* create(PhysicsEngine *physEngine);

	GameWorld(PhysicsEngine *physEngine);
	bool init();

	void AddRectBlock(cocos2d::Rect const& rect);

private:
	ObjectKeeper<PhysicsEngine> m_physEngine;
};
