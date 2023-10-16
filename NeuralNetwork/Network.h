#pragma once
#include <vector>

#include "Connection.h"

class Network
{
	std::vector<std::shared_ptr<Layer>> layers;
	std::vector<std::shared_ptr<Connection>> connections;

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

	void GenerateConnections()
	{
		int numLayers = layers.size();
		for (int i = 0; i < numLayers; i++)
		{
			auto currentLayer = layers[i];

			auto connection = std::make_shared<Connection>();
			connection->previousLayer = currentLayer;

			if (i < numLayers - 1)
			{
				connection->nextLayer = layers[i + 1];
			}

			int layerSize = currentLayer->GetSize();
			connection->weights = new std::vector<double>(layerSize, 0);
		}
	}
};

