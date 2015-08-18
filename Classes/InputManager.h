#pragma once

#include "cocos2d.h"

class InputManager : public cocos2d::Node
{
public:
	CREATE_FUNC(InputManager);
	InputManager();
	void KeyPressed(cocos2d::EventKeyboard::KeyCode keyCode);
	void KeyReleased(cocos2d::EventKeyboard::KeyCode keyCode);
	bool IsLeft() const;
	bool IsRight() const;
	bool IsJump() const;

private:
	static const cocos2d::EventKeyboard::KeyCode LEFT = cocos2d::EventKeyboard::KeyCode::KEY_LEFT_ARROW;
	static const cocos2d::EventKeyboard::KeyCode RIGHT = cocos2d::EventKeyboard::KeyCode::KEY_RIGHT_ARROW;
	static const cocos2d::EventKeyboard::KeyCode JUMP = cocos2d::EventKeyboard::KeyCode::KEY_UP_ARROW;

	bool _left, _right, _jump;
};
