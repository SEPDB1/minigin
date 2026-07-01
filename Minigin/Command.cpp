#include "Command.h"
#include "GameObject.h"
#include <iostream>
#include <glm/geometric.hpp>

dae::GameObjectCommand::GameObjectCommand(GameObject* pGameObject)
	: m_pGameObject{ pGameObject }
{
}

void dae::GameObjectCommand::Execute(InputContext)
{
}

dae::GameObject* dae::GameObjectCommand::GetGameObject() const
{
	return m_pGameObject;
}

dae::MoveCommand::MoveCommand(GameObject* pGameObject, float movementSpeed)
	: GameObjectCommand(pGameObject)
	, m_MovementSpeed{ movementSpeed }
{

}

void dae::MoveCommand::Execute(InputContext ctx)
{
	auto input{ std::get<glm::vec2>(ctx.value) };
	auto pGO{ GetGameObject() };

	if (glm::length(input) > 0.f)
	{
		pGO->SetPosition(pGO->GetTransform().GetPosition() + input * m_MovementSpeed);
	}
}

dae::TestCommand::TestCommand(GameObject* pGameObject)
	: GameObjectCommand(pGameObject)
{
}

void dae::TestCommand::Execute(InputContext ctx)
{
	if (ctx.isDownThisFrame)
		std::cout << "Balls\n";
}
