#pragma once

#include "cocos2d.h"
#include "ObjectKeeper.h"

class PhysicsEngine;
class NodePhysicsPuppeteer;
class AnimationKit;

class Player : public cocos2d::SpriteBatchNode
{
public:
	static Player* create(PhysicsEngine *physEngine, cocos2d::Vec2 const& origin, bool facingLeft);
	
	Player(PhysicsEngine *physEngine);
	bool init(cocos2d::Vec2 const& origin, bool facingLeft);

	void Move(float dx);
	void Jump();
	bool IsFacingLeft() const;

private:
	void SetFacing(bool facingLeft);
	void SetAnimation(AnimationKit *kit, cocos2d::Vec2 const& anchor = cocos2d::Vec2(0.5f, 0.5f));

	ObjectKeeper<PhysicsEngine> m_physEngine;
	ObjectKeeper<NodePhysicsPuppeteer> m_puppeteer;
	cocos2d::Sprite *m_sprite;
	bool m_facingLeft;
	bool m_running;

	ObjectKeeper<AnimationKit> m_idleKit;
	ObjectKeeper<AnimationKit> m_runKit;
};
