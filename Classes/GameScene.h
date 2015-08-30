#pragma once

#include "cocos2d.h"
#include "ObjectKeeper.h"

class PhysicsEngine;
class Player;
class InputManager;
class GameWorld;
class Bonuses;

class GameScene : public cocos2d::Layer
{
public:
	// there's no 'id' in cpp, so we recommend returning the class instance pointer
	static cocos2d::Scene* createScene(std::string const& mapName);

	static GameScene* create(std::string const& mapName);
	GameScene();

	// Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
	virtual bool init(std::string const& mapName);
	
	virtual void update(float dt) override;
	virtual void onEnter() override;
	virtual void onExit() override;

private:
	cocos2d::Vec2 GetPositionInCamera(cocos2d::Vec2 const& scenePos) const;
	float BindCameraPositionXWithinMap(float x) const;
	float BindCameraPositionYWithinMap(float y) const;

	void ChangeMap(std::string const& mapName);
	void EndGame();

	ObjectKeeper<PhysicsEngine> m_physEngine;
	Player *m_player;
	InputManager *m_inputManager;
	GameWorld *m_gameWorld;

	cocos2d::Size m_cameraSize;
	float m_targetPosX;
};
