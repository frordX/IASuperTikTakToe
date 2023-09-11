#pragma once
#include <utility>
#include "Enums.h"

struct PlayerInputValue
{
	int column;
	int row;

	PlayerInputValue(int c, int r)
	{
		column = c;
		row = r;
	}
};

class PlayerInput
{
	bool isAgainstMachine = false;
public:
	PlayerInputValue GetPlayerInput(Colour player)
	{
		int row, column;
		if (!(isAgainstMachine && player == O))
		{
			char letter;
			std::cout << "Select column (letter)" << std::endl;
			std::cin >> letter;
			row = letter - 'A';

			std::cout << "Select row (number)" << std::endl;
			std::cin >> letter;
			column = letter - '0';
		}

		return PlayerInputValue(column, row);
	};
};


