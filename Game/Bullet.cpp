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
	BaseComponent::GetOwner()->AttachComponent<HitboxComponent>(12.f, 12.f, false);
}

void dae::Bullet::Update()
{
	const float eTime{ Timer::GetInstance().GetElapsedTime() };
	auto pGameObj{ BaseComponent::GetOwner() };
	const float angle{ pGameObj->GetTransform().GetRotation() };
	m_MovementNormal = { glm::cos(angle), glm::sin(angle)  };

	pGameObj->SetPosition(pGameObj->GetTransform().GetPosition() + eTime * m_MovementSpeed * m_MovementNormal);

	m_AccuTime += eTime;

	//if (!m_CanBounce && m_AccuTime >= 0.1f)
	//{
	//	m_AccuTime = 0.f;
	//	m_CanBounce = true;
	//}
	if (m_AccuTime >= m_Timer)
	{
		m_AccuTime = 0.f;
		pGameObj->SetActiveSelf(false);
	}
}

void dae::Bullet::OnCollision(const CollisionInfo& info)
{
	//if (!m_CanBounce)
	//	return;

	// Reflect the movement normal
	const glm::vec2 r{ m_MovementNormal - 2.f * glm::dot(m_MovementNormal, info.surfaceNormal) * info.surfaceNormal };
	const float angle{ std::atan2f(r.y, r.x) };


	// Rotate the bullet
	BaseComponent::GetOwner()->SetRotation(angle);

	//m_CanBounce = false;
}
