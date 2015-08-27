#pragma once

#include <iostream>
#include "cocos2d.h"

namespace RawData
{
	const char STOP_CHAR = '#';
	size_t ReadSizeUntilStopChar(std::istream &in);
	std::string ReadString(std::istream &in);
	float ReadFloat(std::istream &in);
	cocos2d::Vec2 ReadVec2(std::istream &in);
}
