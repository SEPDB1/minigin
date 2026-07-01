#include "Gamepad.h"
#include <utility>

dae::Gamepad::Gamepad()
	: m_DeviceIdx{ 0 }
{
}

void dae::Gamepad::Update()
{
	m_PreviousState = m_CurrentState;
	m_CurrentState = {};
	XInputGetState(m_DeviceIdx, &m_CurrentState);

	if (m_CurrentState.dwPacketNumber != m_PreviousState.dwPacketNumber)
	{
		WORD buttonChanges = m_CurrentState.Gamepad.wButtons ^ m_PreviousState.Gamepad.wButtons;
		m_ButtonsPressedThisFrame = buttonChanges & m_CurrentState.Gamepad.wButtons;
		m_ButtonsReleasedThisFrame = buttonChanges & (~m_CurrentState.Gamepad.wButtons);
	}
}

bool dae::Gamepad::IsButtonCompatible(Button button) const
{
	// TO DO: look into alternative ways, this is messy
	switch (button)
	{
	case dae::Button::gamepadA:
	case dae::Button::gamepadB:
	case dae::Button::gamepadX:
	case dae::Button::gamepadY:
		return true;
		break;
	}

	return false;
}

bool dae::Gamepad::IsDownThisFrame(dae::Button button) const
{
	return m_ButtonsPressedThisFrame & std::to_underlying(button);
}

bool dae::Gamepad::IsUpThisFrame(dae::Button button) const
{
	return m_ButtonsReleasedThisFrame & std::to_underlying(button);
}

bool dae::Gamepad::IsPressed(Button button) const
{
	return m_CurrentState.Gamepad.wButtons & std::to_underlying(button);
}
