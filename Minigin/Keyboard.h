#include <memory>
#include "InputDevice.h"
#include "InputUtility.h"

namespace dae
{
	class Keyboard final : public InputDevice
	{
	public:
		Keyboard();
		~Keyboard();
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
		class KeyboardImpl;
		std::unique_ptr<KeyboardImpl> m_pImpl{};
	};
}