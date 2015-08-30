#include "Bonuses.h"
#include "Bonus.h"
#include "Physics\PhysicsEngine.h"
#include "json\JsonUtils.h"

USING_NS_CC;
using namespace json11;

Bonuses* Bonuses::create(PhysicsEngine *physEngine, Json const& json, int mapHeight)
{
	Bonuses *pRet = new (std::nothrow) Bonuses();
	if (pRet && pRet->init(physEngine, json, mapHeight))
	{
		pRet->autorelease();
	}
	else
	{
		CC_SAFE_DELETE(pRet);
	}
	return pRet;
}

bool Bonuses::init(PhysicsEngine *physEngine, Json const& json, int mapHeight)
{
	if (!SpriteBatchNode::initWithFile("gfx/bonus_atlas.png"))
		return false;

	for (auto &bonus : json.array_items())
	{
		Vec2 origin(JsonUtils::ParseVec2(bonus["origin"]));
		origin.y = mapHeight - origin.y;

		auto bonusSprite = Bonus::create(getTexture(), JsonUtils::ParseRect(bonus["imgRect"]), origin, physEngine);
		if (!bonusSprite)
			return false;
		addChild(bonusSprite);
	}

	return true;
}
