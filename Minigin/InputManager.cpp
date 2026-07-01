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

const dae::InputAction* dae::InputManager::AddInputAction(const InputAction& action)
{
	m_InputActions.emplace_back(action);
	return std::addressof(*m_InputActions.crbegin());
}

bool dae::InputManager::IsButtonPressed(Button button, const InputDevice* pDevice) const
{
	try
	{
		return pDevice->IsPressed(button);
	}
	catch (const std::exception& e)
	{
		std::cout << e.what() << "\n";
		return false;
	}
}

bool dae::InputManager::IsButtonDownThisFrame(Button button, const InputDevice* pDevice) const
{
	try
	{
		return pDevice->IsDownThisFrame(button);
	}
	catch (const std::exception& e)
	{
		std::cout << e.what() << "\n";
		return false;
	}

}

bool dae::InputManager::IsButtonUpThisFrame(Button button, const InputDevice* pDevice) const
{
	try
	{
		return pDevice->IsUpThisFrame(button);
	}
	catch (const std::exception& e)
	{
		std::cout << e.what() << "\n";
		return false;
	}
}

float dae::InputManager::GetButtonValue(Button button, const InputDevice* pDevice) const
{
	return static_cast<float>(IsButtonPressed(button, pDevice));
}
