#pragma once
#include <vector>

class Encoder
{
public:
	static std::vector<double> encode(char** data, int boardSize)
	{
		auto toReturn = std::vector<double>(boardSize * boardSize);
		for (int i = 0; i < boardSize; i++)
		{
			for (int j = 0; j<boardSize; j++)
			{
				toReturn[i * boardSize + j] = data[i][j];
			}
		}

		return toReturn;
	}

};
