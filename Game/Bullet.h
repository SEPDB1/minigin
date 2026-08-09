#pragma once
#include <glm/vec2.hpp>
#include "BaseComponent.h"

namespace dae
{
	class GameObject;
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
		void Render() const override;
		void Update() override;

	private:
		RenderComponent& m_RenderCompBullet;
		float m_MovementSpeed{};
		float m_AccuTime{};

		inline const static float m_Timer{ 1.5f };
	};
}