#include "GameCommands.h"
#include "MiniginEngine.h"

dae::TankMoveCommand::TankMoveCommand(GameObject* pGameObject, float movementSpeed)
	: GameObjectCommand(pGameObject)
	, m_MovementSpeed{ movementSpeed }
	, m_GunObj{ *pGameObject->GetChildAt(0) } 
{
}

void dae::TankMoveCommand::Execute(InputContext ctx)
{
	GameObject* pObj{ GameObjectCommand::GetGameObject() };
	glm::vec2 input{ std::get<glm::vec2>(ctx.value) };

	if (glm::length(input) > 0.f)
	{
		const float eTime{ Timer::GetInstance().GetElapsedTime() };
		float worldAngleTank{};
		const float worldAngleGun{ m_GunObj.GetTransform().GetRotation() };

		pObj->SetPosition(pObj->GetTransform().GetPosition() + input * m_MovementSpeed * eTime);

		// Moving Left
		if (input.x < 0.f)
			worldAngleTank = 180.f;
		// Moving Right
		else if (input.x > 0.f)
			worldAngleTank = 0.f;
		// Moving Down
		else if (input.y > 0.f)
			worldAngleTank = 90.f;
		// Moving Up
		else if (input.y < 0.f)
			worldAngleTank = 270.f;

		const float newTankAngle{ glm::radians(worldAngleTank) };
		pObj->SetRotation(newTankAngle);

		// Reset the angle original world angle of the gun
		m_GunObj.SetRotation(worldAngleGun - newTankAngle);
	}
}

dae::GunRotateCommand::GunRotateCommand(GameObject* pGameObject)
	: GameObjectCommand(pGameObject)
	, m_TankObj{ *pGameObject->GetParent() }
{
}

void dae::GunRotateCommand::Execute(InputContext ctx)
{
	GameObject* pObj{ GameObjectCommand::GetGameObject() };
	glm::vec2 input{ std::get<glm::vec2>(ctx.value) };

	if (glm::length(input) > 0.f)
	{
		const float tankRotation{ m_TankObj.GetTransform().GetRotation() };
		float eTime{ Timer::GetInstance().GetElapsedTime() };
		pObj->SetRotation(std::atan2f(input.y, input.x) - tankRotation);
	}
}
