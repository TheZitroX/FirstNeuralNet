//
// Created by zitri on 08.02.2023.
//

#ifndef NEURALNET_NET_H
#define NEURALNET_NET_H

#include <vector>
#include "Layer.h"

class Net
{
	public:
		[[maybe_unused]] explicit Net(const std::vector<int>& topology);
		~Net() = default;

		void feedForward(const std::vector<float>& inputVals);
		void backProp(const std::vector<float>& targetVals);
		void getResults(std::vector<float>& resultVals);

		[[nodiscard]] double getRecentAverageError() const { return m_dRecentAverageError; };
	private:
		double             m_dRecentAverageSmoothingFactor;
		double             m_dRecentAverageError;
		double             m_dError;
		std::vector<Layer> m_vLayers;
};


#endif //NEURALNET_NET_H
