#include "Bullet.h"
#include "MiniginEngine.h"

dae::Bullet::Bullet(GameObject* pOwner, float speed)
	: BaseComponent(pOwner)
	, m_RenderCompBullet{ pOwner->AttachComponent<RenderComponent>() }
	, m_MovementSpeed{ speed }
{
}

void dae::Bullet::Start()
{
	m_RenderCompBullet.LoadTexture("Sprites/BulletPlayer.png");
	BaseComponent::GetOwner()->SetScale(glm::vec2(2.f, 2.f)).AttachComponent<HitboxComponent>(m_HitboxSize, m_HitboxSize, false);
}

void dae::Bullet::Update()
{
	const float eTime{ Timer::GetInstance().GetElapsedTime() };
	auto pGameObj{ BaseComponent::GetOwner() };
	const float angle{ pGameObj->GetTransform().GetRotation() };
	m_MovementNormal = { glm::cos(angle), glm::sin(angle)  };

	pGameObj->SetPosition(pGameObj->GetTransform().GetPosition() + eTime * m_MovementSpeed * m_MovementNormal);

	if (m_AccuTime += eTime >= m_AliveTimer)
	{
		m_AccuTime = 0.f;
		DespawnBullet();
	}
}

void dae::Bullet::OnCollision(const CollisionInfo& info)
{
	const glm::vec2 r{ m_MovementNormal - 2.f * glm::dot(m_MovementNormal, info.surfaceNormal) * info.surfaceNormal };
	const float angle{ std::atan2f(r.y, r.x) };

	BaseComponent::GetOwner()->SetRotation(angle);

	if (++m_BounceCount >= m_MaxBounceCount)
	{
		m_BounceCount = 0;
		DespawnBullet();
	}
}

void dae::Bullet::DespawnBullet()
{
	BaseComponent::GetOwner()->SetActiveSelf(false);
}
