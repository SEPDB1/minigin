#include "InputAction.h"
#include "InputManager.h"

dae::InputActionButton::InputActionButton(const Button& button)
	: m_Buttons{ button }
{
}

dae::InputActionButton::InputActionButton(const std::vector<Button>& buttons)
	: m_Buttons{ buttons }
{
}

void dae::InputActionButton::AddButton(const Button& button)
{
	m_Buttons.push_back(button);
}

float dae::InputAction::GetButtonValue(const Button& button, const InputDevice* pDevice)
{
	const auto& inputManager{ InputManager::GetInstance() };

	if (inputManager.IsButtonCompatible(button, pDevice))
		return inputManager.GetButtonValue(button, pDevice);

	return 0.f;
}

dae::InputContext dae::InputActionButton::GetActionContext(const InputDevice* pDevice) const
{
	const auto& inputManager{ InputManager::GetInstance() };

	for (const auto& button : m_Buttons)
	{
		if (inputManager.IsButtonCompatible(button, pDevice))
		{
			return InputContext{
				inputManager.IsButtonPressed(button, pDevice),
				inputManager.IsButtonDownThisFrame(button, pDevice),
				inputManager.IsButtonUpThisFrame(button, pDevice)
			};
		}
	}

	return InputContext{ false, false, false };
}

dae::InputActionAxis2D::InputActionAxis2D(const Button& left, const Button& right, const Button& up, const Button& down)
	: m_LeftButtons{ left }
	, m_RightButtons{ right }
	, m_UpButtons{ up }
	, m_DownButtons{ down }
{
}

dae::InputActionAxis2D::InputActionAxis2D(const std::vector<Button>& leftButtons, const std::vector<Button>& rightButtons, 
	const std::vector<Button>& upButtons, const std::vector<Button>& downButtons)
	: m_LeftButtons{ leftButtons }
	, m_RightButtons{ rightButtons }
	, m_UpButtons{ upButtons}
	, m_DownButtons{ downButtons }
{
}

void dae::InputActionAxis2D::AddConfiguration(const Button& left, const Button& right, const Button& up, const Button& down)
{
	m_LeftButtons.push_back(left);
	m_RightButtons.push_back(right);
	m_UpButtons.push_back(up);
	m_DownButtons.push_back(down);
}

dae::InputContext dae::InputActionAxis2D::GetActionContext(const InputDevice* pDevice) const
{
	const float leftValue{ GetHighestValue(m_LeftButtons, pDevice) };
	const float rightValue{ GetHighestValue(m_RightButtons, pDevice) };
	const float upValue{ GetHighestValue(m_UpButtons, pDevice) };
	const float downValue{ GetHighestValue(m_DownButtons, pDevice) };

	// Only the value field matters
	return InputContext{ glm::vec2{ -leftValue + rightValue, -upValue + downValue } };
}

float dae::InputActionAxis2D::GetHighestValue(const std::vector<Button>& buttons, const InputDevice* pDevice)
{
	float highestValue{ 0.f };
	
	for (const auto& button : buttons)
	{
		if (InputManager::GetInstance().IsButtonCompatible(button, pDevice))
		{
			float newValue{ InputAction::GetButtonValue(button, pDevice) };

			if (newValue > highestValue)
				highestValue = newValue;
		}
	}

	return highestValue;
}

#pragma region InputActionAxis1D
//dae::InputActionAxis1D::InputActionAxis1D(const Button& left, const Button& right)
//	: m_LeftButtons{ left }
//	, m_RightButtons{ right }
//{
//}
//
//dae::InputContext dae::InputActionAxis1D::GetActionContext(const InputDevice* pDevice) const
//{
//	const float leftValue{ InputAction::GetButtonValue(m_LeftButtons, pDevice) };
//	const float rightValue{ InputAction::GetButtonValue(m_RightButtons, pDevice) };
//
//	// Only the value field matters
//	return InputContext{ -leftValue + rightValue };
//}
#pragma endregion InputActionAxis1D

