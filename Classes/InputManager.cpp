#include "InputManager.h"

USING_NS_CC;

bool InputManager::init()
{
	if (!Node::init())
		return false;

	auto eventListener = EventListenerKeyboard::create();
	if (!eventListener)
		return false;

	Director::getInstance()->getOpenGLView()->setIMEKeyboardState(true);

	eventListener->onKeyPressed = [=](EventKeyboard::KeyCode keyCode, Event* event)
	{
		m_pressed.insert(keyCode);
	};
	eventListener->onKeyReleased = [=](EventKeyboard::KeyCode keyCode, Event* event)
	{
		m_pressed.erase(keyCode);
	};

	this->_eventDispatcher->addEventListenerWithSceneGraphPriority(eventListener, this);
	return true;
}

bool InputManager::IsLeft() const
{
	return IsPressed(EventKeyboard::KeyCode::KEY_LEFT_ARROW) && !IsPressed(EventKeyboard::KeyCode::KEY_RIGHT_ARROW);
}

bool InputManager::IsRight() const
{
	return IsPressed(EventKeyboard::KeyCode::KEY_RIGHT_ARROW) && !IsPressed(EventKeyboard::KeyCode::KEY_LEFT_ARROW);
}

bool InputManager::IsJump() const
{
	return IsPressed(EventKeyboard::KeyCode::KEY_UP_ARROW);
}

bool InputManager::IsPressed(EventKeyboard::KeyCode keyCode) const
{
	return m_pressed.find(keyCode) != m_pressed.end();
}
