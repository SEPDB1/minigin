#pragma once
#include "Singleton.h"
#include <cstdint>

namespace dae
{
	class Timer final : public Singleton<Timer>
	{
	public:
		Timer();

		void Update();
		float GetElapsedTime() const;
		float GetFps() const;

	private:
		uint64_t m_CurrentTime{};
		uint64_t m_PreviousTime{};
		float m_SecondsPerCount{};
		float m_ElapsedTime{};
	};
}