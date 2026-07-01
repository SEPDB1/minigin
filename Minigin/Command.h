#pragma once
#include <glm/vec2.hpp>
#include "InputUtility.h"

namespace dae
{
	class GameObject;
	class Command
	{
	public:
		virtual ~Command() = default;

		virtual void Execute(InputContext ctx) = 0;
	};

	class GameObjectCommand : public Command
	{
	protected:
		GameObjectCommand(GameObject* pGameObject);
		virtual ~GameObjectCommand() = default;

		void Execute(InputContext ctx) override;

		GameObject* GetGameObject() const;

	private:
		GameObject* m_pGameObject;
	};

	class MoveCommand final : public GameObjectCommand
	{
	public:
		MoveCommand(GameObject* pGameObject, float movementSpeed);

		void Execute(InputContext ctx) override;
	private:
		float m_MovementSpeed{};
	};

	class TestCommand final : public GameObjectCommand
	{
	public:
		TestCommand(GameObject* pGameObject);

		void Execute(InputContext ctx) override;
	};
}