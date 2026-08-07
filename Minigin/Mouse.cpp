#include "Mouse.h"
#include <glm/glm.hpp>

const std::unordered_map<std::string_view, uint32_t> dae::Mouse::m_ButtonTable
{
	{ "LeftMouse",		0x0001 },
	{ "MiddleMouse",	0x0002 },
	{ "RightMouse",		0x0003 },
};


void dae::Mouse::Update()
{
	m_PreviousState = m_CurrentState;
	m_CurrentState = SDL_GetMouseState(nullptr, nullptr);
	m_CurrentState = SDL_GetRelativeMouseState(std::addressof(m_CurrentMouseDelta.x), std::addressof(m_CurrentMouseDelta.y));

	auto buttonChanges = m_CurrentState ^ m_PreviousState;
	m_ButtonsPressedThisFrame = buttonChanges & m_CurrentState;
	m_ButtonsReleasedThisFrame = buttonChanges & (~m_CurrentState);
}

bool dae::Mouse::IsDownThisFrame(const Button& button) const
{
	auto it = m_ButtonTable.find(button.name);
	
	if (it != m_ButtonTable.end())
		return m_ButtonsPressedThisFrame & it->second;
	
	return false;
}

bool dae::Mouse::IsUpThisFrame(const Button& button) const
{
	auto it = m_ButtonTable.find(button.name);
	
	if (it != m_ButtonTable.end())
		return m_ButtonsReleasedThisFrame & it->second;
	
	return false;
}

bool dae::Mouse::IsPressed(const Button& button) const
{
	auto it = m_ButtonTable.find(button.name);
	
	if (it != m_ButtonTable.end())
		return m_CurrentState & it->second;
	
	return false;
}

glm::vec2 dae::Mouse::GetAxisValue(Axis axis) const
{
	if (axis == Axis::Mouse)
	{
		if (m_CurrentMouseDelta.x == 0.f && m_CurrentMouseDelta.y == 0.f)
			return glm::vec2();

		return glm::normalize(m_CurrentMouseDelta);
	}

	return glm::vec2();
}

dae::Mouse::Mouse()
{
}
