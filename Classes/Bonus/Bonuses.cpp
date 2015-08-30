#include "Bonuses.h"
#include "Bonus.h"
#include "Physics\PhysicsEngine.h"
#include "RawDataUtils.h"
#include "json\JsonUtils.h"

USING_NS_CC;
using namespace json11;

Bonuses* Bonuses::create(PhysicsEngine *physEngine, Json const& json, int mapHeight)
{
	Bonuses *pRet = new (std::nothrow) Bonuses(physEngine);
	if (pRet && pRet->init(json, mapHeight))
	{
		pRet->autorelease();
	}
	else
	{
		CC_SAFE_DELETE(pRet);
	}
	return pRet;
}

Bonuses::Bonuses(PhysicsEngine *physEngine)
	: m_physEngine(physEngine)
{}

bool Bonuses::init(Json const& json, int mapHeight)
{
	if (!SpriteBatchNode::initWithFile("gfx/bonus_atlas.png"))
		return false;

	auto bonusArray = json.array_items();
	for (auto &bonus : bonusArray)
	{
		Vec2 origin(JsonUtils::ParseVec2(bonus["origin"]));
		origin.y = mapHeight - origin.y;

		if (!AddBonus(JsonUtils::ParseRect(bonus["imgRect"]), origin, bonus["value"].int_value()))
			return false;
	}

	return true;
}

bool Bonuses::AddBonus(Rect const& imageRect, Vec2 const& origin, int value)
{
	auto bonus = Bonus::create(getTexture(), imageRect, origin, value, m_physEngine);
	if (!bonus)
		return false;
	addChild(bonus);

	return true;
}
