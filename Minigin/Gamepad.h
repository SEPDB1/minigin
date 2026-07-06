#pragma once
#include <memory>
#include "InputDevice.h"

namespace dae
{
	class Gamepad final : public InputDevice
	{
	public:
		~Gamepad();
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
		friend class InputManager;
		Gamepad();

		class GamepadImpl;
		std::unique_ptr<GamepadImpl> m_pImpl{};
	};
}