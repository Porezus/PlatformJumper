#include "Player.h"
#include "Physics\PhysicsEngine.h"
#include "PlayerPuppeteer.h"
#include "AnimationKit.h"
#include "Json\JsonUtils.h"

USING_NS_CC;
using namespace json11;

Player* Player::create(PhysicsEngine *physEngine, Json const& json)
{
	Player *pRet = new (std::nothrow) Player(physEngine);
	if (pRet && pRet->init(json))
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
	, m_running(false)
	, m_onGround(false)
{}

bool Player::init(Json const& json)
{
	if (!SpriteBatchNode::initWithFile("gfx/player_atlas.png"))
		return false;

	const Size idleSize(45, 63);
	const Size runSize(75, 90);

	m_sprite = Sprite::createWithTexture(getTexture(), Rect(Vec2(), idleSize));
	if (!m_sprite)
		return false;
	m_sprite->setAnchorPoint(Vec2(0.5f, 0.45f));
	addChild(m_sprite);

	m_idleKit = AnimationKit::create(0.2f);
	if (!m_idleKit)
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
	m_idleKit->m_anchor = Vec2(0.5f, 0.45f);

	m_runKit = AnimationKit::create(0.2f);
	if (!m_runKit)
		return false;

	for (int frameNum = 0; frameNum < 4; ++frameNum)
	{
		SpriteFrame *frame = SpriteFrame::createWithTexture(getTexture(),
			Rect(Vec2(frameNum * runSize.width, idleSize.height), runSize));
		if (!frame)
			return false;
		m_runKit->GetAnimation()->addSpriteFrame(frame);
	}

	if (!m_runKit->InitAction())
		return false;
	m_runKit->m_anchor = Vec2(0.3f, 0.3f);

	SetAnimation(m_idleKit);

	auto origin = JsonUtils::ParseVec2(json["origin"]);

	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	bodyDef.fixedRotation = true;
	bodyDef.position.Set(origin.x / m_physEngine->getPtmRatio(),
		origin.y / m_physEngine->getPtmRatio());
	if (!m_physEngine->createBody(bodyDef))
		CCASSERT(false, "Can't create body");

	m_puppeteer = PlayerPuppeteer::create(m_sprite, bodyDef, m_physEngine);
	if (!m_puppeteer)
		return false;

	const Size playerSize(45, 51);

	b2PolygonShape shape;
	shape.SetAsBox(playerSize.width / 2 / m_physEngine->getPtmRatio(),
		playerSize.height / 2 / m_physEngine->getPtmRatio());

	b2FixtureDef fixtureDef;
	fixtureDef.shape = &shape;
	fixtureDef.density = 1.0f;
	fixtureDef.friction = 0.2f;
	fixtureDef.restitution = 0.1f;
	if (!m_puppeteer->getBody()->CreateFixture(&fixtureDef))
		CCASSERT(false, "Can't create fixture");

	shape.SetAsBox(playerSize.width / 4 / m_physEngine->getPtmRatio(),
		2.5f / m_physEngine->getPtmRatio(),
		b2Vec2(0, -playerSize.height / 2 / m_physEngine->getPtmRatio()),
		0.0f);

	b2FixtureDef footSensor;
	footSensor.shape = &shape;
	footSensor.isSensor = true;
	if (!m_puppeteer->getBody()->CreateFixture(&footSensor))
		CCASSERT(false, "Can't create fixture");

	SetFacing(json["facing"].string_value() == "left");

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

	if (!m_running)
	{
		m_running = true;
		SetAnimation(m_runKit);
	}
}

void Player::Stop()
{
	if (m_running)
	{
		m_running = false;
		SetAnimation(m_idleKit);
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

Vec2 Player::GetSpritePosition() const
{
	return m_sprite->getPosition();
}

void Player::SetAnimation(AnimationKit *kit)
{
	m_sprite->stopAllActions();
	m_sprite->runAction(kit->GetAction());
	m_sprite->setAnchorPoint(kit->m_anchor);
}
