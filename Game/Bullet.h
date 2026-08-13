#pragma once
#include <glm/vec2.hpp>
#include <cstdint>
#include "BaseComponent.h"

namespace dae
{
	class GameObject;
	struct CollisionInfo;
	class RenderComponent;
	class Bullet final : public BaseComponent
	{
	public:
		Bullet(GameObject* pOwner, float speed);
		~Bullet() = default;
		Bullet(const Bullet& other) = delete;
		Bullet(Bullet&& other) = delete;
		Bullet& operator=(const Bullet& other) = delete;
		Bullet& operator=(Bullet&& other) = delete;

		void Start() override;
		void Update() override;
		void OnCollision(const CollisionInfo& info) override;

	private:
		void DespawnBullet();

		RenderComponent& m_RenderCompBullet;
		glm::vec2 m_MovementNormal{};
		float m_MovementSpeed{};
		float m_AccuTime{};
		uint8_t m_BounceCount{};

		static inline constexpr uint8_t m_MaxBounceCount{ 5 };
		static inline constexpr float m_HitboxSize{ 8.f };
		static inline constexpr float m_AliveTimer{ 25.f };
	};
}