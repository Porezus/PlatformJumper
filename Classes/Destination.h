#pragma once

#include "cocos2d.h"

namespace json11
{
	class Json;
};

struct Destination
{
	Destination(std::string const& mapName, cocos2d::Vec2 const& position);
	Destination(json11::Json const& json);

	std::string mapName;
	cocos2d::Vec2 position;
};
