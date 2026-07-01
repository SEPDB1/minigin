#include <cstdint>
#include <SDL3/SDL_keyboard.h>
#include <SDL3/SDL_scancode.h>
#include "InputDevice.h"
#include "InputUtility.h"

namespace dae
{
	class Keyboard final : public InputDevice
	{
	public:
		Keyboard() = default;
		~Keyboard() = default;
		Keyboard(const Keyboard& other) = delete;
		Keyboard(Keyboard&& other) = delete;
		Keyboard& operator=(const Keyboard& other) = delete;
		Keyboard& operator=(Keyboard&& other) = delete;

		void Update() override;

		bool IsButtonCompatible(Button button) const override;

		bool IsDownThisFrame(Button button) const override;
		bool IsUpThisFrame(Button button) const override;
		bool IsPressed(Button button) const override;

	private:
		uint8_t m_CurrentState[SDL_SCANCODE_COUNT]{};
		uint8_t m_PreviousState[SDL_SCANCODE_COUNT]{};
	};
}