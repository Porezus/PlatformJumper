#include "Destination.h"
#include "RawDataUtils.h"
#include "Json\JsonUtils.h"

using namespace json11;

Destination::Destination(std::string const& mapName, cocos2d::Vec2 const& position)
	: mapName(mapName)
	, position(position)
{}

Destination::Destination(Json const& json)
	: mapName(json["map"].string_value())
	, position(JsonUtils::ParseVec2(json["pos"]))
{}
