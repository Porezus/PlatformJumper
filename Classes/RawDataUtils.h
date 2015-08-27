#pragma once

#include <fstream>

namespace RawData
{
	const char STOP_CHAR = '#';
	size_t ReadSizeUntilStopChar(std::istream &in);
	std::string ReadString(std::istream &in);
	float ReadFloat(std::istream &in);
}
