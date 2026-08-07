#include "InputAction.h"
#include "InputManager.h"

dae::InputActionButton::InputActionButton(const Button& button)
	: m_Button{ button }
{
}

dae::InputContext dae::InputActionButton::GetActionContext(const InputDevice* pDevice) const
{
	const auto& inputManager{ InputManager::GetInstance() };

	return InputContext{
		inputManager.IsButtonPressed(m_Button, pDevice),
		inputManager.IsButtonDownThisFrame(m_Button, pDevice),
		inputManager.IsButtonUpThisFrame(m_Button, pDevice)
	};
}

dae::InputActionAxis2D::InputActionAxis2D(const Button& left, const Button& right, const Button& up, const Button& down)
	: m_LeftButton{ left }
	, m_RightButton{ right }
	, m_UpButton{ up }
	, m_DownButton{ down }
	, m_UsesButtons{ true }
{
}

dae::InputActionAxis2D::InputActionAxis2D(const Axis& axis)
	: m_Axis{ axis }
	, m_UsesButtons{ false }
{
}

dae::InputContext dae::InputActionAxis2D::GetActionContext(const InputDevice* pDevice) const
{
	const auto& inputManager{ InputManager::GetInstance() };
	InputContext ctx{};

	if (m_UsesButtons)
	{
		const float leftValue{ inputManager.GetButtonValue(m_LeftButton, pDevice) };
		const float rightValue{ inputManager.GetButtonValue(m_RightButton, pDevice) };
		const float upValue{ inputManager.GetButtonValue(m_UpButton, pDevice) };
		const float downValue{ inputManager.GetButtonValue(m_DownButton, pDevice) };

		ctx.value = glm::vec2{ -leftValue + rightValue, -upValue + downValue };
	}
	else
	{
		ctx.value = inputManager.GetAxisValue(m_Axis, pDevice);
	}

	return ctx;
}
