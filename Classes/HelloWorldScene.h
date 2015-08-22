#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "ObjectKeeper.h"

class PhysicsEngine;
class Player;
class InputManager;
class GameWorld;

class HelloWorld : public cocos2d::Layer
{
public:
	// there's no 'id' in cpp, so we recommend returning the class instance pointer
	static cocos2d::Scene* createScene();

	HelloWorld();

	// Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
	virtual bool init();
	
	// implement the "static create()" method manually
	CREATE_FUNC(HelloWorld);

	virtual void update(float dt) override;
	virtual void onEnter() override;
	virtual void onExit() override;

private:
	cocos2d::Vec2 GetPositionInCamera(cocos2d::Node *node) const;
	float BindCameraPositionXWithinMap(float x) const;
	float BindCameraPositionYWithinMap(float y) const;

	ObjectKeeper<PhysicsEngine> m_physEngine;
	Player *m_player;
	InputManager *m_inputManager;
	GameWorld *m_gameWorld;

	cocos2d::Size m_cameraSize;
	float m_targetPosX;
};

#endif // __HELLOWORLD_SCENE_H__
