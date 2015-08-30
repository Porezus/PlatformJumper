#pragma once

#include "cocos2d.h"
#include "Json\json11.hpp"

namespace JsonUtils
{
	json11::Json LoadFromFile(std::string const& fileName);
	cocos2d::Vec2 ParseVec2(json11::Json const& json);
	cocos2d::Rect ParseRect(json11::Json const& json);
};
