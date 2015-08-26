#include "Player.h"
#include "PhysicsEngine.h"
#include "NodePhysicsPuppeteer.h"
#include "AnimationKit.h"

USING_NS_CC;

Player* Player::create(PhysicsEngine *physEngine, Vec2 const& origin, bool facingLeft)
{
	Player *pRet = new (std::nothrow) Player(physEngine);
	if (pRet && pRet->init(origin, facingLeft))
	{
		pRet->autorelease();
	}
	else
	{
		CC_SAFE_DELETE(pRet);
	}
	return pRet;
}

Player::Player(PhysicsEngine *physEngine)
	: m_physEngine(physEngine)
{}

bool Player::init(Vec2 const& origin, bool facingLeft)
{
	if (!SpriteBatchNode::initWithFile("player_atlas.png"))
		return false;

	const Size idleSize(45, 63);

	m_sprite = Sprite::createWithTexture(getTexture(), Rect(Vec2(), idleSize));
	if (!m_sprite)
		return false;
	m_sprite->setAnchorPoint(Vec2(0.5f, 0.45f));
	addChild(m_sprite);

	m_idleKit = AnimationKit::create(0.2f);
	if (!m_idleKit.Keeps())
		return false;

	for (int frameNum = 0; frameNum < 3; ++frameNum)
	{
		SpriteFrame *frame = SpriteFrame::createWithTexture(getTexture(),
			Rect(Vec2(frameNum * idleSize.width, 0), idleSize));
		if (!frame)
			return false;
		m_idleKit->GetAnimation()->addSpriteFrame(frame);
	}

	if (!m_idleKit->InitAction())
		return false;

	m_sprite->runAction(m_idleKit->GetAction());
	m_sprite->setAnchorPoint(Vec2(0.5f, 0.45f));

	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	bodyDef.fixedRotation = true;
	bodyDef.position.Set(origin.x / m_physEngine->getPtmRatio(),
		origin.y / m_physEngine->getPtmRatio());
	if (!m_physEngine->createBody(bodyDef))
		CCASSERT(false, "Can't create body");

	m_puppeteer = NodePhysicsPuppeteer::create(m_sprite, bodyDef, m_physEngine);
	if (!m_puppeteer.Keeps())
		return false;

	b2PolygonShape shape;
	shape.SetAsBox(45.0f / 2 / m_physEngine->getPtmRatio(),
		51.0f / 2 / m_physEngine->getPtmRatio());

	b2FixtureDef fixtureDef;
	fixtureDef.shape = &shape;
	fixtureDef.density = 1.0f;
	fixtureDef.friction = 0.2f;
	fixtureDef.restitution = 0.0f;
	if (!m_puppeteer->getBody()->CreateFixture(&fixtureDef))
		CCASSERT(false, "Can't create fixture");

	SetFacing(facingLeft);

	return true;
}

void Player::Move(float dx)
{
	auto body = m_puppeteer->getBody();
	body->ApplyLinearImpulse(b2Vec2(dx, 0), body->GetPosition(), false);

	if (dx > 0)
	{
		SetFacing(false);
	}
	if (dx < 0)
	{
		SetFacing(true);
	}
}

void Player::Jump()
{
	auto body = m_puppeteer->getBody();
	body->ApplyLinearImpulse(b2Vec2(0, 0.04f), body->GetPosition(), false);
}

void Player::SetFacing(bool facingLeft)
{
	m_facingLeft = facingLeft;

	if (facingLeft)
	{
		m_sprite->setScaleX(-1);
	}
	else
	{
		m_sprite->setScaleX(1);
	}
}

bool Player::IsFacingLeft() const
{
	return m_facingLeft;
}
