#include "PlayerInputComponent.h"
#include <algorithm>
#include <exception>
#include <iostream>
#include "InputAction.h"
#include "InputManager.h"

dae::PlayerInputComponent::PlayerInputComponent(GameObject* pOwner, const InputDevice* pDevice)
	: BaseComponent(pOwner)
	, m_pDevices{ pDevice }
{
}

dae::PlayerInputComponent::PlayerInputComponent(GameObject* pOwner, std::vector<const InputDevice*> pDevices)
	: BaseComponent(pOwner)
	, m_pDevices{ pDevices }
{
}

void dae::PlayerInputComponent::Render() const
{

}

void dae::PlayerInputComponent::Update()
{
	for (auto& binding : m_CommandBindingTable)
	{
		for (auto pDevice : m_pDevices)
			binding.second->Execute(InputManager::GetInstance().GetActionByName(binding.first)->GetActionContext(pDevice));
	}
}
