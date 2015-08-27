#include "RawDataUtils.h"
#include <string>
#include <vector>

using namespace std;

string ReadStrUntilStopChar(istream &in)
{
	string result;

	char tmpChar;
	while (in.get(tmpChar))
	{
		result.push_back(tmpChar);

		if (tmpChar == RawData::STOP_CHAR)
			break;
	}

	if (result.back() != RawData::STOP_CHAR)
		throw runtime_error("No stop character found");

	result.pop_back();
	return result;
}

size_t RawData::ReadSizeUntilStopChar(istream &in)
{
	return stoul(ReadStrUntilStopChar(in));
}

string RawData::ReadString(istream &in)
{
	const size_t strLen = ReadSizeUntilStopChar(in);
	vector<char> result(strLen + 1, '\0');
	in.read(result.data(), strLen);
	return string(result.data());
}

float RawData::ReadFloat(istream &in)
{
	return stof(ReadStrUntilStopChar(in));
}

cocos2d::Vec2 RawData::ReadVec2(istream &in)
{
	return cocos2d::Vec2(ReadFloat(in), ReadFloat(in));
}
