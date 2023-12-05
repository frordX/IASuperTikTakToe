#pragma once
#include <memory>

#include "Layer.h"

class Connection
{
public:
	class NeuronConnection
	{
	public:
		// Weights connected to the previous layer
		std::vector<double> weights;

		// the neuron in thisLayer
		std::shared_ptr<Neuron> neuron;
	};

	std::shared_ptr<Layer> thisLayer;

	std::vector<std::shared_ptr<NeuronConnection>> neuronConnections;

	std::shared_ptr<Layer> nextLayer;

	std::vector<double> CalculateOutputLayer(std::vector<double>& input)
	{
		int layerSize = neuronConnections.size();
		std::vector<double> output = std::vector<double>(layerSize);
		for(int i = 0; i<layerSize;i++)
		{
			auto currentNeuron = neuronConnections[i];
			int numberOfNeuronsInPreviousLayer = currentNeuron->weights.size();
			if (numberOfNeuronsInPreviousLayer != input.size()) throw;

			int sum = 0; // currentNeuron->neuron->currentValue* currentNeuron->neuron->currentValueWeight;
			for (int j = 0; j<numberOfNeuronsInPreviousLayer; j++)
			{
				sum += currentNeuron->weights[j] * input[j];
			}

			output[i] = sum;
		}

		return output;
	}
};