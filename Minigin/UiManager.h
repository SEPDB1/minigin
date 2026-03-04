#pragma once
#include "Singleton.h"
#include <vector>

namespace dae
{
	struct GraphData
	{
		std::vector<long long> sumResults;
		std::vector<float> xs;
		std::vector<float> ys;
		int numberOfSamples;
		bool isVisible;
	};

	class UiManager final : public Singleton<UiManager>
	{
	public:
		void Render() const;

	private:
		void RenderExercise1() const;
		void RenderExercise2() const;

		template <typename T>
		void CalculateResults(GraphData& data) const;

		const int m_NumberOfSteps{ 11 };
		mutable GraphData m_Exercise1Data{ std::vector<long long>(), std::vector<float>(), std::vector<float>(), 20, false };
		mutable GraphData m_Exercise2aData{ std::vector<long long>(), std::vector<float>(), std::vector<float>(), 100, false };
		mutable GraphData m_Exercise2bData{ std::vector<long long>(), std::vector<float>(), std::vector<float>(), 100, false};
	};
}