#pragma once

#include "cocos2d.h"
#include "Box2D\Box2D.h"

class PhysicsContactsListener;

class PhysicsEngine : public cocos2d::Object
{
public:
	static PhysicsEngine* create(cocos2d::Layer *parent, int pixelsPerMeter);

	PhysicsEngine(cocos2d::Layer *parent, int pixelsPerMeter);
	bool init();

	~PhysicsEngine();

	b2Body *createBody(const b2BodyDef &bodyDef) const;
	void deleteBodyLater(b2Body *body);

	// Updates physics world.
	void tick(float dt);

	cocos2d::Vec2 getBodyPosition(b2Body *body) const;
	float getBodyRotation(b2Body *body) const;
	float getCocosAngleFromBox2d(float angle) const;
	float getBox2dAngleFromCocos(float angle) const;
	int getPtmRatio() const;

	b2Vec2 getNodePosition(cocos2d::Node *node) const;
	b2Vec2 getNodePointPosition(cocos2d::Node *node, const cocos2d::Vec2 &point) const;

private:
	b2World *mWorld;
	PhysicsContactsListener *mContactsListener;
	std::set<b2Body *> mBodiesToDelete;
	int mPixelsPerMeter;
	cocos2d::Layer *m_parent;
};
