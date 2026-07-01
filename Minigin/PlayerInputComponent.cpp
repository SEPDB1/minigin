#include "PlayerInputComponent.h"
#include <algorithm>
#include <exception>
#include <iostream>
#include "InputAction.h"

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
		try // catch invalidaded pointers
		{
			if (binding.second)
				binding.second->Execute(binding.first->GetActionContext(m_pDevice));
		}
		catch (const std::exception& e)
		{
			std::cout << e.what() << "\n";
		}
	}
}

void dae::PlayerInputComponent::AddInputAction(const InputAction* pAction)
{
	m_CommandBindingTable.emplace(pAction, nullptr);
}

void dae::PlayerInputComponent::DeleteInputAction(const InputAction* pActionToDelete)
{
	std::erase_if(m_CommandBindingTable, [pActionToDelete](const auto& pair) { return pair.first == pActionToDelete; });
}
