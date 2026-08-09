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
}

void dae::Bullet::Render() const
{
}

void dae::Bullet::Update()
{
	const float eTime{ Timer::GetInstance().GetElapsedTime() };
	auto pGameObj{ BaseComponent::GetOwner() };
	const float angle{ pGameObj->GetTransform().GetRotation() };
	const glm::vec2 movementNormal{ glm::cos(angle), glm::sin(angle)  };

	pGameObj->SetPosition(pGameObj->GetTransform().GetPosition() + eTime * m_MovementSpeed * movementNormal);

	m_AccuTime += eTime;
	if (m_AccuTime >= m_Timer)
	{
		m_AccuTime = 0.f;
		pGameObj->SetActiveSelf(false);
	}
}