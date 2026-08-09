#pragma once
#include <array>
#include "Command.h"

namespace dae
{
	class Transform;

	// Converts axis input to the tank's rotation
	class TankMoveCommand final : public GameObjectCommand
	{
	public:
		TankMoveCommand(GameObject* pGameObject, float movementSpeed);

		void Execute(InputContext ctx) override;
	private:
		float m_MovementSpeed{};
		GameObject& m_pGunSpriteObj;
	};

	// Converts axis input to the gun's rotation
	class GunRotateCommand final : public GameObjectCommand
	{
	public:
		GunRotateCommand(GameObject* pGameObject);

		void Execute(InputContext ctx) override;

	private:
		GameObject& m_TankObj;
	};

	// Manages the bullets of the tank
	class TankShootCommand final : public GameObjectCommand
	{
	public:
		TankShootCommand(GameObject* pGameObject, float bulletSpeed);

		void Execute(InputContext ctx) override;

	private:
		float m_BulletSpeed{};
	};
}