#pragma once
#include "BaseComponent.h"
#include "CollisionUtility.h"

namespace dae
{
	class GameObject;
	class CollisionHandler;

	// A representation of a simple hitbox
	class HitboxComponent final : public BaseComponent
	{
	public:
		HitboxComponent(GameObject* pOwner, bool isStatic);
		HitboxComponent(GameObject* pOwner, float width, float height, bool isStatic);
		~HitboxComponent() = default;

		HitboxComponent(const HitboxComponent& other) = delete;
		HitboxComponent(HitboxComponent&& other) = delete;
		HitboxComponent& operator=(const HitboxComponent& other) = delete;
		HitboxComponent& operator=(HitboxComponent&& other) = delete;

		void Start() override {}
		void Render() const override {}
		void Update() override;

		Rect GetBounds() const;
		bool IsStatic() const;

	private:
		Rect m_Bounds{};
		float m_Width{};
		float m_Height{};
		bool m_IsStatic{};

		static const CollisionHandler m_Handler;
	};
}