#pragma once
#include <string_view>
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

		bool IsButtonCompatible(const Button& button) const;

		bool IsDownThisFrame(const Button& button) const override;
		bool IsUpThisFrame(const Button& button) const override;
		bool IsPressed(const Button& button) const override;

	private:
		WORD m_ButtonsPressedThisFrame{ 0 };
		WORD m_ButtonsReleasedThisFrame{ 0 };
		DWORD m_DeviceIdx{};
		_XINPUT_STATE m_CurrentState{};
		_XINPUT_STATE m_PreviousState{};

		static const std::unordered_map<std::string_view, uint32_t> m_ButtonTable;
	};
}