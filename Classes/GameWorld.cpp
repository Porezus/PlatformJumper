#include "GameWorld.h"
#include "Physics\PhysicsEngine.h"
#include "RawDataUtils.h"
#include "Json\JsonUtils.h"

USING_NS_CC;
using namespace json11;

GameWorld* GameWorld::create(PhysicsEngine *physEngine, std::string const& img, Json const& json)
{
	GameWorld *pRet = new (std::nothrow) GameWorld(physEngine);
	if (pRet && pRet->init(img, json))
	{
		pRet->autorelease();
	}
	else
	{
		CC_SAFE_DELETE(pRet);
	}
	return pRet;
}

GameWorld::GameWorld(PhysicsEngine *physEngine)
	: m_physEngine(physEngine)
{}

bool GameWorld::init(std::string const& img, Json const& json)
{
	if (!Sprite::initWithFile(img))
		return false;

	auto blockArray = json.array_items();
	for (auto &block : blockArray)
	{
		const Vec2 leftUp(block["left"].number_value(), block["top"].number_value());
		const Vec2 rightDown(block["right"].number_value(), block["bottom"].number_value());
		const Size size(rightDown.x - leftUp.x, rightDown.y - leftUp.y);
		AddRectBlock(Rect(Vec2(leftUp.x, getContentSize().height - leftUp.y - size.height), size));
	}

	setAnchorPoint(Vec2());
	return true;
}

void GameWorld::AddRectBlock(Rect const& rect)
{
	b2BodyDef bodyDef;
	bodyDef.type = b2_staticBody;
	bodyDef.position.Set(rect.getMidX() / m_physEngine->getPtmRatio(),
		rect.getMidY() / m_physEngine->getPtmRatio());

	b2PolygonShape rectShape;
	rectShape.SetAsBox(rect.size.width / 2 / m_physEngine->getPtmRatio(),
		rect.size.height / 2 / m_physEngine->getPtmRatio());

	b2FixtureDef fixtureDef;
	fixtureDef.shape = &rectShape;
	fixtureDef.density = 1.0f;
	fixtureDef.friction = 0.2f;
	fixtureDef.restitution = 0.0f;

	auto body = m_physEngine->createBody(bodyDef);
	CCASSERT(body, "Can't create body");
	body->CreateFixture(&fixtureDef);
}
