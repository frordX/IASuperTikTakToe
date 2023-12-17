#pragma once
#include "Enums.h"
#include "PlayerInput.h"
class Board
{
	Colour values[3][3] = { {Blank, Blank, Blank}, {Blank, Blank, Blank}, {Blank, Blank, Blank} };
public:
	bool EvaluateSolvedForColour(Colour p)
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
			if (values[2 - i][i] == p) counterDig2--;
		}

		if (counterDig1 == 0 || counterDig2 == 0) return true;
		return false;
	}

	Colour EvaluateSolved()
	{
		if (EvaluateSolvedForColour(O)) return O;
		if (EvaluateSolvedForColour(X)) return X;
		return Blank;
	}

	bool IsFull()
	{
		int bCounter = 0;
		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < 3; j++)
			{
				if (values[i][j] != Blank) bCounter++;
			}
		}

		return bCounter == 9;
	}

	bool FillSquare(int column, int row, Colour p)
	{
		if (values[column][row] == Blank && p != Blank)
		{
			values[column][row] = p;
			return true;
		}

		return false;
	}

	char** GetBoardData()
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

