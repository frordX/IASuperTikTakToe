// SuperTiktakToe.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include <math.h> 
#include "EncoderAndDecoder.h"
#include "../SuperTiktakToe/Game.h"
#include "../NeuralNetwork/Network.h"
#include "../NeuralNetwork/Distributor.h"
#include "../NeuralNetwork/Persistence.h"
#include "../Utils/VectorUtils.h"
#include "ConfigConstants.h"
#include "Match.h"

typedef std::vector<std::vector<std::vector<double>>> network;
const int leagueSize = 10;
const int leagueSizeHalf = leagueSize / 2;


/// <summary>
/// this method will randomly distribute the weights of each network of the first half of the league and assign the new network to the same position + half the leagues' size + 1
/// The network in the first position will be distributed two times and the netowrk in the middle-1 position won't be distributed at all
/// </summary>
/// <param name="league"></param>
/// <param name="distributionPower"></param>
void distributeTopHalf(std::vector<network>& league, int distributionPower)
{
    league[leagueSizeHalf] = Distributor::distribute(league[0], 10 * sqrt(++distributionPower));

    for (int i = 1; i < leagueSizeHalf; i++)
    {
        auto contestantWeightsVector = Distributor::distribute(league[i - 1], 10 * sqrt(++distributionPower));

        league[i + leagueSizeHalf] = contestantWeightsVector;
    }
}

std::vector<network> retrieveOrGenerateLeague()
{
    std::vector<network> league = std::vector<network>(leagueSize);

    for (int i = 0; i < leagueSizeHalf; i++)
    {
        auto currentBestWeightsVector = Persistence::retrieveVectorFromFile(filepath + std::to_string(i + 1) + filepathExtension, boardSizeSqare + 1, boardSizeSqare);
        if (currentBestWeightsVector.empty())
        {
            currentBestWeightsVector = std::vector<std::vector<std::vector<double>>>(boardSizeSqare, std::vector<std::vector<double>>(boardSizeSqare + 1, std::vector<double>(boardSizeSqare + 1, 1.0)));
            auto contestantWeightsVector = Distributor::distribute(currentBestWeightsVector, 10);
        }

        league[i] = currentBestWeightsVector;
    }
    
    distributeTopHalf(league, 0);

    return league;
}

/// <summary>
/// Returns: a vector of ints, the same size as the input vector that contains in each position 'i' the amount of times that a network in position 'i'
/// of the input vector has won
/// </summary>
std::vector<int> playLegaue(std::vector<network>& league)
{
    std::vector<int> resultsVector = std::vector<int>(league.size(), 0);
    for (int i = 0; i < leagueSize; i++)
    {
        for (int j = 0; j < leagueSize; j++)
        {
            int winner = Match::playGame(league[i], league[j]);
            if (winner == Colour::X) resultsVector[i] += 3;
            else if (winner == Colour::O) resultsVector[j] += 3;
            else
            {
                resultsVector[i]++;
                resultsVector[j]++;
            }
        }
    }

    return resultsVector;
}

/// <summary>
/// Saves and orders the networks. It only saves an n amount, being n the size of positionsVector. 
/// It saves the networks in the positions determined by this vector
/// </summary>
/// <param name="positionsVector"></param>
/// <param name="networks"></param>
/// <returns></returns>
std::vector<network> saveAndReturn5BestNetworks(std::vector<int> positionsVector, std::vector<network> networks)
{
    std::vector<network> resultLeague = std::vector<network>(leagueSize);
    for (int i = 0; i < positionsVector.size(); i++)
    {
        int position = positionsVector[i];
        Persistence::saveVectorToFile(networks[position], filepath + std::to_string(i + 1) + filepathExtension);
        resultLeague[i] = networks[position];
    }

    return resultLeague;
}

int main()
{
    int numiterations = 0;
    int inverseDelta = 0;

    auto leagueOfNetworks = retrieveOrGenerateLeague();
    while (true)
    {
        std::cout << "Welcome to Tic tac toe! Initializing neural network on iteration:" << ++numiterations <<"\n";

        
        auto results = playLegaue(leagueOfNetworks);

        auto fiveBestResultsPositions = Utils::getNHighestValuesIndices(results, 5);
        leagueOfNetworks = saveAndReturn5BestNetworks(fiveBestResultsPositions, leagueOfNetworks);


        // We check how different this round's results are from the last ones
        int delta = 0;
        for (int i = 0; i < fiveBestResultsPositions.size(); i++)
        {
            delta += std::abs(i + 1 - fiveBestResultsPositions[i]);
        }

        inverseDelta = 26 - delta;

        distributeTopHalf(leagueOfNetworks, inverseDelta);
    }
}