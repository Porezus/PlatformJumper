#include "Bonuses.h"
#include "Bonus.h"

USING_NS_CC;

Bonuses* Bonuses::create()
{
	Bonuses *pRet = new (std::nothrow) Bonuses();
	if (pRet && pRet->init())
	{
		pRet->autorelease();
	}
	else
	{
		CC_SAFE_DELETE(pRet);
	}
	return pRet;
}

bool Bonuses::init()
{
	if (!SpriteBatchNode::initWithFile("bonus_atlas.png"))
		return false;

	return true;
}

bool Bonuses::AddBonus(Rect const& imageRect, Vec2 const& origin, int value)
{
	auto bonus = Bonus::create(getTexture(), imageRect, origin, value);
	if (!bonus)
		return false;
	addChild(bonus);
}
