#include "PhysicsEngine.h"
#include "PhysicsPuppeteer.h"
#include "PhysicsContactsListener.h"

USING_NS_CC;

PhysicsEngine* PhysicsEngine::create(Layer *parent, int pixelsPerMeter)
{
	PhysicsEngine *pRet = new (std::nothrow) PhysicsEngine(parent, pixelsPerMeter);
	if (pRet && pRet->init())
	{
		pRet->autorelease();
	}
	else
	{
		CC_SAFE_DELETE(pRet);
	}
	return pRet;
}

PhysicsEngine::PhysicsEngine(Layer *parent, int pixelsPerMeter)
	: mWorld(nullptr)
	, mContactsListener(nullptr)
	, mPixelsPerMeter(pixelsPerMeter)
	, m_parent(parent)
{}

bool PhysicsEngine::init()
{
	mWorld = new (std::nothrow) b2World(b2Vec2(0.0f, -9.8f));
	if (!mWorld)
		return false;

	mContactsListener = new (std::nothrow) PhysicsContactsListener();
	if (!mContactsListener)
		return false;

	mWorld->SetContactListener(mContactsListener);
	return true;
}

PhysicsEngine::~PhysicsEngine()
{
	delete mWorld;
	delete mContactsListener;
}

b2Body *PhysicsEngine::createBody(const b2BodyDef &bodyDef) const
{
	return mWorld->CreateBody(&bodyDef);
}

void PhysicsEngine::deleteBodyLater(b2Body *body)
{
	body->SetUserData(nullptr);
	mBodiesToDelete.insert(body);
}

void PhysicsEngine::tick(float dt)
{
	for (b2Body *body : mBodiesToDelete)
		mWorld->DestroyBody(body);
	mBodiesToDelete.clear();

	// Update puppeteers in the physics world
	for (b2Body* b = mWorld->GetBodyList(); b; b = b->GetNext()) {
		if (b->GetUserData() != NULL) {
			PhysicsPuppeteer *puppeteer = reinterpret_cast<PhysicsPuppeteer *>(b->GetUserData());
			puppeteer->willUpdatePhysics(dt);
		}
	}

	int velocityIterations = 10;
	int positionIterations = 10;

	// Instruct the world to perform a single step of simulation. It is
	// generally best to keep the time step and iterations fixed.
	mWorld->Step(dt, velocityIterations, positionIterations);
	for (b2Body* b = mWorld->GetBodyList(); b; b = b->GetNext()) {
		if (b->GetUserData() != NULL) {
			PhysicsPuppeteer *puppeteer = reinterpret_cast<PhysicsPuppeteer *>(b->GetUserData());
			puppeteer->didUpdatePhysics();
		}
	}

	for (b2Body *body : mBodiesToDelete)
		mWorld->DestroyBody(body);
	mBodiesToDelete.clear();
}

Vec2 PhysicsEngine::getBodyPosition(b2Body *body) const
{
	const b2Vec2 &pos = body->GetPosition();
	return Vec2(mPixelsPerMeter * pos.x, mPixelsPerMeter * pos.y);
}

float PhysicsEngine::getBodyRotation(b2Body *body) const
{
	return -1 * CC_RADIANS_TO_DEGREES(body->GetAngle());
}

float PhysicsEngine::getCocosAngleFromBox2d(float angle) const
{
	return -1 * CC_RADIANS_TO_DEGREES(angle);
}

float PhysicsEngine::getBox2dAngleFromCocos(float angle) const
{
	return -1 * CC_DEGREES_TO_RADIANS(angle);
}

int PhysicsEngine::getPtmRatio() const
{
	return mPixelsPerMeter;
}

b2Vec2 PhysicsEngine::getNodePosition(Node *node) const
{
	return getNodePointPosition(node, Vec2(0, 0));
}

b2Vec2 PhysicsEngine::getNodePointPosition(Node *node, const Vec2 &point) const
{
	AffineTransform transform = AffineTransformMakeIdentity();
	for (;;) {
		AffineTransform next = node->getNodeToParentAffineTransform();
		transform = AffineTransformConcat(transform, next);
		node = node->getParent();
		CCAssert(node, "Node is out of Box2D world: physics layer is not parent of this node.");
		if (node == m_parent)
			break;
	}
	Vec2 position = PointApplyAffineTransform(point, transform);
	return b2Vec2(position.x / mPixelsPerMeter, position.y / mPixelsPerMeter);
}
