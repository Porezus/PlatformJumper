#include "WorldPhysics.h"

USING_NS_CC;

WorldPhysics* WorldPhysics::create(Vec2 const& playerOrigin, Size const& playerSize, float ppm)
{
	WorldPhysics *ret = new (std::nothrow) WorldPhysics(ppm);
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

WorldPhysics::WorldPhysics(float ppm)
	:_world(nullptr)
	,_playerBody(nullptr)
	,_ppm(ppm)
{}

bool WorldPhysics::init(Vec2 const& playerOrigin, Size const& playerSize)
{
	if (!Node::init())
	{
		return false;
	}

	_world = new (std::nothrow) b2World(b2Vec2(0.0f, -9.8f));
	if (!_world) return false;

	b2BodyDef playerBodyDef;
	playerBodyDef.type = b2_dynamicBody;
	playerBodyDef.position.Set(playerOrigin.x / _ppm, playerOrigin.y / _ppm);

	b2PolygonShape playerPolygon;
	playerPolygon.SetAsBox(playerSize.width / 2 / _ppm, playerSize.height / 2 / _ppm);

	b2FixtureDef playerFixtureDef;
	playerFixtureDef.shape = &playerPolygon;
	playerFixtureDef.density = 1.0f;
	playerFixtureDef.friction = 0.2f;
	playerFixtureDef.restitution = 0.0f;

	_playerBody = _world->CreateBody(&playerBodyDef);
	if (!_playerBody) return false;
	_playerBody->CreateFixture(&playerFixtureDef);

	return true;
}

WorldPhysics::~WorldPhysics()
{
	delete _world;
}

void WorldPhysics::Step(float dt)
{
	_world->Step(dt, 10, 10);
}

Vec2 WorldPhysics::GetPlayerPosition() const
{
	return Vec2(_playerBody->GetPosition().x * _ppm, _playerBody->GetPosition().y * _ppm);
}

bool WorldPhysics::AddWallRect(Rect const& rect)
{
	b2BodyDef bodyDef;
	bodyDef.type = b2_staticBody;
	bodyDef.position.Set(rect.getMidX() / _ppm, rect.getMidY() / _ppm);

	b2PolygonShape rectShape;
	rectShape.SetAsBox(rect.size.width / 2 / _ppm, rect.size.height / 2 / _ppm);

	b2FixtureDef fixtureDef;
	fixtureDef.shape = &rectShape;
	fixtureDef.density = 1.0f;
	fixtureDef.friction = 0.2f;
	fixtureDef.restitution = 0.0f;

	auto body = _world->CreateBody(&bodyDef);
	if (!body) return false;
	body->CreateFixture(&fixtureDef);

	return true;
}
