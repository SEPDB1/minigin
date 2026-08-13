#include "CollisionHandler.h"
#include "HitboxComponent.h"
#include "CollisionUtility.h"
#include "GameObject.h"

bool dae::CollisionHandler::IsOverlapping(const Rect& r) const
{
	const size_t staticSize{ m_pStaticHitboxes.size() };

	for (size_t staticIdx{ 0 }; staticIdx < staticSize; ++staticIdx)
	{
		const auto pStaticHitbox{ m_pStaticHitboxes[staticIdx] };

		if (!pStaticHitbox->GetOwner()->IsActive())
			continue;

		if (pStaticHitbox->GetBounds().IsOverlapping(r))
			return true;
	}
	return false;
}

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

void dae::CollisionHandler::AddHitbox(const HitboxComponent* pHitboxComp)
{
	if (pHitboxComp->IsStatic())
		m_pStaticHitboxes.push_back(pHitboxComp);
	else
		m_pDynamicHitboxes.push_back(pHitboxComp);
}

void dae::CollisionHandler::HandleCollision(const HitboxComponent* pCollider1, const HitboxComponent* pCollider2) const
{
	const Rect bounds1{ pCollider1->GetBounds() };
	const Rect bounds2{ pCollider2->GetBounds() };
	
	dae::CollisionInfo info{ std::move(bounds2.CreateCollisionInfo(bounds1.GetCenter())) };
	info.pCollider = pCollider2;
	pCollider1->GetOwner()->OnCollision(info);

	info = std::move(bounds1.CreateCollisionInfo(bounds2.GetCenter()));
	info.pCollider = pCollider1;
	pCollider2->GetOwner()->OnCollision(info);
}
