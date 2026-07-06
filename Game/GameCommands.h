#pragma once
#include "Command.h"

namespace dae
{
	class TankMoveCommand final : public GameObjectCommand
	{
	public:
		TankMoveCommand(GameObject* pGameObject, float movementSpeed);

		void Execute(InputContext ctx) override;
	private:
		float m_MovementSpeed{};
	};
}