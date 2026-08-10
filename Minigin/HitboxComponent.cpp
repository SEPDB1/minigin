#include "HitboxComponent.h"
#include "GameObject.h"
#include "CollisionHandler.h"

const dae::CollisionHandler dae::HitboxComponent::m_Handler{};

dae::HitboxComponent::HitboxComponent(GameObject* pOwner, bool isStatic)
	: HitboxComponent(pOwner, 0.f, 0.f, isStatic)
{
}

dae::HitboxComponent::HitboxComponent(GameObject* pOwner, float width, float height, bool isStatic)
	: BaseComponent(pOwner)
	, m_Width{ width }
	, m_Height{ height }
	, m_IsStatic{ isStatic }
{
	CollisionHandler::GetInstance().AddHitbox(this);
}

void dae::HitboxComponent::Update()
{
	auto pOwner{ BaseComponent::GetOwner() };
	auto pos{ pOwner->GetTransform().GetPosition() };
	auto scale{ pOwner->GetTransform().GetScale() };

	m_Bounds.width = m_Width * scale.x;
	m_Bounds.height = m_Height * scale.y;

	m_Bounds.left = pos.x - m_Bounds.width / 2.f;
	m_Bounds.top = pos.y - m_Bounds.height / 2.f;
}	

dae::Rect dae::HitboxComponent::GetBounds() const
{
	return m_Bounds;
}

bool dae::HitboxComponent::IsStatic() const
{
	return m_IsStatic;
}
