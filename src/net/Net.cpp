//
// Created by zitri on 08.02.2023.
//

#include "Net.h"
#include <cassert>
#include <cmath>

[[maybe_unused]] Net::Net(const std::vector<int>& topology)
	: m_dError(0.0f)
	, m_dRecentAverageError(0.0f)
	, m_dRecentAverageSmoothingFactor(100.0f)
{
	// Create layers
	for (int layerId = 0; layerId < topology.size(); ++layerId)
	{
		const int numOutputs = layerId == topology.size() - 1 ? 0 : topology[layerId + 1];
		m_vLayers.emplace_back(topology[layerId], numOutputs);
	}

	// Force the bias node's output to 1.0 (it was the last neuron pushed in this layer):
	m_vLayers.back().getNeurons().back().setOutputVal(1.0f);
}

void Net::feedForward(const std::vector<float>& inputVals)
{
	assert(inputVals.size() == m_vLayers[0].getNeuronCount());

	auto& neurons = m_vLayers[0].getNeurons();
	for (int i = 0; i < inputVals.size(); ++i)
		neurons[i].setOutputVal(inputVals[i]);

	for (int layerId = 1; layerId < m_vLayers.size(); ++layerId)
	{
		auto& prevLayer = m_vLayers[layerId - 1];
		for (auto & n : m_vLayers[layerId].getNeurons())
			n.feedForward(prevLayer);
	}
}

void Net::backProp(const std::vector<float>& targetVals)
{
	// Calculate overall net error (RMS of output neuron errors)

	auto& outputLayer = m_vLayers.back();
	m_dError = 0.0f;

	for (int n = 0; n < outputLayer.getNeurons().size(); ++n)
	{
		float delta = targetVals[n] - outputLayer.getNeurons()[n].getOutputVal();
		m_dError += delta * delta;
	}
	m_dError /= static_cast<double>(outputLayer.getNeurons().size());
	m_dError   = std::sqrt(m_dError);

	// Implement a recent average measurement
	m_dRecentAverageError = (m_dRecentAverageError * m_dRecentAverageSmoothingFactor + m_dError) /
	                        (m_dRecentAverageSmoothingFactor + 1.0);

	// Calculate output layer gradients
	for (int n = 0; n < outputLayer.getNeurons().size(); ++n)
		outputLayer.getNeurons()[n].calcOutputGradients(targetVals[n]);

	// Calculate hidden layer gradients
	for (int layerId = static_cast<int>(m_vLayers.size()) - 2; layerId > 0; --layerId)
	{
		auto& hiddenLayer = m_vLayers[layerId];
		auto& nextLayer   = m_vLayers[layerId + 1];

		for (auto& n: hiddenLayer.getNeurons())
			n.calcHiddenGradients(nextLayer);
	}

	// For all layers from outputs to first hidden layer,
	// Update connection weights
	for (int layerId = static_cast<int>(m_vLayers.size()) - 1; layerId > 0; --layerId)
	{
		auto& layer     = m_vLayers[layerId];
		auto& prevLayer = m_vLayers[layerId - 1];

		for (auto& n: layer.getNeurons())
			n.updateInputWeights(prevLayer);
	}
}

void Net::getResults(std::vector<float>& resultVals)
{
	resultVals.clear();

	for (const Neuron& neuron: m_vLayers.back().getNeurons())
		resultVals.push_back(neuron.getOutputVal());
}
