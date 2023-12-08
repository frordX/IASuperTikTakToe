// SuperTiktakToe.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "Encoder.h"
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
        std::vector<double> inputData = Encoder::encode(game.GetBoardData(), 3);
        std::vector<double> outputData;
        if (isPlayer2turn)
        {
            outputData = network2.CalculateOutput(inputData);
        }
        else
        {
            outputData = network1.CalculateOutput(inputData);
        }

        // TODO: decode and input to game
        // TODO: put all this inside a do while(turn is not valid)
    }

    std::cout << "Fininished Game. Winner: " << ColourToString[game.GetWinner()] << std::endl;
    game.RenderBoard();
}
