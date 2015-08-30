#pragma once

#include "cocos2d.h"
#include "ObjectKeeper.h"

class PhysicsEngine;
class Player;
class InputManager;
class GameWorld;
class Bonuses;
class CameraControl;

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
	void GrabBonus();

private:
	void LoadNextMap();

	ObjectKeeper<PhysicsEngine> m_physEngine;
	Player *m_player;
	InputManager *m_inputManager;
	GameWorld *m_gameWorld;
	std::unique_ptr<CameraControl> m_cameraControl;

	int m_bonusesLeft;
	std::string m_nextMap;
};
