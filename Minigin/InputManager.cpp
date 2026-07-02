#include "InputManager.h"
#include "Gamepad.h"
#include "Keyboard.h"
#include <backends/imgui_impl_sdl3.h>
#include <SDL3/SDL.h>
#include <iostream>

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

	for (auto& m_pDevice : m_pDevices)
	{
		m_pDevice->Update();
	}

	return true;
}

const dae::InputAction* dae::InputManager::GetActionByName(const std::string& actionName) const
{
	auto it{ m_pInputActions.find(actionName) };

	if (it != m_pInputActions.end())
		return it->second.get();

	return nullptr;
}

bool dae::InputManager::IsButtonPressed(const Button& button, const InputDevice* pDevice) const
{
	return pDevice->IsPressed(button);
}

bool dae::InputManager::IsButtonDownThisFrame(const Button& button, const InputDevice* pDevice) const
{
	return pDevice->IsDownThisFrame(button);
}

bool dae::InputManager::IsButtonUpThisFrame(const Button& button, const InputDevice* pDevice) const
{
	return pDevice->IsUpThisFrame(button);
}

float dae::InputManager::GetButtonValue(const Button& button, const InputDevice* pDevice) const
{
	return static_cast<float>(IsButtonPressed(button, pDevice));
}

bool dae::InputManager::IsButtonCompatible(const Button& button, const InputDevice* pDevice) const
{
	return pDevice->IsButtonCompatible(button);
}
