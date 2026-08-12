#include "InputUtility.h"
#include "InputManager.h"

dae::InputContext::InputContext(ActionValue value, const InputDevice* pDevice, bool isDownThisFrame, bool isUpThisFrame)
	: value{ value }
	, pDevice{ pDevice }
	, isDownThisFrame{ isDownThisFrame }
	, isUpThisFrame{ isUpThisFrame }
{
}

dae::Button::Button(std::string_view name)
	: name{ name }
{
}

dae::CompoundControlButton::CompoundControlButton(const Button& left, const Button& right, const Button& up, const Button& down)
	: CompoundControl()
	, m_Left{ left }
	, m_Right{ right}
	, m_Up{ up }
	, m_Down{ down }
{
}
dae::CompoundControlAxis::CompoundControlAxis(Axis axis)
	: CompoundControl()
	, m_Axis{ axis }
{
}

dae::InputContext dae::CompoundControlButton::GetActionContext(const InputDevice* pDevice) const
{
	const InputManager& inputManager{ inputManager.GetInstance() };
	const float leftValue{ inputManager.GetButtonValue(m_Left, pDevice) };
	const float rightValue{ inputManager.GetButtonValue(m_Right, pDevice) };
	const float upValue{ inputManager.GetButtonValue(m_Up, pDevice) };
	const float downValue{ inputManager.GetButtonValue(m_Down, pDevice) };

	return InputContext{ glm::vec2{ -leftValue + rightValue, -upValue + downValue }, pDevice };
}

dae::InputContext dae::CompoundControlAxis::GetActionContext(const InputDevice* pDevice) const
{
	return InputContext{ InputManager::GetInstance().GetAxisValue(m_Axis, pDevice), pDevice };
}
