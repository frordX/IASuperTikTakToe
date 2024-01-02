#pragma once
#include <vector>
#include "../SuperTiktakToe/Enums.h"
#include "../SuperTiktakToe/PlayerInput.h"

class Encoder
{
public:
	static std::vector<double> encode(char** data, int boardSize, int playerValue)
	{
		auto toReturn = std::vector<double>(boardSize * boardSize + 1);
		for (int i = 0; i < boardSize; i++)
		{
			for (int j = 0; j<boardSize; j++)
			{
				toReturn[i * boardSize + j] = StringToColour.at(data[i][j]);
			}
		}

		toReturn[toReturn.size() - 1] = playerValue;
		return toReturn;
	}
};

class Decoder
{
public:
	static PlayerInputValue decode(static std::vector<double> val, int boardSize, int numTries)
	{
		int position = std::distance(val.begin(), max_element(val.begin(), val.end()));
		position += numTries;
		if (numTries > 0) position = position % (boardSize * boardSize);
		PlayerInputValue result(position / boardSize, position % boardSize);
		return result;
	}
};