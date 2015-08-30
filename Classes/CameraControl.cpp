#include "CameraControl.h"

USING_NS_CC;

CameraControl::CameraControl(Size const& mapSize)
	: m_cameraSize(Director::getInstance()->getOpenGLView()->getFrameSize())
	, m_mapSize(mapSize)
	, m_targetPositionX(0)
{}

void CameraControl::Update(Vec2 const& playerPosition, bool playerFacingLeft, float dt)
{
	const float DEAD_ZONE_WIDTH = m_cameraSize.width * 0.25f;
	if (GetPositionInCamera(playerPosition).x < DEAD_ZONE_WIDTH)
	{
		m_currentPosition.x += (DEAD_ZONE_WIDTH - GetPositionInCamera(playerPosition).x);
	}
	if (GetPositionInCamera(playerPosition).x > m_cameraSize.width - DEAD_ZONE_WIDTH)
	{
		m_currentPosition.x -= (GetPositionInCamera(playerPosition).x - (m_cameraSize.width - DEAD_ZONE_WIDTH));
	}
	m_currentPosition.x = BindCameraPositionXWithinMap(m_currentPosition.x);

	const float KEEP_VISIBLE_GAP = m_cameraSize.width * 0.7f;
	if (!playerFacingLeft && m_cameraSize.width - GetPositionInCamera(playerPosition).x < KEEP_VISIBLE_GAP)
	{
		m_targetPositionX = m_currentPosition.x - (KEEP_VISIBLE_GAP - (m_cameraSize.width - GetPositionInCamera(playerPosition).x));
	}
	if (playerFacingLeft && GetPositionInCamera(playerPosition).x < KEEP_VISIBLE_GAP)
	{
		m_targetPositionX = m_currentPosition.x + (KEEP_VISIBLE_GAP - GetPositionInCamera(playerPosition).x);
	}
	m_targetPositionX = BindCameraPositionXWithinMap(m_targetPositionX);

	const float CAM_MOVE_SPEED = 300.0f;
	if (m_currentPosition.x < m_targetPositionX)
	{
		m_currentPosition.x += (CAM_MOVE_SPEED * dt);
	}
	if (m_currentPosition.x > m_targetPositionX)
	{
		m_currentPosition.x -= (CAM_MOVE_SPEED * dt);
	}

	const float UPPER_DEAD_ZONE_HEIGHT = 0.1f * m_cameraSize.height;
	if (m_cameraSize.height - GetPositionInCamera(playerPosition).y < UPPER_DEAD_ZONE_HEIGHT)
	{
		m_currentPosition.y -= (UPPER_DEAD_ZONE_HEIGHT - (m_cameraSize.height - GetPositionInCamera(playerPosition).y));
	}
	const float LOWER_DEAD_ZONE_HEIGHT = 0.3f * m_cameraSize.height;
	if (GetPositionInCamera(playerPosition).y < LOWER_DEAD_ZONE_HEIGHT)
	{
		m_currentPosition.y += (LOWER_DEAD_ZONE_HEIGHT - GetPositionInCamera(playerPosition).y);
	}
	m_currentPosition.y = BindCameraPositionYWithinMap(m_currentPosition.y);
}

Vec2 CameraControl::GetPosition() const
{
	return m_currentPosition;
}

Vec2 CameraControl::GetPositionInCamera(Vec2 const& scenePos) const
{
	return scenePos + m_currentPosition;
}

float CameraControl::BindCameraPositionXWithinMap(float x) const
{
	if (x > 0)
		return 0;

	if (-x + m_cameraSize.width > m_mapSize.width)
		return -(m_mapSize.width - m_cameraSize.width);

	return x;
}

float CameraControl::BindCameraPositionYWithinMap(float y) const
{
	if (y > 0)
		return 0;

	if (-y + m_cameraSize.height > m_mapSize.height)
		return -(m_mapSize.height - m_cameraSize.height);

	return y;
}
