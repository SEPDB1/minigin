#pragma once
#include <glm/vec2.hpp>
#include <InputTypes.h>

namespace dae
{
	class GameObject;
	class Command
	{
	protected:
		virtual ~Command() = default;

		virtual void Execute(ActionValue value) = 0;
	};

	class GameObjectCommand : public Command
	{
	protected:
		GameObjectCommand(GameObject* actor);
		virtual ~GameObjectCommand() override = default;

		GameObject* GetGameActor() const;

	private:
		GameObject* m_pGameObject;
	};

	class MoveCommand final : public GameObjectCommand
	{
	public:
		MoveCommand(GameObject* actor);

		void Execute(ActionValue value) override;
	private:
		float m_MovementSpeed{ 2.f };
	};
}