// SuperTiktakToe.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "EncoderAndDecoder.h"
#include "../SuperTiktakToe/Game.h"
#include "../NeuralNetwork/Network.h"
#include "../NeuralNetwork/Distributor.h"
#include "../NeuralNetwork/Persistence.h"

const std::string filepath = "TikTakToeAI/data.bin";
const int boardSize = 3;
const int boardSizeSqare = boardSize*boardSize;
int main()
{
    auto megaWeightsVector = Persistence::retrieveVectorFromFile(filepath, boardSizeSqare+1, boardSizeSqare);
    if (megaWeightsVector.empty())
    {
        megaWeightsVector = std::vector<std::vector<std::vector<double>>>(boardSizeSqare, std::vector<std::vector<double>>(boardSizeSqare+1, std::vector<double>(boardSizeSqare+1, 1.0)));
    }

    int numiterations = 0;
    while (true)
    {
        std::cout << "Welcome to Tic tac toe! Initializing neural network on iteration:" << ++numiterations <<"\n";

        // TODO: Network 1 and two should be a vector or an array
        Network network1;
        network1.GenerateLayers(9, 10);
        network1.GenerateConnections();
        network1.UpdateWeights(megaWeightsVector);

        Network network2;
        network2.GenerateLayers(9, 10);
        network2.GenerateConnections();
        auto megaWeightsVector2 = Distributor::distribute(megaWeightsVector);
        network2.UpdateWeights(megaWeightsVector2);

        bool isPlayer2turn = false;
        Game game;
        while (!game.GetFinished())
        {
            std::vector<double> outputData;
            if (isPlayer2turn)
            {
                std::vector<double> inputData = Encoder::encode(game.GetBoardData(), boardSize, 0);
                outputData = network2.CalculateOutput(inputData);
            }
            else
            {
                std::vector<double> inputData = Encoder::encode(game.GetBoardData(), boardSize, 1);
                outputData = network1.CalculateOutput(inputData);
            }

            // decode and input to game
            int numTries = 0;
            auto output = Decoder::decode(outputData, boardSize, numTries);
            while (!game.ProcessTurnForPlayer(isPlayer2turn ? Colour::O : Colour::X, output))
            {
                output = Decoder::decode(outputData, boardSize, ++numTries);

                if (numTries > 9)
                {
                    game.RenderBoard();
                    output = Decoder::decode(outputData, boardSize, ++numTries);
                    throw;
                }
            }

            isPlayer2turn = !isPlayer2turn;
            game.RenderBoard();
        }

        auto winner = game.GetWinner();
        std::cout << "Fininished Game. Winner: " << ColourToString[winner] << std::endl;
        game.RenderBoard();

        if (winner == Colour::O)
        {
            megaWeightsVector = megaWeightsVector2;
            Persistence::saveVectorToFile(megaWeightsVector, filepath);
        }

        if (numiterations % 15 == 0) Persistence::saveVectorToFile(megaWeightsVector, filepath);
    }
}
