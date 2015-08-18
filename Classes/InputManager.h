#pragma once

#include "cocos2d.h"

class InputManager : public cocos2d::Node
{
public:
	CREATE_FUNC(InputManager);
	void KeyPressed(cocos2d::EventKeyboard::KeyCode keyCode);
	void KeyReleased(cocos2d::EventKeyboard::KeyCode keyCode);
};
