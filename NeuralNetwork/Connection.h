#pragma once
#include <memory>

#include "Layer.h"

class Connection
{
	std::shared_ptr<Layer> previousLayer;
	std::vector<double> weights;

	std::shared_ptr<Neuron> neuron;
};

