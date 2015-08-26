#pragma once

#include "cocos2d.h"
#include "ObjectKeeper.h"

class AnimationKit : public cocos2d::Object
{
public:
	static AnimationKit* create(float delay);
	bool init(float delay);

	bool InitAction(bool repeat = true);
	cocos2d::Animation* GetAnimation() const;
	cocos2d::ActionInterval* GetAction() const;

private:
	cocos2d::Animation *m_animation;
	ObjectKeeper<cocos2d::ActionInterval> m_action;
};
