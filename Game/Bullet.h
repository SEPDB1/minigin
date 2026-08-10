#pragma once
#include <glm/vec2.hpp>
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
		RenderComponent& m_RenderCompBullet;
		glm::vec2 m_MovementNormal{};
		float m_MovementSpeed{};
		float m_AccuTime{};
		//bool m_CanBounce{ true };

		inline const static float m_Timer{ 3.f };
	};
}