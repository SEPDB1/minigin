#include "InputAction.h"
#include "InputManager.h"

dae::InputActionButton::InputActionButton(const Button& button)
	: m_Button{ button }
{
}

float dae::InputAction::GetButtonValue(const Button& button, const InputDevice* pDevice) const
{
	const auto& inputManager{ InputManager::GetInstance() };

	if (inputManager.IsButtonCompatible(button, pDevice))
		return inputManager.GetButtonValue(button, pDevice);

	return 0.f;
}

dae::InputContext dae::InputActionButton::GetActionContext(const InputDevice* pDevice) const
{
	const auto& inputManager{ InputManager::GetInstance() };

	return InputContext
	{
		inputManager.IsButtonPressed(m_Button, pDevice),
		inputManager.IsButtonDownThisFrame(m_Button, pDevice),
		inputManager.IsButtonUpThisFrame(m_Button, pDevice)
	};
}

dae::InputActionAxis1D::InputActionAxis1D(const Button& left, const Button& right)
	: m_ButtonLeft{ left }
	, m_ButtonRight{ right }
{
}

dae::InputContext dae::InputActionAxis1D::GetActionContext(const InputDevice* pDevice) const
{
	const float leftValue{ InputAction::GetButtonValue(m_ButtonLeft, pDevice) };
	const float rightValue{ InputAction::GetButtonValue(m_ButtonRight, pDevice) };

	// Only the value field matters
	return InputContext{ -leftValue + rightValue };
}

dae::InputActionAxis2D::InputActionAxis2D(const Button& left, const Button& right, const Button& up, const Button& down)
	: m_ButtonLeft{ left }
	, m_ButtonRight{ right }
	, m_ButtonUp{ up }
	, m_ButtonDown{ down }
{
}

dae::InputContext dae::InputActionAxis2D::GetActionContext(const InputDevice* pDevice) const
{
	const float leftValue{ InputAction::GetButtonValue(m_ButtonLeft, pDevice) };
	const float rightValue{ InputAction::GetButtonValue(m_ButtonRight, pDevice) };
	const float upValue{ InputAction::GetButtonValue(m_ButtonUp, pDevice) };
	const float downValue{ InputAction::GetButtonValue(m_ButtonDown, pDevice) };

	// Only the value field matters
	return InputContext{ glm::vec2{ -leftValue + rightValue, -upValue + downValue } };
}

