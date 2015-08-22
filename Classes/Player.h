#pragma once

#include "cocos2d.h"
#include "ObjectKeeper.h"

class PhysicsEngine;

class Player : public cocos2d::Sprite
{
public:
	static Player* create(PhysicsEngine *physEngine);
	Player(PhysicsEngine *physEngine);

private:
	ObjectKeeper<PhysicsEngine> m_physEngine;
};
