#pragma once

#include "cocos2d.h"

class CameraControl
{
public:
	CameraControl(cocos2d::Size const& mapSize);
	void Update(cocos2d::Vec2 const& playerPosition, bool playerFacingLeft, float dt);
	cocos2d::Vec2 GetPosition() const;

private:
	cocos2d::Vec2 GetPositionInCamera(cocos2d::Vec2 const& scenePos) const;
	float BindCameraPositionXWithinMap(float x) const;
	float BindCameraPositionYWithinMap(float y) const;

	cocos2d::Size m_cameraSize;
	cocos2d::Size m_mapSize;

	cocos2d::Vec2 m_currentPosition;
	float m_targetPositionX;
};
