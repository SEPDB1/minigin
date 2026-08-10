#include "PlayerTank.h"
#include "MiniginEngine.h"
#include "GameCommands.h"
#include "Bullet.h"

dae::PlayerTank::PlayerTank(GameObject* pOwner, const InputDevice* pDevice, const glm::vec2& spawnPos)
	: BaseComponent(pOwner)
	, m_BulletPool{}
	, m_pRenderCompTank{ pOwner->AttachComponent<RenderComponent>() }
	, m_pGunSpriteObj{ SceneManager::GetInstance().GetActiveScene().AddObject() }
	, m_pRenderCompGun{ m_pGunSpriteObj.AttachComponent<RenderComponent>() }
	, m_pGunBarrelObj{ SceneManager::GetInstance().GetActiveScene().AddObject() }
	, m_PlayerInput{ pOwner->AttachComponent<PlayerInputComponent>(pDevice) }
{
	pOwner->SetPosition(spawnPos);
	InitialiseBulletPool();
}

dae::PlayerTank::PlayerTank(GameObject* pOwner, std::vector<const InputDevice*>&& pDevices, const glm::vec2& spawnPos)
	: BaseComponent(pOwner)
	, m_BulletPool{}
	, m_pRenderCompTank{ pOwner->AttachComponent<RenderComponent>() }
	, m_pGunSpriteObj{ SceneManager::GetInstance().GetActiveScene().AddObject() }
	, m_pRenderCompGun{ m_pGunSpriteObj.AttachComponent<RenderComponent>() }
	, m_pGunBarrelObj{ SceneManager::GetInstance().GetActiveScene().AddObject() }
	, m_PlayerInput{ pOwner->AttachComponent<PlayerInputComponent>(std::move(pDevices)) }
{
	pOwner->SetPosition(spawnPos);
	InitialiseBulletPool();
}

void dae::PlayerTank::Start()
{
	GameObject& tank{ *BaseComponent::GetOwner() };

	// Parent the gun object to the tank body
	m_pGunSpriteObj.SetParent(std::addressof(tank));
	m_pGunSpriteObj.SetPosition(glm::vec2( -3.f, 0.f));

	m_pGunBarrelObj.SetParent(std::addressof(m_pGunSpriteObj));
	m_pGunBarrelObj.SetPosition(glm::vec2(25.f, 0.f));

	tank.SetScale(glm::vec2(4.f, 4.f));
	//tank.AttachComponent<HitboxComponent>(32.f, 32.f, false);

	// Assign textures
	m_pRenderCompTank.LoadTexture("Sprites/RedTank.png");
	m_pRenderCompGun.LoadTexture("Sprites/RedTankGun.png");
	m_PlayerInput.AddCommandBinding("Move", std::make_unique<TankMoveCommand>(std::addressof(tank), 400.f));
	m_PlayerInput.AddCommandBinding("Aim", std::make_unique<GunRotateCommand>(std::addressof(m_pGunSpriteObj)));
	m_PlayerInput.AddCommandBinding("Shoot", std::make_unique<TankShootCommand>(std::addressof(tank), m_BulletSpeed));
}

void dae::PlayerTank::Render() const
{
}

void dae::PlayerTank::Update()
{
	if (!m_CanShoot)
	{
		m_AccuTime += Timer::GetInstance().GetElapsedTime();

		if (m_AccuTime >= m_ShotCooldown)
		{
			m_AccuTime = 0.f;
			m_CanShoot = true;
		}
	}
}

void dae::PlayerTank::Shoot()
{
	if (!m_CanShoot)
		return;

	GameObject* pUnusedBullet{ nullptr };

	// Cache the first unused bullet
	for (auto pBullet : m_BulletPool)
	{
		if (!pBullet->IsActive())
		{
			pUnusedBullet = pBullet;
			break;
		}
	}

	// No free bullets in the pool
	if (!pUnusedBullet)
		return;

	// Activate the unused bullet
	auto& transformBullet{ pUnusedBullet->GetTransform() };
	auto& transformGunBarrel{ m_pGunBarrelObj.GetTransform() };

	pUnusedBullet->SetPosition(transformGunBarrel.GetPosition());
	pUnusedBullet->SetRotation(transformGunBarrel.GetRotation());
	pUnusedBullet->SetActiveSelf(true);

	m_CanShoot = false;
}

void dae::PlayerTank::InitialiseBulletPool()
{
	for (auto& pBullet : m_BulletPool)
	{
		pBullet = std::addressof(SceneManager::GetInstance().GetActiveScene().AddObject());
		pBullet->AttachComponent<Bullet>(m_BulletSpeed);
		pBullet->SetActiveSelf(false);
	}
}
