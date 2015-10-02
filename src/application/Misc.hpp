#pragma once

#include <vector>
#include <string>


namespace misc
{
	static std::vector<int> getAllInstancesOfChar(const std::string& string, const char& character)
	{
		std::vector<int> indices;
		for (int i = 0; i < string.size(); ++i)
		{
			if (string[i] == character)
				indices.push_back(i);
		}

		return indices;
	}
}

