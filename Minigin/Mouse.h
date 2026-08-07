#pragma once
#include "InputDevice.h"
#include <SDL3/SDL_Mouse.h>
#include <unordered_map>

namespace dae
{
	class Mouse final : public InputDevice
	{
	public:
		Mouse(const Mouse& other) = delete;
		Mouse(Mouse&& other) = delete;
		Mouse& operator=(const Mouse& other) = delete;
		Mouse& operator=(Mouse&& other) = delete;

		void Update() override;

		bool IsDownThisFrame(const Button& button) const override;
		bool IsUpThisFrame(const Button& button) const override;
		bool IsPressed(const Button& button) const override;
		glm::vec2 GetAxisValue(Axis axis) const override;

	private:
		friend class InputManager;
		Mouse();

		SDL_MouseButtonFlags m_PreviousState{};
		SDL_MouseButtonFlags m_CurrentState{};
		SDL_MouseButtonFlags m_ButtonsPressedThisFrame{};
		SDL_MouseButtonFlags m_ButtonsReleasedThisFrame{};
		glm::vec2 m_CurrentMouseDelta{};

		static const std::unordered_map<std::string_view, uint32_t> m_ButtonTable;
	};
}