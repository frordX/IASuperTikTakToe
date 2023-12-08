#pragma once
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

    void ProcessTurnForPlayer(Colour player, PlayerInputValue input)
    {
        std::cout << "Its " << ColourToString[player] << "'s turn" << std::endl;
        std::cout << "Select an empty square: " << std::endl;

        RenderBoard();

        if (!board.FillSquare(input.column, input.row, player)) throw;
    }

public:

    // Todo: improve for nine boards
    void RenderBoard()
    {
        auto chars = board.GetBoardData();

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

    void ProcessTurn()
    {
        if (!GetFinished())
        {
            ProcessTurnForPlayer(X);
        }

        if (!GetFinished())
        {
            ProcessTurnForPlayer(O);
        }
    }

    Colour GetWinner()
    {
        return board.EvaluateSolved();
    }

    bool GetFinished()
    {
        return GetWinner() != Blank || board.IsFull();
    }

    char** GetBoardData()
    {
return board.GetBoardData();
    }
};