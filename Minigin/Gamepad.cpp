#include "Gamepad.h"

const std::unordered_map<std::string_view, uint32_t> dae::Gamepad::m_ButtonTable
{ 
	{ "DpadUp",			0x0001 },
	{ "DpadDown",		0x0002 },
	{ "DpadLeft",		0x0004 },
	{ "DpadRight",		0x0008 },
	{ "Start",			0x0010 },
	{ "Back",			0x0020 },
	{ "LeftThumb",		0x0040 },
	{ "RightThumb",		0x0080 },
	{ "LeftShoulder",	0x0100 },
	{ "RightShoulder",	0x0200 },
	{ "A",				0x1000 },
	{ "B",				0x2000 },
	{ "X",				0x4000 },
	{ "Y",				0x8000 },
};

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

bool dae::Gamepad::IsButtonCompatible(const Button& button) const
{
	return button.deviceType == DeviceType::gamepad;
}

bool dae::Gamepad::IsDownThisFrame(const Button& button) const
{
	return m_ButtonsPressedThisFrame & m_ButtonTable.at(button.name);
}

bool dae::Gamepad::IsUpThisFrame(const Button& button) const
{
	return m_ButtonsReleasedThisFrame & m_ButtonTable.at(button.name);
}

bool dae::Gamepad::IsPressed(const Button& button) const
{
	return m_CurrentState.Gamepad.wButtons & m_ButtonTable.at(button.name);
}
