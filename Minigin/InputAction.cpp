#include "InputAction.h"
#include "InputManager.h"

// 'macro's' for clarity sake
inline constexpr uint32_t IDX_LEFT{ 0 };
inline constexpr uint32_t IDX_RIGHT{ 1 };
inline constexpr uint32_t IDX_UP{ 2 };
inline constexpr uint32_t IDX_DOWN{ 3 };


dae::InputAction::InputAction(Button button)
	: m_Buttons{ button, Button::invalid, Button::invalid, Button::invalid }
	, m_Type{ ActionType::button }
{
}

dae::InputAction::InputAction(Button left, Button right)
	: m_Buttons{ left, right, Button::invalid, Button::invalid }
	, m_Type{ ActionType::axis1D }
{
}

dae::InputAction::InputAction(Button left, Button right, Button up, Button down)
	: m_Buttons{ left, right, up, down }
	, m_Type{ ActionType::axis2D }
{
}

dae::InputContext dae::InputAction::GetActionContext(const InputDevice* pDevice) const
{
	auto& inputManager{ InputManager::GetInstance() };

	InputContext cxt{};
	switch (m_Type)
	{
	case dae::InputAction::ActionType::button:

		cxt.value = inputManager.IsButtonPressed(m_Buttons[IDX_LEFT], pDevice);
		cxt.isDownThisFrame = inputManager.IsButtonDownThisFrame(m_Buttons[IDX_LEFT], pDevice);
		cxt.isUpThisFrame = inputManager.IsButtonUpThisFrame(m_Buttons[IDX_LEFT], pDevice);
		break;
	case dae::InputAction::ActionType::axis1D:

		// Only the value field matters
		cxt.value = - inputManager.GetButtonValue(m_Buttons[IDX_LEFT], pDevice) + inputManager.GetButtonValue(m_Buttons[IDX_RIGHT], pDevice);
		break;
	case dae::InputAction::ActionType::axis2D:

		// Only the value field matters
		cxt.value = glm::vec2{ 
			-inputManager.GetButtonValue(m_Buttons[IDX_LEFT], pDevice) + inputManager.GetButtonValue(m_Buttons[IDX_RIGHT], pDevice),
			-inputManager.GetButtonValue(m_Buttons[IDX_UP], pDevice) + inputManager.GetButtonValue(m_Buttons[IDX_DOWN], pDevice),
		};
		break;
	}

	return cxt;
}
