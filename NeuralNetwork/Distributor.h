#pragma once
#include <vector>
#include <random>
#include <chrono>

namespace Distributor
{
	std::vector<std::vector<std::vector<double>>> distribute(std::vector<std::vector<std::vector<double>>>& weights)
	{
		unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
		std::default_random_engine generator(seed);

		auto iSize = weights.size();
		if (iSize == 0) return weights;
		auto jSize = weights[0].size();
		if (jSize == 0) return weights;
		auto kSize = weights[0][0].size();

		std::vector<std::vector<std::vector<double>>> weightsToReturn = std::vector<std::vector<std::vector<double>>>(iSize, std::vector<std::vector<double>>(jSize, std::vector<double>(kSize, 1.0)));

		for (int i = 0; i < iSize; i++)
		{
			for (int j = 0; j < jSize; j++)
			{
				for (int k = 0; k < kSize; k++)
				{
					std::normal_distribution<double> distribution(weights[i][j][k], 15);
					weightsToReturn[i][j][k] = distribution(generator);
				}
			}
		}

		return weightsToReturn;
	}
}