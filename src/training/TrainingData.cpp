//
// Created by zitri on 10.02.2023.
//

#include "TrainingData.h"
#include <sstream>
#include <cassert>

TrainingData::TrainingData(const std::string& filename)
{
	m_trainingDataFile.open(filename.c_str());
}

void TrainingData::getTopology(std::vector<int>& topology)
{
	std::string line;
	std::string label;

	std::getline(m_trainingDataFile, line);
	std::stringstream ss(line);
	ss >> label;
	if (this->isEof() || label.compare("topology:") != 0)
		assert(false);

	int n;
	while (!ss.eof())
	{
		ss >> n;
		topology.push_back(n);
	}
}

int TrainingData::getNextInputs(std::vector<float>& inputVals)
{
	inputVals.clear();

	std::string line;
	std::getline(m_trainingDataFile, line);
	std::stringstream ss(line);

	std::string label;
	ss >> label;
	if (label.compare("in:") == 0)
	{
		float oneValue;
		while (ss >> oneValue)
			inputVals.push_back(oneValue);
	}

	return inputVals.size();
}

int TrainingData::getTargetOutputs(std::vector<float>& targetOutputVals)
{
	targetOutputVals.clear();

	std::string line;
	std::getline(m_trainingDataFile, line);
	std::stringstream ss(line);

	std::string label;
	ss >> label;
	if (label.compare("out:") == 0)
	{
		float oneValue;
		while (ss >> oneValue)
			targetOutputVals.push_back(oneValue);
	}

	return targetOutputVals.size();
}
