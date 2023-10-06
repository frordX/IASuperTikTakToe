#pragma once
#include <vector>

#include "Neuron.h"

class Layer
{
	std::vector<std::shared_ptr<Neuron>> neurons;

	Layer()
	{
		neurons = std::vector<std::shared_ptr<Neuron>>();
	}
};

