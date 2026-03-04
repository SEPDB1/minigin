// standard includes
#include <chrono>
#include <vector>

// library includes
#include <imgui.h>
#include <imgui_plot.h>
#include <backends/imgui_impl_sdl3.h>
#include <backends/imgui_impl_sdlrenderer3.h>

// project includes
#include "UiManager.h"

struct Transform
{
	float matrix[16] = {
		1,0,0,0,
		0,1,0,0,
		0,0,1,0,
		0,0,0,1 };
};

class GameObject3D
{
public:
	Transform transform{};
	int ID;
};

class GameObject3DAlt
{
public:
	Transform* pTransform{};
	int ID;
};

void dae::UiManager::Render() const
{
	RenderExercise1();
	RenderExercise2();
}

void dae::UiManager::RenderExercise1() const
{
	bool isOpen{};
	ImGui::Begin("Exercise 1", &isOpen);
	ImGui::InputInt("# samples", &m_Exercise1.numberOfSamples);
	bool isPressed = ImGui::Button("Trash the cache");

	if (isPressed)
	{
		CalculateResults();
		m_Exercise1.isVisible = true;
	}

	if (m_Exercise1.isVisible)
	{
		ImGui::PlotConfig conf{};
		//conf.frame_size = ImVec2(50.f, 50.f);
		//conf.values.ys = static_cast<>(m_Exercise1.results.data());
		ImGui::Plot("plot", conf);
	}

	ImGui::End();
}

void dae::UiManager::RenderExercise2() const
{
	bool isOpen{};
	ImGui::Begin("Exercise 2", &isOpen);
	ImGui::InputInt("# samples", &m_Exercise2a.numberOfSamples);
	ImGui::Button("Trash the cache with GameObject3D");
	ImGui::Button("Trash the cache with GameObject3DAlt");
	ImGui::End();
}

void dae::UiManager::CalculateResults() const
{
	m_Exercise1.results.resize(m_Exercise1.numberOfSamples);

	//constexpr int size{ 64'000'000 };
	//int* pArray = new int[size]{ 5 };
	//long long* totalsArr = new long long[m_NumberOfSteps] {};

	//// Fill array with total results
	//for (int count{ 0 }; count < m_NumberSamplesExercise1; ++count)
	//{
	//	for (int step{ 0 }; step < m_NumberOfSteps; ++step)
	//	{
	//		const int stepsize = static_cast<int>(std::roundf(std::powf(2.f, static_cast<float>(step))));
	//		const auto start = std::chrono::high_resolution_clock::now();

	//		for (int i{ 0 }; i < size; i += stepsize)
	//			pArray[i] *= 2;

	//		const auto end = std::chrono::high_resolution_clock::now();
	//		totalsArr[step] += std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
	//	}
	//}

	//// Divide the total to retrieve the average
	//for (int step{ 0 }; step < m_NumberOfSteps; ++step)
	//	totalsArr[step] /= m_NumberSamplesExercise1;
}
