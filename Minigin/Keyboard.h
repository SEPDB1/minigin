#include <cstdint>
#include <SDL3/SDL_keyboard.h>
#include <SDL3/SDL_scancode.h>
#include "InputDevice.h"

namespace dae
{
	class Keyboard final : public InputDevice
	{
	public:
		enum class Button
		{

		};

		Keyboard() = default;
		~Keyboard() = default;
		Keyboard(const Keyboard& other) = delete;
		Keyboard(Keyboard&& other) = delete;
		Keyboard& operator=(const Keyboard& other) = delete;
		Keyboard& operator=(Keyboard&& other) = delete;

		void Update() override;

		InputContext GetContext(UButton button) const override;
	private:
		bool IsDownThisFrame(Button button) const;
		bool IsUpThisFrame(Button button) const;
		bool IsPressed(Button button) const;

		uint8_t m_CurrentState[SDL_SCANCODE_COUNT]{};
		uint8_t m_PreviousState[SDL_SCANCODE_COUNT]{};
		uint8_t m_ButtonsPressedThisFrame{};
		uint8_t m_ButtonsReleasedThisFrame{};
	};
}