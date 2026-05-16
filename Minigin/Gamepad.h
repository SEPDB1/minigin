#pragma once
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <Xinput.h>
#include "InputDevice.h"

namespace dae
{
	class Gamepad final : public InputDevice
	{
	public:
		enum class Button : uint32_t
		{
			dpadUp			= 0x0000'0001,
			dpadDown		= 0x0000'0002,
			dpadLeft		= 0x0000'0004,
			dpadRight		= 0x0000'0008,
			start			= 0x0000'0010,
			back			= 0x0000'0020,
			leftThumb		= 0x0000'0040,
			rightThumb		= 0x0000'0080,
			leftShoulder	= 0x0000'0100,
			rightShoulder	= 0x0000'0200,
			a				= 0x0000'1000,
			b				= 0x0000'2000,
			x				= 0x0000'4000,
			y				= 0x0000'8000,
			thumbLeftx		= 0x0001'0000,
			thumbLefty		= 0x0002'0000,
			thumbRightx		= 0x0004'0000,
			thumbRighty		= 0x0008'0000,
		};

		Gamepad(DWORD deviceIdx);
		~Gamepad() = default;
		Gamepad(const Gamepad& other) = delete;
		Gamepad(Gamepad&& other) = delete;
		Gamepad& operator=(const Gamepad& other) = delete;
		Gamepad& operator=(Gamepad&& other) = delete;

		void Update() override;

		InputContext GetContext(UButton button) const override;
	private:
		bool IsDownThisFrame(Button button) const;
		bool IsUpThisFrame(Button button) const;
		bool IsPressed(Button button) const;
		InputContext CreateContextJoystick(SHORT previousValue, SHORT currentValue, SHORT deadzone) const;

		WORD m_ButtonsPressedThisFrame{ 0 };
		WORD m_ButtonsReleasedThisFrame{ 0 };
		DWORD m_DeviceIdx{};
		_XINPUT_STATE m_CurrentState{};
		_XINPUT_STATE m_PreviousState{};
	};
}