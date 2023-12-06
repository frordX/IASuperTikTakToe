// SuperTiktakToe.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "../SuperTiktakToe/Game.h"

int main()
{
    std::cout << "Welcome to Tic tac toe!\n";
    Game game;
    while (!game.GetFinished())
    {
        game.ProcessTurn();
    }

    std::cout << "Fininished Game. Winner: " << ColourToString[game.GetWinner()] << std::endl;
    game.RenderBoard();
}
