#include "Mouse.h"
#include <glm/glm.hpp>
#include <SDL3/SDL_Mouse.h>

#pragma region MouseImpl

class dae::Mouse::MouseImpl final
{
public:
	MouseImpl() = default;
	~MouseImpl() = default;
	MouseImpl(const MouseImpl& other) = delete;
	MouseImpl(MouseImpl&& other) = delete;
	MouseImpl& operator=(const MouseImpl& other) = delete;
	MouseImpl& operator=(MouseImpl&& other) = delete;

	void Update();

	bool IsDownThisFrame(const dae::Button& button) const;
	bool IsUpThisFrame(const dae::Button& button) const;
	bool IsPressed(const dae::Button& button) const;
	glm::vec2 GetAxisValue(dae::Axis axis) const;
	DeviceType GetType() const;

private:
	SDL_MouseButtonFlags m_PreviousState{};
	SDL_MouseButtonFlags m_CurrentState{};
	SDL_MouseButtonFlags m_ButtonsPressedThisFrame{};
	SDL_MouseButtonFlags m_ButtonsReleasedThisFrame{};
	glm::vec2 m_CurrentMouseDelta{};

	static const std::unordered_map<std::string_view, uint32_t> m_ButtonTable;
};

const std::unordered_map<std::string_view, uint32_t> dae::Mouse::MouseImpl::m_ButtonTable
{
	{ "LeftMouse",		0x0001 },
	{ "MiddleMouse",	0x0002 },
	{ "RightMouse",		0x0003 },
};


void dae::Mouse::MouseImpl::Update()
{
	m_PreviousState = m_CurrentState;
	m_CurrentState = SDL_GetMouseState(nullptr, nullptr);
	m_CurrentState = SDL_GetRelativeMouseState(std::addressof(m_CurrentMouseDelta.x), std::addressof(m_CurrentMouseDelta.y));

	auto buttonChanges = m_CurrentState ^ m_PreviousState;
	m_ButtonsPressedThisFrame = buttonChanges & m_CurrentState;
	m_ButtonsReleasedThisFrame = buttonChanges & (~m_CurrentState);
}

bool dae::Mouse::MouseImpl::IsDownThisFrame(const Button& button) const
{
	auto it = m_ButtonTable.find(button.name);
	
	if (it != m_ButtonTable.end())
		return m_ButtonsPressedThisFrame & it->second;
	
	return false;
}

bool dae::Mouse::MouseImpl::IsUpThisFrame(const Button& button) const
{
	auto it = m_ButtonTable.find(button.name);
	
	if (it != m_ButtonTable.end())
		return m_ButtonsReleasedThisFrame & it->second;
	
	return false;
}

bool dae::Mouse::MouseImpl::IsPressed(const Button& button) const
{
	auto it = m_ButtonTable.find(button.name);
	
	if (it != m_ButtonTable.end())
		return m_CurrentState & it->second;
	
	return false;
}

glm::vec2 dae::Mouse::MouseImpl::GetAxisValue(Axis axis) const
{
	if (axis == Axis::Mouse)
	{
		if (m_CurrentMouseDelta.x == 0.f && m_CurrentMouseDelta.y == 0.f)
			return glm::vec2();

		return glm::normalize(m_CurrentMouseDelta);
	}

	return glm::vec2();
}

dae::DeviceType dae::Mouse::MouseImpl::GetType() const
{
	return DeviceType::Mouse;
}

#pragma endregion MouseImpl

dae::Mouse::~Mouse() = default;


void dae::Mouse::Update()
{
	m_pImpl->Update();
}

bool dae::Mouse::IsDownThisFrame(const Button& button) const
{
	return m_pImpl->IsDownThisFrame(button);
}

bool dae::Mouse::IsUpThisFrame(const Button& button) const
{
	return m_pImpl->IsUpThisFrame(button);
}

bool dae::Mouse::IsPressed(const Button& button) const
{
	return m_pImpl->IsPressed(button);
}

glm::vec2 dae::Mouse::GetAxisValue(Axis axis) const
{
	return m_pImpl->GetAxisValue(axis);
}

dae::DeviceType dae::Mouse::GetType() const
{
	return m_pImpl->GetType();
}

dae::Mouse::Mouse()
	: m_pImpl{ std::make_unique<MouseImpl>() }
{

}
