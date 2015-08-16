#pragma once

#include "cocos2d.h"
#include "Box2D\Box2D.h"

class WorldPhysics : public cocos2d::Node
{
public:
	static WorldPhysics* create(b2Vec2 const& playerOrigin, cocos2d::Vec2 const& playerSize, float ppm);

	WorldPhysics(float ppm);
	bool init(b2Vec2 const& playerOrigin, cocos2d::Vec2 const& playerSize);
	~WorldPhysics();

	void Step(float dt);
	b2Vec2 GetPlayerPosition() const;

	bool AddWallPolygon(b2Vec2 const& origin, b2PolygonShape const& shape);

private:
	b2World *_world;
	b2Body *_playerBody;
	float _ppm;
};
