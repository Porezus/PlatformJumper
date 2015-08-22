#include "Player.h"
#include "PhysicsEngine.h"

Player* Player::create(PhysicsEngine *physEngine)
{
	Player *pRet = new (std::nothrow) Player(physEngine);
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

Player::Player(PhysicsEngine *physEngine)
	: m_physEngine(physEngine)
{}
