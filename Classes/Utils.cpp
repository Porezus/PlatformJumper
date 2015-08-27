#include "Utils.h"

std::vector<std::string> SplitString(std::string const& str, std::string const& delimiter)
{
	std::vector<std::string> result;
	size_t startIndex = 0;

	while (startIndex < str.length())
	{
		const size_t delimiterIndex = str.find(delimiter, startIndex);
		const bool delimiterFound = (delimiterIndex != std::string::npos);
		const size_t partLength = delimiterFound ? delimiterIndex - startIndex : std::string::npos;

		result.push_back(str.substr(startIndex, partLength));
		startIndex = delimiterFound ? delimiterIndex + delimiter.length() : std::string::npos;
	}

	return result;
}
