#include "InputManager.h"

InputManager::InputManager()
	:_left(false)
	,_right(false)
	,_jump(false)
{}

void InputManager::KeyPressed(cocos2d::EventKeyboard::KeyCode keyCode)
{
	switch (keyCode)
	{
	case LEFT:
		_left = true;
		break;

	case RIGHT:
		_right = true;
		break;

	case JUMP:
		_jump = true;
		break;
	}
}

void InputManager::KeyReleased(cocos2d::EventKeyboard::KeyCode keyCode)
{
	switch (keyCode)
	{
	case LEFT:
		_left = false;
		break;

	case RIGHT:
		_right = false;
		break;

	case JUMP:
		_jump = false;
		break;
	}
}

bool InputManager::IsLeft() const
{
	return _left && !_right;
}

bool InputManager::IsRight() const
{
	return _right && !_left;
}

bool InputManager::IsJump() const
{
	return _jump;
}
