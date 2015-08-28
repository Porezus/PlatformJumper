#pragma once

#include "cocos2d.h"

class Bonuses : public cocos2d::SpriteBatchNode
{
public:
	static Bonuses* create();
	bool init();

private:
	bool AddBonus(cocos2d::Rect const& imageRect, cocos2d::Vec2 const& origin, int value);
};
