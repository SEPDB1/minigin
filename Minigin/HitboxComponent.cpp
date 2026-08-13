#include "HitboxComponent.h"
#include "GameObject.h"
#include "CollisionHandler.h"
#include "SceneManager.h"
#include "Scene.h"

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
	SceneManager::GetInstance().GetActiveScene().GetCollisionHandler().AddHitbox(this);
}

void dae::HitboxComponent::Update()
{
	auto pOwner{ BaseComponent::GetOwner() };
	auto pos{ pOwner->GetTransform().GetPosition() };

	m_Bounds = CalculateBounds(pos);
}	

dae::Rect dae::HitboxComponent::GetBounds() const
{
	return m_Bounds;
}

bool dae::HitboxComponent::IsStatic() const
{
	return m_IsStatic;
}

dae::Rect dae::HitboxComponent::CalculateBounds(const glm::vec2& center)
{
	const auto scale{ BaseComponent::GetOwner()->GetTransform().GetScale() };
	Rect bounds{ 0.f, 0.f,  m_Width * scale.x, m_Height * scale.y, };
	bounds.left = center.x - m_Bounds.width / 2.f;
	bounds.top = center.y - m_Bounds.height / 2.f;

	return bounds;
}
