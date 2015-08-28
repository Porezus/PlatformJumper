#pragma once

#include "cocos2d.h"

class Bonus : public cocos2d::Sprite
{
public:
	static Bonus* create(cocos2d::Texture2D *texture, cocos2d::Rect const& imageRect,
		cocos2d::Vec2 const& origin, int value);

	bool init(cocos2d::Texture2D *texture, cocos2d::Rect const& imageRect,
		cocos2d::Vec2 const& origin, int value);
};
