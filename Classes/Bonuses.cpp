#include "Bonuses.h"
#include "Bonus.h"
#include "PhysicsEngine.h"
#include "RawDataUtils.h"

USING_NS_CC;

Bonuses* Bonuses::create(PhysicsEngine *physEngine, std::istream &in)
{
	Bonuses *pRet = new (std::nothrow) Bonuses(physEngine);
	if (pRet && pRet->init(in))
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

bool Bonuses::init(std::istream &in)
{
	if (!SpriteBatchNode::initWithFile("bonus_atlas.png"))
		return false;

	try
	{
		const size_t bonusCnt = RawData::ReadSizeT(in);
		for (size_t i = 0; i < bonusCnt; ++i)
		{
			const Rect imageRect(RawData::ReadRect(in));
			const Vec2 origin(RawData::ReadVec2(in));
			const int value(RawData::ReadInt(in));
			AddBonus(imageRect, origin, value);
		}
	}
	catch (std::exception const&)
	{
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
