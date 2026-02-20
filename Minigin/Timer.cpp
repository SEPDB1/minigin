#include "Timer.h"
#include <SDL3/SDL_timer.h>

dae::Timer::Timer()
{
	const uint64_t countPerSeconds = SDL_GetPerformanceFrequency();
	m_SecondsPerCount = 1.0f / static_cast<float>(countPerSeconds);

	m_CurrentTime = SDL_GetPerformanceCounter();
	m_PreviousTime = m_CurrentTime;
}


void dae::Timer::Update()
{
	m_CurrentTime = SDL_GetPerformanceCounter();

	m_ElapsedTime = static_cast<float>((m_CurrentTime - m_PreviousTime) * m_SecondsPerCount);
 	m_PreviousTime = m_CurrentTime;

	if (m_ElapsedTime < 0.0f)
		m_ElapsedTime = 0.0f;
}

float dae::Timer::GetElapsedTime() const
{
	return m_ElapsedTime;
}

float dae::Timer::GetFps() const
{
	return 1.f / m_ElapsedTime;
}
