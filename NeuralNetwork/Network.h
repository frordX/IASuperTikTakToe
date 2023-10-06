#pragma once
#include <vector>

#include "Connection.h"

class Network
{
	std::vector<std::shared_ptr<Layer>> layers;
	std::vector<std::shared_ptr<Connection>> connections;

	void generateLayers(int numLayers, int layerSize)
	{
		if (numLayers < 3) throw;

		for(int i = 0; i<numLayers; i++)
		{
			auto currentLayer = std::make_shared<Layer>();
			for (int j = 0; j<layerSize; j++)
			{
				auto neuron = std::make_shared<Neuron>();

				currentLayer.
			}
			layers.push_back(currentLayer);
		}
	}
};

