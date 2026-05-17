#include "InputManager.h"
#include "Gamepad.h"
#include "Keyboard.h"
#include "InputAction.h"
#include <backends/imgui_impl_sdl3.h>
#include <SDL3/SDL.h>
#include <algorithm>
#include <stdexcept>

dae::InputManager::InputManager() = default;

bool dae::InputManager::ProcessInput()
{
	SDL_Event e;
	while (SDL_PollEvent(&e))
	{
		if (e.type == SDL_EVENT_QUIT)
			return false;

		//process event for IMGUI
		ImGui_ImplSDL3_ProcessEvent(&e);
	}

	for (auto& pDevice : m_pDevices)
	{
		pDevice->Update();
	}

	return true;
}

dae::InputDeviceID dae::InputManager::CreateNewDevice(std::unique_ptr<InputDevice> pInputDevice)
{
	m_pDevices.push_back(std::move(pInputDevice));
	return m_pDevices.back().get()->GetID();
}

dae::InputActionID dae::InputManager::CreateNewAction(std::unique_ptr<InputActionBase> pAction)
{
	m_pActions.push_back(std::move(pAction));

	return m_pActions.back().get()->GetID();
}

void dae::InputManager::EraseAction(InputActionID actionId)
{
	std::erase_if(m_pActions,
		[actionId](const auto& action) {
			return action.get()->GetID() == actionId;
		}
	);

	m_CommandBindings.erase(actionId);
}

void dae::InputManager::EraseAction(std::string_view name)
{
	EraseAction(GetActionIDByActionName(name));
}

void dae::InputManager::BindCommand(InputActionID ID, std::unique_ptr<Command> pCommand)
{
	m_CommandBindings[ID] = std::move(pCommand);
}

void dae::InputManager::BindCommand(std::string_view name, std::unique_ptr<Command> pCommand)
{
	BindCommand(GetActionIDByActionName(name), std::move(pCommand));
}

std::string_view dae::InputManager::GetActionNameByActionID(dae::InputActionID ID) const
{
	auto it = std::ranges::find_if
	(m_pActions,
		[ID](const auto& pAction) { 
			return pAction.get()->GetID() == ID;
		}
	);

	if (it == m_pActions.end())
		throw std::runtime_error("Invalid InputAction ID");

	return it->get()->GetName();
}

dae::InputActionID dae::InputManager::GetActionIDByActionName(std::string_view name) const
{
	auto it = std::ranges::find_if
	(m_pActions, 
		[name](const auto& pAction) { 
			return pAction.get()->GetName() == name; 
		}
	);

	if (it == m_pActions.end())
		throw std::runtime_error("Invalid InputAction name");

	return it->get()->GetID();
}

dae::InputContext dae::InputManager::GetContextByButton(UButton button, InputDeviceID deviceID) const
{
	auto pDevice{ GetDeviceByDeviceID(deviceID) };

	return pDevice->GetContext(button);
}

dae::Command* dae::InputManager::GetCommand(InputActionID actionId) const
{
	return m_CommandBindings.at(actionId).get();
}

dae::Command* dae::InputManager::GetCommand(std::string_view name) const
{
	return GetCommand(GetActionIDByActionName(name));
}

dae::InputActionBase* dae::InputManager::GetActionByActionID(InputActionID actionId) const
{
	auto it = std::ranges::find_if(m_pActions, 
		[actionId](const auto& pAction) { 
			return pAction.get()->GetID() == actionId; 
		}
	);

	if (it == m_pActions.end())
		throw std::runtime_error("Invalid InputAction ID");

	return it->get();
}

dae::InputDevice* dae::InputManager::GetDeviceByDeviceID(InputDeviceID deviceID) const
{
	auto it = std::ranges::find_if(m_pDevices,
		[deviceID](const auto& pDEvice) {
			return pDEvice.get()->GetID() == deviceID;
		}
	);

	if (it == m_pDevices.end())
		throw std::runtime_error("Invalid Device ID");

	return (*it).get();
}
