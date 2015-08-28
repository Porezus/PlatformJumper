#include "Destination.h"
#include "RawDataUtils.h"

Destination::Destination(std::string const& mapName, cocos2d::Vec2 const& position)
	: mapName(mapName)
	, position(position)
{}

Destination::Destination(std::istream &in)
	: mapName(RawData::ReadStringAdv(in))
	, position(RawData::ReadVec2(in))
{}
