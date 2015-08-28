#include "Bonuses.h"
#include "Bonus.h"
#include "PhysicsEngine.h"

USING_NS_CC;

Bonuses* Bonuses::create(PhysicsEngine *physEngine)
{
	Bonuses *pRet = new (std::nothrow) Bonuses(physEngine);
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

Bonuses::Bonuses(PhysicsEngine *physEngine)
	: m_physEngine(physEngine)
{}

bool Bonuses::init()
{
	if (!SpriteBatchNode::initWithFile("bonus_atlas.png"))
		return false;

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
