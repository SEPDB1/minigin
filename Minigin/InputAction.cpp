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

dae::InputActionButton::InputActionButton(std::vector<Button>&& buttons)
	: m_Buttons{ std::move(buttons) }
{
}

dae::InputContext dae::InputActionButton::GetActionContext(const InputDevice* pDevice) const
{
	const auto& inputManager{ InputManager::GetInstance() };

	for (const Button& button : m_Buttons)
	{
		const bool isPressed{ inputManager.IsButtonPressed(button, pDevice) };

		InputContext ctx
		{
			isPressed,
			inputManager.IsButtonDownThisFrame(button, pDevice),
			inputManager.IsButtonUpThisFrame(button, pDevice)
		};

		if (isPressed || ctx.isDownThisFrame || ctx.isUpThisFrame)
			return ctx;
	}

	return InputContext{};
}

dae::InputActionAxis2D::InputActionAxis2D(std::unique_ptr<CompoundControl> pControl)
	: m_Controls{}
{
	m_Controls.push_back(std::move(pControl));
}

dae::InputActionAxis2D::InputActionAxis2D(std::vector<std::unique_ptr<CompoundControl>>&& controls)
	: m_Controls{ std::move(controls) }
{
}

dae::InputContext dae::InputActionAxis2D::GetActionContext(const InputDevice* pDevice) const
{
	// Loop over all the controls and return the first non-zero one
	for (auto& pControl : m_Controls)
	{
		const InputContext ctx{ pControl->GetActionContext(pDevice) };
		const glm::vec2 input{ std::get<glm::vec2>(ctx.value) };

		if (input.x != 0.f || input.y != 0.f)
			return ctx;
	}

	return InputContext{ glm::vec2() };
}
