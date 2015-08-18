#pragma once

#include "cocos2d.h"

class InputManager : public cocos2d::Node
{
public:
	CREATE_FUNC(InputManager);
	InputManager();
	void KeyPressed(cocos2d::EventKeyboard::KeyCode keyCode);
	void KeyReleased(cocos2d::EventKeyboard::KeyCode keyCode);

private:
	static const cocos2d::EventKeyboard::KeyCode LEFT = cocos2d::EventKeyboard::KeyCode::KEY_L;
	static const cocos2d::EventKeyboard::KeyCode RIGHT = cocos2d::EventKeyboard::KeyCode::KEY_R;
	static const cocos2d::EventKeyboard::KeyCode JUMP = cocos2d::EventKeyboard::KeyCode::KEY_U;

	bool _left, _right, _jump;
};
