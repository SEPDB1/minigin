#pragma once
#include <vector>

namespace dae
{
	struct Rect;
	class HitboxComponent;
	class CollisionHandler final
	{
	public:
		CollisionHandler() = default;
		~CollisionHandler() = default;
		CollisionHandler(const CollisionHandler& other) = delete;
		CollisionHandler(CollisionHandler&& other) = delete;
		CollisionHandler& operator=(const CollisionHandler& other) = delete;
		CollisionHandler& operator=(CollisionHandler&& other) = delete;

		// Checks whether r is overlapping with a static HitboxComponent. 
		bool IsOverlapping(const Rect& r) const;

	private:
		friend class Scene;
		void Update();

		friend class HitboxComponent;
		void AddHitbox(const HitboxComponent* pHitboxComp);

		void HandleCollision(const HitboxComponent* pCollider1, const HitboxComponent* pCollider2) const;

		std::vector<const HitboxComponent*> m_pStaticHitboxes{};
		std::vector<const HitboxComponent*> m_pDynamicHitboxes{};
	};
}