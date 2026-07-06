#include "GameCommands.h"
#include "MiniginEngine.h"

dae::TankMoveCommand::TankMoveCommand(GameObject* pGameObject, float movementSpeed)
	: GameObjectCommand(pGameObject)
	, m_MovementSpeed{ movementSpeed }
{
}

void dae::TankMoveCommand::Execute(InputContext ctx)
{
	GameObject* pObj{ GameObjectCommand::GetGameObject() };
	glm::vec2 input{ std::get<glm::vec2>(ctx.value) };

	if (input.length() > 0.f)
	{
		float eTime{ Timer::GetInstance().GetElapsedTime() };
		pObj->SetPosition(pObj->GetTransform().GetPosition() + input * m_MovementSpeed * eTime);

		// Moving Left
		if (input.x < 0.f)
			pObj->SetRotation(glm::radians(180.f));
		// Moving Right
		else if (input.x > 0.f)
			pObj->SetRotation(glm::radians(0.f));
		// Moving Down
		else if (input.y > 0.f)
			pObj->SetRotation(glm::radians(90.f));
		// Moving Up
		else if (input.y < 0.f)
			pObj->SetRotation(glm::radians(270.f));
	}
}
