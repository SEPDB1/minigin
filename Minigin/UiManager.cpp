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


struct GameObject3D
{
	Transform transform{};
	int ID{};

	/* it doesnt make sense to be able to multiply the ID
	   its just for changing something to the GameObject in CalculateResults*/
	GameObject3D& operator*=(int scalar) 
	{ 
		this->ID *= scalar;
		return *this;
	}
};

struct GameObject3DAlt
{
	Transform* pTransform{};
	int ID{};

	/* it doesnt make sense to be able to multiply the ID
	   its just for changing something to the GameObject in CalculateResults*/
	GameObject3DAlt& operator*=(int scalar)
	{
		this->ID *= scalar;
		return *this;
	}
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
	ImGui::InputInt("# samples", &m_Exercise1Data.numberOfSamples);
	bool isPressed = ImGui::Button("Trash the cache");

	if (isPressed)
	{
		CalculateResults<int>(m_Exercise1Data);
		m_Exercise1Data.isVisible = true;
	}

	if (m_Exercise1Data.isVisible)
	{
		ImGui::PlotConfig conf{};
		conf.values.xs = m_Exercise1Data.xs.data();
		conf.values.count = m_NumberOfSteps;
		conf.values.ys = m_Exercise1Data.ys.data();
		conf.values.color = ImColor(0, 255, 0);
		conf.frame_size = ImVec2(225, 150);
		conf.scale.min = 0;
		conf.scale.max = m_Exercise1Data.ys[0];
		conf.tooltip.show = true;
		conf.tooltip.format = "x=%.2f, y=%.2f";
		conf.grid_x.show = true;
		conf.grid_y.show = true;
		conf.line_thickness = 2.f;
		
		ImGui::Plot("plot", conf);
	}

	ImGui::End();
}

void dae::UiManager::RenderExercise2() const
{
	bool isOpen{};
	ImGui::Begin("Exercise 2", &isOpen);
	ImGui::InputInt("# samples", &m_Exercise2aData.numberOfSamples);

	if (ImGui::Button("Trash the cache with GameObject3D"))
	{
		CalculateResults<GameObject3D>(m_Exercise2aData);
		m_Exercise2aData.isVisible = true;
	}

	if (ImGui::Button("Trash the cache with GameObject3DAlt"))
	{
		CalculateResults<GameObject3DAlt>(m_Exercise2bData);
		m_Exercise2bData.isVisible = true;
	}

	if (m_Exercise2aData.isVisible || m_Exercise2bData.isVisible)
	{
		ImGui::PlotConfig conf{};
		conf.values.count = m_NumberOfSteps;
		conf.frame_size = ImVec2(225, 150);
		conf.scale.min = 0;
		conf.tooltip.show = true;
		conf.tooltip.format = "x=%.2f, y=%.2f";
		conf.grid_x.show = true;
		conf.grid_y.show = true;
		conf.line_thickness = 2.f;

		if (m_Exercise2aData.isVisible)
		{
			conf.scale.max = m_Exercise2aData.ys[0];
			conf.values.ys = m_Exercise2aData.ys.data();
			conf.values.color = ImColor(255, 255, 0);
			conf.values.xs = m_Exercise2aData.xs.data();
			ImGui::Plot("plot1", conf);
		}

		if (m_Exercise2bData.isVisible)
		{
			conf.scale.max = m_Exercise2bData.ys[0];
			conf.values.ys = m_Exercise2bData.ys.data();
			conf.values.color = ImColor(0, 255, 255);
			conf.values.xs = m_Exercise2bData.xs.data();
			ImGui::Plot("plot2", conf);
		}

		if (m_Exercise2aData.isVisible && m_Exercise2bData.isVisible)
		{
			const float* list[] = { m_Exercise2aData.ys.data(), m_Exercise2bData.ys.data() };
			ImU32 colors[3] = { ImColor(255, 255, 0), ImColor(0, 255, 255) };

			conf.values.ys = nullptr;
			conf.values.ys_list = list;
			conf.values.ys_count = 2;
			conf.scale.max = std::max(m_Exercise2aData.ys[0], m_Exercise2bData.ys[0]);
			conf.values.colors = colors;
			ImGui::Plot("combinedPlot", conf);
		}

	}

	ImGui::End();
}

template <typename T>
void dae::UiManager::CalculateResults(GraphData& data) const
{
	data.sumResults.resize(m_NumberOfSteps);
	data.xs.resize(m_NumberOfSteps);
	data.ys.resize(m_NumberOfSteps);

	// Make an array of the requested type
	constexpr int size{ 15'000'000 };
	T* pArray = new T[size]{};

	for (int count{ 0 }; count < data.numberOfSamples; ++count)
	{
		for (int step{ 0 }; step < m_NumberOfSteps; ++step)
		{
			const int stepsize = static_cast<int>(std::roundf(std::powf(2.f, static_cast<float>(step))));
			const auto start = std::chrono::high_resolution_clock::now();

			for (int i{ 0 }; i < size; i += stepsize)
				pArray[i] *= 2;

			const auto end = std::chrono::high_resolution_clock::now();
			data.sumResults[step] += std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
			data.xs[step] = static_cast<float>(stepsize);
		}
	}

	// Divide the total to retrieve the average
	for (int step{ 0 }; step < m_NumberOfSteps; ++step)
		data.ys[step] = static_cast<float>(data.sumResults[step] / data.numberOfSamples);

	delete[] pArray;
}
