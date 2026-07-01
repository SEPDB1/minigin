#pragma once
#include "InputUtility.h"
#include <array>

namespace dae
{
	class InputDevice;
	class InputAction final
	{
	public:
		using ButtonArray = std::array<Button, 4>;

		enum class ActionType : uint8_t
		{
			button,
			axis1D,
			axis2D
		};

		InputAction(Button button);
		InputAction(Button left, Button right);
		InputAction(Button left, Button right, Button up, Button down);

		InputContext GetActionContext(const InputDevice* pDeivce) const;

	private:
		ButtonArray m_Buttons{ Button::invalid, Button::invalid, Button::invalid, Button::invalid };
		ActionType m_Type{};
	};
}