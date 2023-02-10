//
// Created by zitri on 08.02.2023.
//

#ifndef NEURALNET_LAYER_H
#define NEURALNET_LAYER_H

#include <vector>
#include "Neuron.h"

class Layer
{
	public:
		Layer(int layerCount, int numOutputs);
		~Layer() = default;

		[[nodiscard]] std::vector<Neuron>& getNeurons() { return m_vNeurons; }

		int getNeuronCount() { return static_cast<int>(m_vNeurons.size()); }

	private:
		Neuron              m_bias;
		std::vector<Neuron> m_vNeurons;
};


#endif //NEURALNET_LAYER_H
