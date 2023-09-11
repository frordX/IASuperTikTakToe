// SuperTiktakToe.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "Board.h"

class Game
{
    Board board;

    void ProcessTurnForPlayer(Colour player)
    {
        std::cout << "Its " << ColourToString[player] << "'s turn" << std::endl;
        std::cout << "Select an empty square: " << std::endl;

        RenderBoard();
    }

    // To improve for nine boards
    void RenderBoard()
    {
        auto chars = board.GetCharsToRender();

        std::cout << "  ";
        for (int j = 0; j < 3; j++)
        {
            char c = 'A' + j;
            std::cout << c;
            if (j < 2) std::cout << ' ';
        }

        std::cout << std::endl;

        for (int i = 0; i < 3; i++)
        {
            char c = '0' + i;
            std::cout << c << ' ';
            for (int j = 0; j < 3; j++)
            {
                std::cout << chars[i][j];
                if (j < 2) std::cout << ' ';
            }

            if (i < 2) std::cout << std::endl;
        }
    }

public:

    void ProcessTurn()
    {
        ProcessTurnForPlayer(X);
    }
};

int main()
{
    std::cout << "Welcome to Tic tac toe!\n";
    Game game;
    game.ProcessTurn();
}

