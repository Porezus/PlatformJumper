#pragma once

#include "cocos2d.h"
#include "Box2D\Box2D.h"

class WorldPhysics : public cocos2d::Node
{
public:
	static WorldPhysics* create(cocos2d::Vec2 const& playerOrigin, cocos2d::Size const& playerSize, float ppm);

	WorldPhysics(float ppm);
	bool init(cocos2d::Vec2 const& playerOrigin, cocos2d::Size const& playerSize);
	~WorldPhysics();

	void Step(float dt);
	cocos2d::Vec2 GetPlayerPosition() const;
	bool AddWallRect(cocos2d::Rect const& rect);

private:
	b2World *_world;
	b2Body *_playerBody;
	float _ppm;
};
