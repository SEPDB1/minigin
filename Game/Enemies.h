#pragma once
#include "BaseComponent.h"
#include <string>
#include <glm/fwd.hpp>

namespace dae
{
	class GameObject;
	class RenderComponent;
	class HitboxComponent;

	class EnemyComponent : public BaseComponent
	{
	public:
		virtual ~EnemyComponent() = default;
		EnemyComponent(const EnemyComponent& other) = delete;
		EnemyComponent(EnemyComponent&& other) = delete;
		EnemyComponent& operator=(const EnemyComponent& other) = delete;
		EnemyComponent& operator=(EnemyComponent&& other) = delete;

	protected:
		EnemyComponent(GameObject* pOwner, const std::string& pathSprite, float movementSpeed);

	private:
		RenderComponent& m_Sprite;
		HitboxComponent& m_Hitbox;
		float m_MovementSpeed;

		static inline constexpr float m_HitboxSize{ 16.f };
		static inline constexpr float m_SpriteScale{ 2.f };
	};

	class EnemyTank final : public EnemyComponent
	{
	public:
		EnemyTank(GameObject* pOwner, const glm::vec2& pos);
		~EnemyTank() = default;
		EnemyTank(const EnemyTank& other) = delete;
		EnemyTank(EnemyTank&& other) = delete;
		EnemyTank& operator=(const EnemyTank& other) = delete;
		EnemyTank& operator=(EnemyTank&& other) = delete;

	private:
		static inline constexpr float m_MovementSpeed{ 200.f };
	};

	class Recognizer final : public EnemyComponent
	{
	public:
		Recognizer(GameObject* pOwner, const glm::vec2& pos);
		~Recognizer() = default;
		Recognizer(const Recognizer& other) = delete;
		Recognizer(Recognizer&& other) = delete;
		Recognizer& operator=(const Recognizer& other) = delete;
		Recognizer& operator=(Recognizer&& other) = delete;

	private:
		static inline constexpr float m_MovementSpeed{ 400.f };
	};
}