#include "PhysicsPuppeteer.h"
#include "PhysicsEngine.h"

PhysicsPuppeteer::PhysicsPuppeteer()
	: m_body(nullptr)
{}

PhysicsPuppeteer::~PhysicsPuppeteer()
{
	m_engine->deleteBodyLater(m_body);
}

bool PhysicsPuppeteer::init(const b2BodyDef &bodyDef, PhysicsEngine *engine)
{
	if (!Node::init())
		return false;

	m_engine = engine;

	b2BodyDef fixedDef = bodyDef;
	fixedDef.userData = reinterpret_cast<void *>(this);
	m_body = m_engine->createBody(fixedDef);
	CCASSERT(m_body, "Can't create body");

	return true;
}

PhysicsEngine *PhysicsPuppeteer::getEngine() const
{
	return m_engine;
}

b2Body *PhysicsPuppeteer::getBody() const
{
	return m_body;
}
