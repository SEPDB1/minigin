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

dae::InputActionAxis2D::InputActionAxis2D(std::unique_ptr<CompoundControl> pControl)
	: m_Controls{}
{
	m_Controls.push_back(std::move(pControl));
}

dae::InputActionAxis2D::InputActionAxis2D(std::vector<std::unique_ptr<CompoundControl>> controls)
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
