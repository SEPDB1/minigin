#include "PlayerInputComponent.h"
#include "InputAction.h"
#include "InputManager.h"
#include <algorithm>

dae::PlayerInputComponent::PlayerInputComponent(GameObject* pOwner, InputDeviceID deviceID)
	: BaseComponent(pOwner)
	, m_DeviceID{ deviceID }
{
}

void dae::PlayerInputComponent::Update()
{
	//for (InputActionID actionID : m_ActionsIDs)
	//{
	//	const auto& command = InputManager::GetInstance().GetCommand(actionID);
	//	const auto& context = InputManager::GetInstance().GetActionContext(actionID, m_DeviceID);

	//	// Execute command
	//	command(context);
	//}
}

void dae::PlayerInputComponent::BindAction(InputActionID id)
{
	m_ActionsIDs.push_back(id);
}

void dae::PlayerInputComponent::BindAction(const std::vector<InputActionID>& ids)
{
	m_ActionsIDs.insert(m_ActionsIDs.end(), ids.begin(), ids.end());
}

void dae::PlayerInputComponent::EraseAction(InputActionID idToRemove)
{
	std::erase_if(m_ActionsIDs, 
		[idToRemove](auto id) { 
			return idToRemove == id; 
		}
	);
}
