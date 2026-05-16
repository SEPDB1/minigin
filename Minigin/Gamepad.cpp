#include "Gamepad.h"
#include <utility>
#include "MathHelpers.h"

dae::Gamepad::Gamepad(DWORD deviceIdx)
	: m_DeviceIdx{ deviceIdx }
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

dae::InputContext dae::Gamepad::GetContext(UButton uButton) const
{
	Button button{ static_cast<Button>(uButton) };

	switch (button)
	{
	case dae::Gamepad::Button::thumbLeftx:
		return CreateContextJoystick(m_PreviousState.Gamepad.sThumbLX, m_CurrentState.Gamepad.sThumbLX, 
			static_cast<SHORT>(XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE)
		);
		break;
	case dae::Gamepad::Button::thumbLefty:
		return CreateContextJoystick(m_PreviousState.Gamepad.sThumbLY, m_CurrentState.Gamepad.sThumbLY,
			static_cast<SHORT>(XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE)
		);
		break;
	case dae::Gamepad::Button::thumbRightx:
		return CreateContextJoystick(m_PreviousState.Gamepad.sThumbRX, m_CurrentState.Gamepad.sThumbRX,
			static_cast<SHORT>(XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE)
		);
		break;
	case dae::Gamepad::Button::thumbRighty:
		return CreateContextJoystick(m_PreviousState.Gamepad.sThumbRY,m_CurrentState.Gamepad.sThumbRY,
			static_cast<SHORT>(XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE)
		);
		break;
	default:

		InputContext context{ 0.f };
		context.started = IsDownThisFrame(button);
		context.isPressed = IsPressed(button);
		context.canceled = IsUpThisFrame(button);
		context.value = static_cast<float>(context.isPressed);

		return context;
		break;
	}
}

bool dae::Gamepad::IsDownThisFrame(Button button) const
{
	return m_ButtonsPressedThisFrame & std::to_underlying(button);
}

bool dae::Gamepad::IsUpThisFrame(Button button) const
{
	return m_ButtonsReleasedThisFrame & std::to_underlying(button);
}

bool dae::Gamepad::IsPressed(Button button) const
{
	return m_CurrentState.Gamepad.wButtons & std::to_underlying(button);
}

dae::InputContext dae::Gamepad::CreateContextJoystick(SHORT previousValue, SHORT currentValue, SHORT deadzone) const
{
	// Convert value from [MINSHORT, MAXSHORT] to [0.f, 1.f]
	InputContext context{ 
		dae::math::InverseLerp(
			static_cast<float>(MINSHORT), 
			static_cast<float>(MAXSHORT), 
			static_cast<float>(currentValue)) 
	};

	bool wasPressed{ static_cast<SHORT>(std::abs(previousValue)) > deadzone };

	context.isPressed = static_cast<SHORT>(std::abs(currentValue)) > deadzone;
	context.started = !wasPressed && context.isPressed;
	context.canceled = wasPressed && !context.isPressed;;

	return context;
}