#pragma once
#include <vector>
#include "EncoderAndDecoder.h"
#include "../SuperTiktakToe/Enums.h"
#include "../SuperTiktakToe/PlayerInput.h"
#include "../NeuralNetwork/Network.h"
#include "../SuperTiktakToe/Game.h"
#include "ConfigConstants.h"
namespace Match
{
    Colour playGame(std::vector<std::vector<std::vector<double>>> weightsX, std::vector<std::vector<std::vector<double>>> weightsO)
    {
        // TODO: Network 1 and two should be a vector or an array
        Network network1;
        network1.GenerateLayers(9, 10);
        network1.GenerateConnections();
        network1.UpdateWeights(weightsX);

        Network network2;
        network2.GenerateLayers(9, 10);
        network2.GenerateConnections();
        network2.UpdateWeights(weightsO);

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

        return winner;
    }

    /// <summary>
    /// Plays two games, one with the neural networks on each colour
    /// </summary>
    /// <param name="weightsKing"></param>
    /// <param name="weightsContestant"></param>
    /// <returns>Whether the contestant neural network has won both games</returns>
    bool playMatch(std::vector<std::vector<std::vector<double>>> weightsKing, std::vector<std::vector<std::vector<double>>> weightsContestant)
    {
        std::cout << "Starting game 1" << "\n";
        auto winnerGame1 = playGame(weightsKing, weightsContestant);
        std::cout << "Starting game 2" << "\n";
        auto winnerGame2 = playGame(weightsContestant, weightsKing);
        std::cout << "Winner game 1" << winnerGame1 << "\nWinner game 2: " << winnerGame2 << "\n";
        return winnerGame1 == Colour::O && winnerGame2 == Colour::X;
    }
}