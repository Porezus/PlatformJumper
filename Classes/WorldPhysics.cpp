#include "WorldPhysics.h"

USING_NS_CC;

WorldPhysics* WorldPhysics::create(b2Vec2 const& playerOrigin, Vec2 const& playerSize)
{
	WorldPhysics *ret = new (std::nothrow) WorldPhysics();
	if (ret && ret->init(playerOrigin, playerSize))
	{
		ret->autorelease();
		return ret;
	}
	else
	{
		CC_SAFE_DELETE(ret);
		return nullptr;
	}
}

WorldPhysics::WorldPhysics()
	:_world(nullptr)
	,_playerBody(nullptr)
{}

bool WorldPhysics::init(b2Vec2 const& playerOrigin, Vec2 const& playerSize)
{
	_world = new (std::nothrow) b2World(b2Vec2(0.0f, -9.8f));
	if (!_world) return false;

	b2BodyDef playerBodyDef;
	playerBodyDef.type = b2_dynamicBody;
	playerBodyDef.position = playerOrigin;

	b2PolygonShape playerPolygon;
	playerPolygon.SetAsBox(playerSize.x, playerSize.y);

	b2FixtureDef playerFixtureDef;
	playerFixtureDef.shape = &playerPolygon;
	playerFixtureDef.density = 1.0f;
	playerFixtureDef.friction = 0.2f;
	playerFixtureDef.restitution = 0.8f;

	_playerBody = _world->CreateBody(&playerBodyDef);
	if (!_playerBody) return false;
	_playerBody->CreateFixture(&playerFixtureDef);

	return true;
}

WorldPhysics::~WorldPhysics()
{
	delete _world;
}
