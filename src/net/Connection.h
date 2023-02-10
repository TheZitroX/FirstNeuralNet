//
// Created by zitri on 08.02.2023.
//

#ifndef NEURALNET_CONNECTION_H
#define NEURALNET_CONNECTION_H


class Connection
{
	public:
		explicit Connection(float weight);
		~Connection() = default;

		[[nodiscard]] float getWeight() { return m_fWeight; }

		void setWeight(float weight) { m_fWeight = weight; }

		[[nodiscard]] float getDeltaWeight() { return m_fDeltaWeight; }

		void setDeltaWeight(float deltaWeight) { m_fDeltaWeight = deltaWeight; }

	private:
		float m_fWeight;
		float m_fDeltaWeight;
};


#endif //NEURALNET_CONNECTION_H
