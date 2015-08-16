#pragma once

#include "cocos2d.h"
#include "Box2D\Box2D.h"

class WorldPhysics : public cocos2d::Object
{
public:
	static WorldPhysics* create(b2Vec2 const& playerOrigin, cocos2d::Vec2 const& playerSize);

	WorldPhysics();
	bool init(b2Vec2 const& playerOrigin, cocos2d::Vec2 const& playerSize);
	~WorldPhysics();

private:
	b2World *_world;
	b2Body *_playerBody;
};
