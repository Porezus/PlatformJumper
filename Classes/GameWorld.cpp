#include "GameWorld.h"
#include "Physics\PhysicsEngine.h"
#include "Json\JsonUtils.h"

USING_NS_CC;
using namespace json11;

GameWorld* GameWorld::create(PhysicsEngine *physEngine, std::string const& img, Json const& json)
{
	GameWorld *pRet = new (std::nothrow) GameWorld();
	if (pRet && pRet->init(physEngine, img, json))
	{
		pRet->autorelease();
	}
	else
	{
		CC_SAFE_DELETE(pRet);
	}
	return pRet;
}

bool GameWorld::init(PhysicsEngine *physEngine, std::string const& img, Json const& json)
{
	if (!Sprite::initWithFile(img))
		return false;

	for (auto &block : json.array_items())
	{
		const Vec2 leftUp(block["left"].number_value(), block["top"].number_value());
		const Vec2 rightDown(block["right"].number_value(), block["bottom"].number_value());
		const Size size(rightDown.x - leftUp.x, rightDown.y - leftUp.y);
		AddRectBlock(Rect(Vec2(leftUp.x, getContentSize().height - leftUp.y - size.height), size), physEngine);
	}

	setAnchorPoint(Vec2());
	return true;
}

void GameWorld::AddRectBlock(Rect const& rect, PhysicsEngine *physEngine)
{
	b2BodyDef bodyDef;
	bodyDef.type = b2_staticBody;
	bodyDef.position.Set(rect.getMidX() / physEngine->getPtmRatio(),
		rect.getMidY() / physEngine->getPtmRatio());

	b2PolygonShape rectShape;
	rectShape.SetAsBox(rect.size.width / 2 / physEngine->getPtmRatio(),
		rect.size.height / 2 / physEngine->getPtmRatio());

	b2FixtureDef fixtureDef;
	fixtureDef.shape = &rectShape;

	auto body = physEngine->createBody(bodyDef);
	CCASSERT(body, "Can't create body");
	body->CreateFixture(&fixtureDef);
}
