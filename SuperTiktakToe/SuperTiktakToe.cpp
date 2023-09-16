// SuperTiktakToe.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "Board.h"
#include "PlayerInput.h"

class Game
{
    Board board;
    PlayerInput playerInput;

    void ProcessTurnForPlayer(Colour player)
    {
        std::cout << "Its " << ColourToString[player] << "'s turn" << std::endl;
        std::cout << "Select an empty square: " << std::endl;

        RenderBoard();

        auto userInput = playerInput.GetPlayerInput(player);
        while (!board.FillSquare(userInput.column, userInput.row, player))
        {
            std::cout << "The selected square must be empty!" << std::endl;
            userInput = playerInput.GetPlayerInput(player);
        }
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

            std::cout << std::endl;
        }
    }

public:

    void ProcessTurn()
    {
        ProcessTurnForPlayer(X);
        ProcessTurnForPlayer(O);
    }

    Colour GetWinner()
    {
        return board.EvaluateSolved();
    }

    bool GetFinished()
    {
        return GetWinner() != Blank || board.IsFull();
    }
};

int main()
{
    std::cout << "Welcome to Tic tac toe!\n";
    Game game;
    while (!game.GetFinished())
    {
        game.ProcessTurn();
    }

    std::cout << "Fininished Game. Winner: "<< game.GetWinner() << std::endl;
}

