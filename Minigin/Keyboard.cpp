#include "Keyboard.h"
#include <utility>

void dae::Keyboard::Update()
{
	std::memcpy(m_PreviousState, m_CurrentState, sizeof(m_CurrentState));
	std::memcpy(m_CurrentState, SDL_GetKeyboardState(nullptr), sizeof(m_CurrentState));
}

bool dae::Keyboard::IsButtonCompatible(Button button) const
{
	// TO DO: look into alternative ways, this is messy
	switch (button)
	{
	case dae::Button::keyboardA:
	case dae::Button::keyboardB:
	case dae::Button::keyboardC:
	case dae::Button::keyboardD:
	case dae::Button::keyboardE:
	case dae::Button::keyboardF:
	case dae::Button::keyboardG:
	case dae::Button::keyboardH:
	case dae::Button::keyboardI:
	case dae::Button::keyboardJ:
	case dae::Button::keyboardK:
	case dae::Button::keyboardL:
	case dae::Button::keyboardM:
	case dae::Button::keyboardN:
	case dae::Button::keyboardO:
	case dae::Button::keyboardP:
	case dae::Button::keyboardQ:
	case dae::Button::keyboardR:
	case dae::Button::keyboardS:
	case dae::Button::keyboardT:
	case dae::Button::keyboardU:
	case dae::Button::keyboardV:
	case dae::Button::keyboardW:
	case dae::Button::keyboardX:
	case dae::Button::keyboardY:
	case dae::Button::keyboardZ:
		return true;
		break;
	}
	return false;
}

bool dae::Keyboard::IsDownThisFrame(Button button) const
{
	auto idx{ std::to_underlying(button) };
	return !m_PreviousState[idx] && m_CurrentState[idx];
}

bool dae::Keyboard::IsUpThisFrame(Button button) const
{
	auto idx{ std::to_underlying(button) };
	return m_PreviousState[idx] && !m_CurrentState[idx];
}

bool dae::Keyboard::IsPressed(Button button) const
{
	return m_CurrentState[std::to_underlying(button)];
}
