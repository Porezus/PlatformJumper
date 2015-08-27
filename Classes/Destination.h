#pragma once

#include "cocos2d.h"
#include <iostream>

struct Destination
{
	Destination(std::string const& mapName, cocos2d::Vec2 const& position);
	Destination(std::istream &in);

	std::string mapName;
	cocos2d::Vec2 position;
};
