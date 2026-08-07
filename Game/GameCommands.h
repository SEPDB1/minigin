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
		GameObject& m_GunObj;
	};

	class GunRotateCommand final : public GameObjectCommand
	{
	public:
		GunRotateCommand(GameObject* pGameObject);

		void Execute(InputContext ctx) override;

	private:
		GameObject& m_TankObj;
	};
}