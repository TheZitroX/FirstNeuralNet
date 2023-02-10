//
// Created by zitri on 08.02.2023.
//

#ifndef NEURALNET_NEURON_H
#define NEURALNET_NEURON_H

#include <vector>
#include <cstdlib>
#include "Connection.h"

class Layer;

class Neuron
{
	public:
		static float s_fEta;
		static float s_fAlpha;

		Neuron(int numOutputs, int index);
		~Neuron() = default;

		void setOutputVal(const float& val) { m_fOutputVal = val; }

		void feedForward(Layer& layer);

		[[nodiscard]] float getOutputVal() const { return m_fOutputVal; }

		void calcOutputGradients(const float& targetVal);
		void calcHiddenGradients(const Layer& layer);

		[[nodiscard]] float getGradient() const { return m_fGradient; }

		void updateInputWeights(Layer& prevLayer) const;
	private:

		int                     m_iIndex;
		float                   m_fOutputVal;
		int                     m_iNumOutputs;
		float                   m_fGradient;
		std::vector<Connection> m_vOutputConnections;

		static float randomWeight() { return static_cast<float>(rand()) / float(RAND_MAX); }

		static float transferFunction(float sum);

		static float transferFunctionDerivative(float sum);
		float sumDOW(Layer layer);
};

#endif //NEURALNET_NEURON_H
