// SuperTiktakToe.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "../SuperTiktakToe/Game.h"
#include "../NeuralNetwork/Network.h"


int main()
{
    std::cout << "Welcome to Tic tac toe! Initializing neural network\n";

    // TODO: Network 1 and two should be a vector or an array
    Network network1;
    network1.GenerateLayers(9, 9);
    network1.GenerateConnections();

    Network network2;
    network2.GenerateLayers(9, 9);
    network2.GenerateConnections();
    auto megaWeightsVector = std::vector<std::vector<std::vector<double>>>(9, std::vector<std::vector<double>>(9, std::vector<double>(9, 1.0)));
    network2.UpdateWeights(megaWeightsVector);

    bool isPlayer2turn = false;
    Game game;
    while (!game.GetFinished())
    {
        // TODO: Convert game board into 9 inputs game.boa
        if (isPlayer2turn)
        {
	        network2.CalculateOutput()
        }
        else
        {
            network1.CalculateOutput()
        }
        game.ProcessTurn();
    }

    std::cout << "Fininished Game. Winner: " << ColourToString[game.GetWinner()] << std::endl;
    game.RenderBoard();
}
