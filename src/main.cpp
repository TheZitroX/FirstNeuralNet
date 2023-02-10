#include "net/Net.h"
#include "training/TrainingData.h"
#include <iostream>
#include <cassert>

void showVectorVals(const std::string& label, std::vector<float>& vector)
{
	std::cout << label << " ";
	for (float value: vector)
		std::cout << value << " ";

	std::cout << std::endl;
}

int main()
{
	Neuron::s_fEta   = 0.05f; // overall net learning rate [0.0..1.0]
	Neuron::s_fAlpha = 0.15f; // momentum, multiplier of last deltaWeight [0.0..n]

	TrainingData trainingData("../trainingData.txt");

	std::vector<int> topology;
	trainingData.getTopology(topology);
	Net net(topology);

	std::vector<float> inputVals, targetVals, resultVals;
	int                trainingPass = 0;

	while (!trainingData.isEof())
	{
		++trainingPass;
		std::cout << std::endl << "Pass " << trainingPass;

		// Get new input data and feed it forward:
		if (trainingData.getNextInputs(inputVals) != topology[0])
			break;

		showVectorVals(": Inputs:", inputVals);
		net.feedForward(inputVals);

		// Collect the net's actual output results:
		net.getResults(resultVals);
		showVectorVals("Outputs:", resultVals);

		// Train the net what the outputs should have been:
		trainingData.getTargetOutputs(targetVals);
		showVectorVals("Targets:", targetVals);
		assert(targetVals.size() == topology.back());
		net.backProp(targetVals);

		// Report how well the training is working, average over recent samples:
		std::cout << "Net recent average error: " << net.getRecentAverageError() << std::endl;
	}

	return 0;
}
