#include "GameCommands.h"

dae::TankMoveCommand::TankMoveCommand(GameObject* pGameObject, float movementSpeed)
	: GameObjectCommand(pGameObject)
	, m_MovementSpeed{ movementSpeed }
{
}

void dae::TankMoveCommand::Execute(InputContext ctx)
{
}
