#include "Bonus.h"

USING_NS_CC;

Bonus* Bonus::create(Texture2D *texture, Rect const& imageRect, Vec2 const& origin, int value)
{
	Bonus *pRet = new (std::nothrow) Bonus();
	if (pRet && pRet->init(texture, imageRect, origin, value))
	{
		pRet->autorelease();
	}
	else
	{
		CC_SAFE_DELETE(pRet);
	}
	return pRet;
}

bool Bonus::init(Texture2D *texture, Rect const& imageRect, Vec2 const& origin, int value)
{
	if (!Sprite::initWithTexture(texture, imageRect))
		return false;

	return true;
}
