#include "CollisionHandler.h"
#include "HitboxComponent.h"
#include "CollisionUtility.h"
#include "GameObject.h"

void dae::CollisionHandler::Update()
{
	const size_t staticSize{ m_pStaticHitboxes.size() };
	const size_t dynamicSize{ m_pDynamicHitboxes.size() };

	// size_t looping used to prevent reallocation crashes
	for (size_t dynamicIdx{ 0 }; dynamicIdx < dynamicSize; ++dynamicIdx)
	{
		auto pDynamicHitbox{ m_pDynamicHitboxes[dynamicIdx] };

		if (!pDynamicHitbox->GetOwner()->IsActive())
			continue;

		const Rect dynamicBounds{ pDynamicHitbox->GetBounds() };

		// Loop over all static hitboxes
		for (size_t staticIdx{ 0 }; staticIdx < staticSize; ++staticIdx)
		{
			auto pStaticHitbox{ m_pStaticHitboxes[staticIdx] };

			if (!pStaticHitbox->GetOwner()->IsActive())
				continue;

			if (pStaticHitbox->GetBounds().IsOverlapping(dynamicBounds))
				HandleCollision(pStaticHitbox, pDynamicHitbox);
		}

		// Loop over dynamic ones
		for (size_t idx{ dynamicIdx + 1 }; idx < dynamicSize; ++idx)
		{
			auto pOtherHitbox{ m_pDynamicHitboxes[idx] };

			if (!pOtherHitbox->GetOwner()->IsActive())
				continue;

			if (pOtherHitbox->GetBounds().IsOverlapping(dynamicBounds))
				HandleCollision(pOtherHitbox, pDynamicHitbox);
		}
	}
}

void dae::CollisionHandler::AddHitbox(HitboxComponent* pHitboxComp)
{
	if (pHitboxComp->IsStatic())
		m_pStaticHitboxes.push_back(pHitboxComp);
	else
		m_pDynamicHitboxes.push_back(pHitboxComp);
}

void dae::CollisionHandler::HandleCollision(HitboxComponent* pCollider1, HitboxComponent* pCollider2)
{
	const Rect bounds1{ pCollider1->GetBounds() };
	const Rect bounds2{ pCollider2->GetBounds() };
	
	dae::CollisionInfo info1{ bounds2.GetCollisionNormal(bounds1.GetCenter()), pCollider2 };
	pCollider1->GetOwner()->OnCollision(info1);

	dae::CollisionInfo info2{ bounds1.GetCollisionNormal(bounds2.GetCenter()), pCollider1 };
	pCollider2->GetOwner()->OnCollision(info2);
}
