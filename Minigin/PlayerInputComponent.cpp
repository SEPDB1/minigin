#include "PlayerInputComponent.h"
#include <algorithm>
#include <exception>
#include <iostream>
#include "InputAction.h"
#include "InputManager.h"

dae::PlayerInputComponent::PlayerInputComponent(GameObject* pOwner, const InputDevice* pDevice)
	: BaseComponent(pOwner)
	, m_pDevice{ pDevice }
{
}

void dae::PlayerInputComponent::Render() const
{
}

void dae::PlayerInputComponent::Update()
{
	for (auto& binding : m_CommandBindingTable)
	{
		binding.second->Execute(InputManager::GetInstance().GetActionByName(binding.first)->GetActionContext(m_pDevice));
	}
}
