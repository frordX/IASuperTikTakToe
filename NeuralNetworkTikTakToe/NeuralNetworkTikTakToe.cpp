// SuperTiktakToe.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "EncoderAndDecoder.h"
#include "../SuperTiktakToe/Game.h"
#include "../NeuralNetwork/Network.h"


int main()
{
    std::cout << "Welcome to Tic tac toe! Initializing neural network\n";

    // TODO: Network 1 and two should be a vector or an array
    Network network1;
    network1.GenerateLayers(9, 10);
    network1.GenerateConnections();

    Network network2;
    network2.GenerateLayers(9, 10);
    network2.GenerateConnections();
    auto megaWeightsVector = std::vector<std::vector<std::vector<double>>>(9, std::vector<std::vector<double>>(10, std::vector<double>(10, 1.0)));
    network2.UpdateWeights(megaWeightsVector);

    bool isPlayer2turn = false;
    Game game;
    while (!game.GetFinished())
    {
        std::vector<double> outputData;
        if (isPlayer2turn)
        {
            std::vector<double> inputData = Encoder::encode(game.GetBoardData(), 3, 0);
            outputData = network2.CalculateOutput(inputData);
    }
        else
        {
            std::vector<double> inputData = Encoder::encode(game.GetBoardData(), 3, 1);
            outputData = network1.CalculateOutput(inputData);
        }

        // decode and input to game
        int numTries = 0;
        auto output = Decoder::decode(outputData, 3, numTries);
        while (!game.ProcessTurnForPlayer(isPlayer2turn ? Colour::O : Colour::X, output))
        {
            output = Decoder::decode(outputData, 3, ++numTries);
        }

        isPlayer2turn = !isPlayer2turn;
        game.RenderBoard();
    }

    std::cout << "Fininished Game. Winner: " << ColourToString[game.GetWinner()] << std::endl;
    game.RenderBoard();
}
