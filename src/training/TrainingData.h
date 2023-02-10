//
// Created by zitri on 10.02.2023.
//

#ifndef NEURALNET_TRAININGDATA_H
#define NEURALNET_TRAININGDATA_H

#include <string>
#include <vector>
#include <fstream>

class TrainingData
{
	public:
		explicit TrainingData(const std::string& filename);
		~TrainingData() = default;

		bool isEof() { return m_trainingDataFile.eof(); }

		void getTopology(std::vector<int>& topology);

		// Returns the number of input values read from the file:
		int getNextInputs(std::vector<float>& inputVals);
		int getTargetOutputs(std::vector<float>& targetOutputVals);
	private:
		std::ifstream m_trainingDataFile;
};


#endif //NEURALNET_TRAININGDATA_H
