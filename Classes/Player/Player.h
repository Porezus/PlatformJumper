#pragma once

#include "cocos2d.h"
#include "ObjectKeeper.h"

class PhysicsEngine;
class PlayerPuppeteer;
class AnimationKit;
namespace json11
{
	class Json;
};

class Player : public cocos2d::SpriteBatchNode
{
public:
	static Player* create(PhysicsEngine *physEngine, json11::Json const& json, int mapHeight);
	Player();
	bool init(PhysicsEngine *physEngine, json11::Json const& json, int mapHeight);

	void Move(float dx);
	void Stop();
	void Jump();
	bool IsFacingLeft() const;
	cocos2d::Vec2 GetSpritePosition() const;

private:
	void SetFacing(bool facingLeft);
	void SetAnimation(AnimationKit *kit);

	ObjectKeeper<PlayerPuppeteer> m_puppeteer;
	cocos2d::Sprite *m_sprite;
	bool m_facingLeft;
	bool m_running;

	ObjectKeeper<AnimationKit> m_idleKit;
	ObjectKeeper<AnimationKit> m_runKit;
};
