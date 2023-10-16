#pragma once
#include <vector>

#include "Neuron.h"

class Layer
{
	std::vector<std::shared_ptr<Neuron>> neurons;
public:
	Layer()
	{
		neurons = std::vector<std::shared_ptr<Neuron>>();
	}

	void AddNeuron(std::shared_ptr<Neuron> neuron)
	{
		neurons.push_back(neuron);
	}

	int GetSize() { return neurons.size(); }
};

