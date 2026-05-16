#include "Keyboard.h"
#include <cstring>

void dae::Keyboard::Update()
{
	std::memcpy(m_PreviousState, m_CurrentState, sizeof(m_CurrentState));
	std::memcpy(m_CurrentState, SDL_GetKeyboardState(nullptr), sizeof(m_CurrentState));
}

dae::InputContext dae::Keyboard::GetContext(UButton) const
{
	return InputContext(0.f);
}

bool dae::Keyboard::IsDownThisFrame(Button) const
{
	return false;
}

bool dae::Keyboard::IsUpThisFrame(Button) const
{
	return false;
}

bool dae::Keyboard::IsPressed(Button) const
{
	return false;
}
