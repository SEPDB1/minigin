#pragma once
#include "Singleton.h"
#include "InputDevice.h"
#include "InputAction.h"
#include <memory>
#include <vector>

namespace dae
{
	using Command = std::function<void(const InputContext&)>;

	class InputManager final : public Singleton<InputManager>
	{
	public:
		InputManager();
		~InputManager() = default;
		InputManager(const InputManager& other) = delete;
		InputManager(InputManager&& other) = delete;
		InputManager& operator=(const InputManager& other) = delete;
		InputManager& operator=(InputManager&& other) = delete;

		bool ProcessInput();

		InputDeviceID CreateNewDevice(std::unique_ptr<InputDevice> pInputDevice);
		InputActionID CreateNewAction(std::unique_ptr<InputActionBase> pAction);
		
		void EraseAction(InputActionID actionID);
		void EraseAction(std::string_view name);

		void BindCommand(InputActionID actionID, Command command);
		void BindCommand(std::string_view name, Command command);

		std::string_view GetActionNameByActionID(InputActionID actionId) const;
		InputActionID GetActionIDByActionName(std::string_view name) const;
		InputContext GetContextByButton(UButton button, InputDeviceID deviceID) const;

		const Command& GetCommand(InputActionID actionID) const;
		const Command& GetCommand(std::string_view name) const;

	private:
		InputActionBase* GetActionByActionID(InputActionID actionId) const;
		InputDevice* GetDeviceByDeviceID(InputDeviceID deviceID) const;

		std::vector<std::unique_ptr<InputDevice>> m_pDevices;
		std::vector<std::unique_ptr<InputActionBase>> m_pActions;
		std::unordered_map<InputActionID, Command> m_CommandBindings;
	};
}
