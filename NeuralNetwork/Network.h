#pragma once
#include <vector>

#include "Connection.h"

class Network
{
	std::vector<std::shared_ptr<Layer>> layers;
	std::vector<std::shared_ptr<Connection>> connections;

public:
	void GenerateLayers(int numLayers, int layerSize)
	{
		if (numLayers < 3) throw;

		for(int i = 0; i<numLayers; i++)
		{
			auto currentLayer = std::make_shared<Layer>();
			for (int j = 0; j<layerSize; j++)
			{
				auto neuron = std::make_shared<Neuron>();

				currentLayer->AddNeuron(neuron);
			}
			layers.push_back(currentLayer);
		}
	}

	/**
	 * \brief This will reset the weights to 0
	 */
	void GenerateConnections()
	{
		int numLayers = layers.size();
		for (int i = 0; i < numLayers; i++)
		{
			auto currentLayer = layers[i];

			auto connection = std::make_shared<Connection>();
			connection->thisLayer = currentLayer;

			if (i < numLayers - 1)
			{
				connection->nextLayer = layers[i + 1];
			}

			int layerSize = currentLayer->GetSize();
			connection->neuronConnections = std::vector<std::shared_ptr<Connection::NeuronConnection>>();

			for (int j = 0; j<layerSize; j++)
			{
				std::shared_ptr<Connection::NeuronConnection> neuronConnection = std::make_shared<Connection::NeuronConnection>();
				neuronConnection->weights = std::vector<double>(layerSize, 0.0);
				neuronConnection->neuron = currentLayer->GetNeuron(j);
				connection->neuronConnections.push_back(neuronConnection);
			}

			connections.push_back(connection);
		}
	}

	void UpdateWeights(std::vector<std::vector<std::vector<double>>> &newWeights)
	{
		int numLayers = layers.size();
		for (int i = 0; i < numLayers; i++)
		{
			auto currentLayer = layers[i];
			auto neuronConnection = connections[i];
			int connectionSize = neuronConnection->neuronConnections.size();
			for (int j = 0; j < connectionSize; j++)
			{
				int weightSize = neuronConnection->neuronConnections[j]->weights.size();
				for (int k = 0; k < weightSize; k++)
				{
					neuronConnection->neuronConnections[j]->weights[k] = newWeights[i][j][k];
				}
			}
		}
	}

	std::vector<double> CalculateOutput(std::vector<double> input)
	{
		int numLayers = connections.size();
		for (int i = 0; i < numLayers; i++)
		{
			input = this->connections[i]->CalculateOutputLayer(input);
		}

		return input;
	}
};

