//
// Created by zitri on 08.02.2023.
//

#include "Layer.h"
#include <iostream>

Layer::Layer(int layerCount, int numOutputs)
	: m_bias(numOutputs, 0)
{
	std::cout << "Made a Neuron!" << std::endl;

	// Create the neurons in the layer
	for (int i = 0; i < layerCount; i++)
	{
		m_vNeurons.emplace_back(numOutputs, i);
		std::cout << "Made a Neuron! " << i << std::endl;
	}
}

