//
// Created by zitri on 08.02.2023.
//

#include "Neuron.h"
#include <cmath>
#include "Layer.h"

float Neuron::s_fAlpha = 0.2f;
float Neuron::s_fEta   = 0.15f;

Neuron::Neuron(int numOutputs, int index)
	: m_iNumOutputs(numOutputs)
	, m_fOutputVal(0.0f)
	, m_iIndex(index)
	, m_fGradient(0.0f)
{
	for (int i = 0; i < numOutputs; i++)
		m_vOutputConnections.emplace_back(randomWeight());
}

void Neuron::feedForward(Layer& prevLayer)
{
	float sum = 0.0f;
	for (auto& neuron: prevLayer.getNeurons())
		sum += neuron.getOutputVal() *
		       neuron.m_vOutputConnections[m_iIndex].getWeight();

	m_fOutputVal = Neuron::transferFunction(sum);
}

float Neuron::transferFunction(float sum)
{
	 //tanh - output range [-1.0..1.0]
	return std::tanh(sum);

	// ReLU
	//return std::max(0.0f, sum);
}

float Neuron::transferFunctionDerivative(float sum)
{
	// tanh derivative
	return 1.0f - sum * sum;

	// ReLU derivative
	//return sum > 0.0f ? 1.0f : 0.0f;
}

void Neuron::calcOutputGradients(const float& targetVal)
{
	float delta = targetVal - m_fOutputVal;
	m_fGradient = delta * Neuron::transferFunctionDerivative(m_fOutputVal);
}

void Neuron::calcHiddenGradients(const Layer& layer)
{
	float dow = sumDOW(layer);
	m_fGradient = dow * Neuron::transferFunctionDerivative(m_fOutputVal);
}

float Neuron::sumDOW(Layer layer)
{
	float sum = 0.0f;

	// Sum our contributions of the errors at the nodes we feed.
	for (int i = 0; i < m_iNumOutputs; i++)
		sum += m_vOutputConnections[i].getWeight() * layer.getNeurons()[i].getGradient();

	return sum;
}

void Neuron::updateInputWeights(Layer& prevLayer) const
{
	// The weights to be updated are in the Connection container
	// in the neurons in the preceding layer

	for (auto& neuron: prevLayer.getNeurons())
	{
		const float oldDeltaWeight = neuron.m_vOutputConnections[m_iIndex].getDeltaWeight();
		const float newDeltaWeight =
			            // Individual input, magnified by the gradient and train rate:
			            s_fEta * neuron.getOutputVal() * m_fGradient +
			            // Also add momentum = a fraction of the previous delta weight
			            s_fAlpha * oldDeltaWeight;

		neuron.m_vOutputConnections[m_iIndex].setDeltaWeight(newDeltaWeight);
		neuron.m_vOutputConnections[m_iIndex].setWeight(
			neuron.m_vOutputConnections[m_iIndex].getWeight() + newDeltaWeight
		);
	}
}
