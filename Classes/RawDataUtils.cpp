#include "RawDataUtils.h"
#include <string>
#include <vector>

using namespace std;

void RawData::SkipWhitespaces(istream &in)
{
	if (in.peek() == '\n' || in.peek() == '\t')
		in.get();
}

string RawData::ReadString(istream &in)
{
	SkipWhitespaces(in);
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

size_t RawData::ReadSizeT(istream &in)
{
	return stoul(ReadString(in));
}

string RawData::ReadStringAdv(istream &in)
{
	const size_t strLen = ReadSizeT(in);
	vector<char> result(strLen + 1, '\0');
	in.read(result.data(), strLen);
	return string(result.data());
}

float RawData::ReadFloat(istream &in)
{
	return stof(ReadString(in));
}

int RawData::ReadInt(istream &in)
{
	return stoi(ReadString(in));
}

cocos2d::Vec2 RawData::ReadVec2(istream &in)
{
	const float x = ReadFloat(in);
	const float y = ReadFloat(in);
	return cocos2d::Vec2(x, y);
}

cocos2d::Size RawData::ReadSize(istream &in)
{
	const float w = ReadFloat(in);
	const float h = ReadFloat(in);
	return cocos2d::Size(w, h);
}

cocos2d::Rect RawData::ReadRect(istream &in)
{
	const cocos2d::Vec2 vec2 = ReadVec2(in);
	const cocos2d::Size size = ReadSize(in);
	return cocos2d::Rect(vec2, size);
}
