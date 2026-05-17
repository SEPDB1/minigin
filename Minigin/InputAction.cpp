#include "InputAction.h"
#include "InputManager.h"

// ***********
// BASE
// ***********
dae::InputActionBase::InputActionBase(std::string_view name, std::vector<UButton> buttons)
    : m_Buttons{ std::move(buttons) }
    ,m_Name{ name }
    , m_ID{ m_NextID++ }
{
}

const std::vector<dae::UButton>& dae::InputActionBase::GetButtons() const
{
    return m_Buttons;
}

std::string_view dae::InputActionBase::GetName() const
{
    return m_Name;
}

dae::InputActionID dae::InputActionBase::GetID() const
{
    return m_ID;
}

// ***********
// BUTTON
// ***********
dae::InputActionButton::InputActionButton(std::string_view name, UButton button)
    : InputActionBase(name, std::vector<UButton>{ button })
{

}

dae::InputContext dae::InputActionButton::GetContext(InputDeviceID deviceID) const
{
    return InputManager::GetInstance().GetContextByButton(InputActionBase::GetButtons().at(0), deviceID);
}

// ***********
// AXIS2D
// ***********
dae::InputActionAxis2D::InputActionAxis2D(std::string_view name, UButton left, UButton right, UButton up, UButton down)
    : InputActionBase(name, std::vector<UButton>{ left, right, up, down })
{

}

dae::InputContext dae::InputActionAxis2D::GetContext(InputDeviceID deviceID) const
{
    const auto& buttons{ InputActionBase::GetButtons() };
    const auto& inputManager{ InputManager::GetInstance() };

    InputContext left { inputManager.GetContextByButton(buttons.at(0), deviceID) };
    InputContext right{ inputManager.GetContextByButton(buttons.at(1), deviceID) };
    InputContext up   { inputManager.GetContextByButton(buttons.at(2), deviceID) };
    InputContext down { inputManager.GetContextByButton(buttons.at(3), deviceID) };

    const glm::vec2 combinedValue
    { 
    	-std::get<float>(left.value) + std::get<float>(right.value),
    	-std::get<float>(down.value) + std::get<float>(up.value) 
    };

    return InputContext{ combinedValue };
}
