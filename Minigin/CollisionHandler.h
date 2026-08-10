#pragma once
#include "Singleton.h"
#include <vector>

namespace dae
{
	class HitboxComponent;
	class CollisionHandler final : public Singleton<CollisionHandler>
	{
	public:
		CollisionHandler() = default;
		~CollisionHandler() = default;
		CollisionHandler(const CollisionHandler& other) = delete;
		CollisionHandler(CollisionHandler&& other) = delete;
		CollisionHandler& operator=(const CollisionHandler& other) = delete;
		CollisionHandler& operator=(CollisionHandler&& other) = delete;

		void Update();

		void AddHitbox(HitboxComponent* pHitboxComp);

	private:
		void HandleCollision(HitboxComponent* pCollider1, HitboxComponent* pCollider2);

		std::vector<HitboxComponent*> m_pStaticHitboxes{};
		std::vector<HitboxComponent*> m_pDynamicHitboxes{};
	};
}