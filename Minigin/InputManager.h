#pragma once
#include <memory>
#include <vector>
#include "Singleton.h"
#include "InputAction.h"
#include "InputUtility.h"
#include "Gamepad.h"

namespace dae
{
	class InputManager final : public Singleton<InputManager>
	{
	public:
		InputManager() = default;
		~InputManager() = default;
		InputManager(const InputManager& other) = delete;
		InputManager(InputManager&& other) = delete;
		InputManager& operator=(const InputManager& other) = delete;
		InputManager& operator=(InputManager&& other) = delete;

		bool ProcessInput();

		// Creates and stores an new instance of a input device T which must derive from InputDevice
		template<typename T> requires std::derived_from<T, InputDevice>
		const InputDevice* CreateInputDevice()
		{
			m_pDevices.push_back(std::move(std::make_unique<T>()));
			return m_pDevices.crbegin()->get();
		}

		const InputAction* AddInputAction(const InputAction& action);

		bool IsButtonPressed(Button button, const InputDevice* pDevice) const;
		bool IsButtonDownThisFrame(Button button, const InputDevice* pDevice) const;
		bool IsButtonUpThisFrame(Button button, const InputDevice* pDevice) const;
		float GetButtonValue(Button button, const InputDevice* pDevice) const;

	private:
		std::vector<std::unique_ptr<InputDevice>> m_pDevices{};
		std::vector<InputAction> m_InputActions{};
	};
}
