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
		Gamepad();
		~Gamepad() = default;
		Gamepad(const Gamepad& other) = delete;
		Gamepad(Gamepad&& other) = delete;
		Gamepad& operator=(const Gamepad& other) = delete;
		Gamepad& operator=(Gamepad&& other) = delete;

		void Update() override;

		bool IsButtonCompatible(Button button) const override;

		bool IsDownThisFrame(Button button) const override;
		bool IsUpThisFrame(Button button) const override;
		bool IsPressed(Button button) const override;

	private:
		WORD m_ButtonsPressedThisFrame{ 0 };
		WORD m_ButtonsReleasedThisFrame{ 0 };
		DWORD m_DeviceIdx{};
		_XINPUT_STATE m_CurrentState{};
		_XINPUT_STATE m_PreviousState{};
	};
}