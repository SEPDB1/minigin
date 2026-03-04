#pragma once
#include "Singleton.h"
#include <vector>

namespace dae
{
	struct GraphData
	{
		std::vector<long long> results;
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
		void CalculateResults() const;

		const int m_NumberOfSteps{ 11 };
		mutable GraphData m_Exercise1{ std::vector<long long>(), 20, false };
		mutable GraphData m_Exercise2a{ std::vector<long long>(), 100, false };
		mutable GraphData m_Exercise2b{ std::vector<long long>(), 100, false};
	};
}