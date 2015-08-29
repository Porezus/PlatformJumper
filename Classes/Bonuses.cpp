#include "Bonuses.h"
#include "Bonus.h"
#include "PhysicsEngine.h"
#include "RawDataUtils.h"

USING_NS_CC;

Bonuses* Bonuses::create(PhysicsEngine *physEngine, std::istream &in, int mapHeight)
{
	Bonuses *pRet = new (std::nothrow) Bonuses(physEngine);
	if (pRet && pRet->init(in, mapHeight))
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

bool Bonuses::init(std::istream &in, int mapHeight)
{
	if (!SpriteBatchNode::initWithFile("gfx/bonus_atlas.png"))
		return false;

	try
	{
		const size_t bonusCnt = RawData::ReadSizeT(in);
		for (size_t i = 0; i < bonusCnt; ++i)
		{
			const Rect imageRect(RawData::ReadRect(in));

			Vec2 origin(RawData::ReadVec2(in));
			origin.y = mapHeight - origin.y;

			const int value(RawData::ReadInt(in));

			if (!AddBonus(imageRect, origin, value))
				return false;
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
