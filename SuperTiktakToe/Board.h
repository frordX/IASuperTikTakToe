#pragma once
#include "Enums.h"
#include "PlayerInput.h"
class Board
{
	Colour values[3][3] = { {Blank, Blank, Blank}, {Blank, Blank, Blank}, {Blank, Blank, Blank} };
public:
	bool EvaluateSolved(Colour p)
	{
		if (p == Blank) throw;
		int counterDig1 = 3, counterDig2 = 3;
		for (int i = 0; i < 3; i++)
		{
			int counterX = 3, counterY = 3;
			for (int j = 0; j < 3; j++)
			{
				if (values[i][j] == p) counterY--;
				if (values[j][i] == p) counterX--;
			}

			if (counterX == 0 || counterY == 0) return true;

			if (values[i][i] == p) counterDig1--;
			if (values[2 - i][2 - i] == p) counterDig2--;
		}

		if (counterDig1 == 0 || counterDig2 == 0) return true;
		return false;
	}

	bool FillSquare(int x, int y, Colour p)
	{
		values[x][y] = p;
	}

	char** GetCharsToRender()
	{
		char** toReturn = 0;
		toReturn = new char* [3];
		for (int i = 0; i < 3; i++)
		{
			toReturn[i] = new char[3];
			for (int j = 0; j < 3; j++)
			{
				toReturn[i][j] = ColourToString[values[i][j]];
			}
		}

		return toReturn;
	}
};

