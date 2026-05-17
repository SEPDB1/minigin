#include "Command.h"
#include "GameObject.h"
#include "InputTypes.h"

dae::GameObjectCommand::GameObjectCommand(GameObject* pGameObject)
	: m_pGameObject{ pGameObject }
{
}

dae::GameObject* dae::GameObjectCommand::GetGameObject() const
{
	return m_pGameObject;
}

dae::MoveCommand::MoveCommand(GameObject* pGameObject)
	: GameObjectCommand(pGameObject)
{

}

void dae::MoveCommand::Execute(InputContext context)
{
	auto pObject{ GetGameObject() };

	pObject->SetPosition(pObject->GetTransform().GetPosition() + std::get<glm::vec2>(context.value) * m_MovementSpeed);
}

dae::TestCommand::TestCommand(GameObject* pGameObject)
	: GameObjectCommand(pGameObject)
{
}

void dae::TestCommand::Execute(InputContext context)
{
	float value{ std::get<float>(context.value) };

	if (context.started)
	{
		static_assert(true);
		++value;
	}
	else if (context.isPressed)
	{
		static_assert(true);
	}
	else if (context.canceled)
	{
		static_assert(true);
	}
}
