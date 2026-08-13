#pragma once
#include <array>
#include "Command.h"

namespace dae
{
	class Transform;
	class HitboxComponent;

	// Converts axis input to the tank's rotation
	class TankMoveCommand final : public GameObjectCommand
	{
	public:
		TankMoveCommand(GameObject* pGameObject, float movementSpeed, HitboxComponent* pHitbox);

		void Execute(InputContext ctx) override;
	private:
		float m_MovementSpeed{};
		GameObject& m_ObjGun;
		HitboxComponent* m_pHitboxComponent{};
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

	// Assumes that a PlayerTank component is attached to the game object.
	class TankShootCommand final : public GameObjectCommand
	{
	public:
		TankShootCommand(GameObject* pGameObject, float bulletSpeed);

		void Execute(InputContext ctx) override;

	private:
		float m_BulletSpeed{};
	};

	// Assumes that a StartScreen component is attached to the game object.
	class JoinCommand final : public GameObjectCommand
	{
	public:
		JoinCommand(GameObject* pGameObject);

		void Execute(InputContext ctx) override;
	};

	// Assumes that a StartScreen component is attached to the game object.
	class LeaveCommand final : public GameObjectCommand
	{
	public:
		LeaveCommand(GameObject* pGameObject);

		void Execute(InputContext ctx) override;
	};

	// Assumes that a StartScreen component is attached to the game object.
	class ReadyUpCommand final : public GameObjectCommand
	{
	public:
		ReadyUpCommand(GameObject* pGameObject);

		void Execute(InputContext ctx) override;
	};
}