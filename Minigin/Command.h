#pragma once
#include <glm/vec2.hpp>

namespace dae
{
	class GameObject;
	struct InputContext;
	class Command
	{
	public:
		virtual ~Command() = default;

		virtual void Execute(InputContext context) = 0;
	};

	class GameObjectCommand : public Command
	{
	protected:
		GameObjectCommand(GameObject* pGameObject);
		virtual ~GameObjectCommand() = default;

		GameObject* GetGameObject() const;

	private:
		GameObject* m_pGameObject;
	};

	class MoveCommand final : public GameObjectCommand
	{
	public:
		MoveCommand(GameObject* pGameObject);

		void Execute(InputContext context) override;

	private:
		float m_MovementSpeed{ 2.f };
	};

	class TestCommand final : public GameObjectCommand
	{
	public:
		TestCommand(GameObject* pGameObject);

		void Execute(InputContext context) override;
	};
}