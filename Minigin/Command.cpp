#include "Command.h"
#include "GameObject.h"

dae::GameObjectCommand::GameObjectCommand(GameObject* pGameObject)
	: m_pGameObject{ pGameObject }
{
}

dae::GameObject* dae::GameObjectCommand::GetGameActor() const
{
	return m_pGameObject;
}

dae::MoveCommand::MoveCommand(GameObject* pGameObject)
	: GameObjectCommand(pGameObject)
{

}

void dae::MoveCommand::Execute(ActionValue value)
{
	auto pObject{ GetGameActor() };
	const glm::vec2 input{ std::get<glm::vec2>(value) };

	pObject->SetPosition(pObject->GetTransform().GetPosition() + input * m_MovementSpeed);
}



