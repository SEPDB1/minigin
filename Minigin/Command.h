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
		GameObjectCommand(GameObject* pGameObject) : m_pGameObject{ pGameObject } {};
		virtual ~GameObjectCommand() = default;

		GameObject* GetGameObject() const { return m_pGameObject; };

	private:
		GameObject* m_pGameObject;
	};
}