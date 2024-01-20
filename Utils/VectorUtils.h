#pragma once
#include <vector>
#include <algorithm>


namespace Utils
{
	std::vector<int> getNHighestValuesIndices(const std::vector<int> values, const int n)
	{
		int valuesSize = values.size();
		std::vector<std::pair<double, double > >vec = std::vector<std::pair<double, double > >(0);
		for (int i = 0; i < valuesSize; i++) {
			vec.push_back(std::make_pair(values[i], i));
		}

		std::sort(vec.begin(), vec.end());

		std::vector<int> resultVector = std::vector<int>(n);
		for (int i = 0; i < n; i++) {
			resultVector[i] = vec[i].second;
		}

		return resultVector;
	}
}