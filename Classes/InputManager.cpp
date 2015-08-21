#include "InputManager.h"

USING_NS_CC;

InputManager::InputManager()
	:_left(false)
	,_right(false)
	,_jump(false)
{
	auto eventListener = EventListenerKeyboard::create();
	Director::getInstance()->getOpenGLView()->setIMEKeyboardState(true);
	eventListener->onKeyPressed = [=](EventKeyboard::KeyCode keyCode, Event* event)
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
	};
	eventListener->onKeyReleased = [=](EventKeyboard::KeyCode keyCode, Event* event)
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
	};
	this->_eventDispatcher->addEventListenerWithSceneGraphPriority(eventListener, this);
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
