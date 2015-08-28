#include "AnimationKit.h"

USING_NS_CC;

AnimationKit* AnimationKit::create(float delay)
{
	AnimationKit *pRet = new (std::nothrow) AnimationKit();
	if (pRet && pRet->init(delay))
	{
		pRet->autorelease();
	}
	else
	{
		CC_SAFE_DELETE(pRet);
	}
	return pRet;
}

bool AnimationKit::init(float delay)
{
	m_animation = Animation::create();
	if (!m_animation)
		return false;
	m_animation->setDelayPerUnit(delay);

	return true;
}

AnimationKit::AnimationKit()
	: m_anchor(0.5f, 0.5f)
{}

bool AnimationKit::InitAction(bool repeat)
{
	CCASSERT(!m_action, "Action is already initialized");

	m_action = Animate::create(m_animation);
	if (!m_action)
		return false;

	if (repeat)
	{
		m_action = RepeatForever::create(m_action);
		if (!m_action)
			return false;
	}

	return true;
}

Animation* AnimationKit::GetAnimation() const
{
	return m_animation;
}

ActionInterval* AnimationKit::GetAction() const
{
	CCASSERT(m_action, "Action is not initialized");
	return m_action;
}
