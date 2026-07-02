#include <cstdint>
#include <SDL3/SDL_keyboard.h>
#include <SDL3/SDL_scancode.h>
#include <string_view>
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

		bool IsButtonCompatible(const Button& button) const;

		bool IsDownThisFrame(const Button& button) const override;
		bool IsUpThisFrame(const Button& button) const override;
		bool IsPressed(const Button& button) const override;

	private:
		uint8_t m_CurrentState[SDL_SCANCODE_COUNT]{};
		uint8_t m_PreviousState[SDL_SCANCODE_COUNT]{};

		static const std::unordered_map<std::string_view, uint32_t> m_ButtonTable;
	};
}