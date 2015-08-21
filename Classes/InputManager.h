#pragma once

#include "cocos2d.h"

class InputManager : public cocos2d::Node
{
public:
	CREATE_FUNC(InputManager);
	InputManager();

	bool IsLeft() const;
	bool IsRight() const;
	bool IsJump() const;

private:
	bool IsPressed(cocos2d::EventKeyboard::KeyCode keyCode) const;
	std::set<cocos2d::EventKeyboard::KeyCode> m_pressed;
};
