#include "JsonUtils.h"
#include <fstream>

USING_NS_CC;
using namespace json11;

Json JsonUtils::LoadFromFile(std::string const& fileName)
{
	std::ifstream file(fileName);
	CCASSERT(file.is_open(), "Can't open file");

	std::string data;
	char c;
	while (file.get(c))
	{
		data.push_back(c);
	}

	std::string err;
	auto result = Json::parse(data, err);
	CCASSERT(err.empty(), err.c_str());
	return result;
}

Vec2 JsonUtils::ParseVec2(Json const& json)
{
	return Vec2(json["x"].number_value(), json["y"].number_value());
}
