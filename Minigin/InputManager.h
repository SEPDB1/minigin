#pragma once
#include <memory>
#include <vector>
#include <string>
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

		// Creates and stores an new instance of the requested input device which must derive from InputDevice
		template<typename InputDeviceT> requires std::derived_from<InputDeviceT, InputDevice>
		const InputDevice* CreateInputDevice()
		{
			m_pDevices.emplace_back (new InputDeviceT());
			return m_pDevices.crbegin()->get();
		}

		// Creates a new InputAction of the requested type by forwarding args to the InputAction's constructor 
		// and maps it to the name, the requested type has to derive from InputAction
		template <typename ActionT> requires std::derived_from<ActionT, InputAction>
		void AddInputAction(const std::string& name, std::unique_ptr<ActionT> pAction)
		{
			assert(pAction != nullptr && "InputAction should not be null");
			m_pInputActions.insert_or_assign(name, std::move(pAction));
		}

		const InputAction* GetActionByName(const std::string& actionName) const;
			
		bool IsButtonPressed(const Button& button, const InputDevice* pDevice) const;
		bool IsButtonDownThisFrame(const Button& button, const InputDevice* pDevice) const;
		bool IsButtonUpThisFrame(const Button& button, const InputDevice* pDevice) const;
		float GetButtonValue(const Button& button, const InputDevice* pDevice) const;
		bool IsButtonCompatible(const Button& button, const InputDevice* pDevice) const;

	private:
		std::vector<std::unique_ptr<InputDevice>> m_pDevices{};
		std::unordered_map<std::string, std::unique_ptr<InputAction>> m_pInputActions{};
	};
}
