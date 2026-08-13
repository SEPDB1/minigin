#include "PlayerTank.h"
#include "MiniginEngine.h"
#include "GameCommands.h"
#include "Bullet.h"

dae::PlayerTank::TankProperties::TankProperties(const std::string& filePathTank, const std::string& filePathGun, const glm::vec2& spawnPos)
	: filePathTank{ filePathTank }
	, filePathGun{ filePathGun }
	, spawnPos{ spawnPos }
{
}

dae::PlayerTank::PlayerTank(GameObject* pOwner, const InputDevice* pDevice, const TankProperties& properties)
	: BaseComponent(pOwner)
	, m_BulletPool{}
	, m_SpriteTank{ pOwner->AttachComponent<RenderComponent>() }
	, m_ObjGun{ SceneManager::GetInstance().GetActiveScene().AddObject() }
	, m_SpriteGun{ m_ObjGun.AttachComponent<RenderComponent>() }
	, m_ObjBarrel{ SceneManager::GetInstance().GetActiveScene().AddObject() }
	, m_PlayerInput{ pOwner->AttachComponent<PlayerInputComponent>(pDevice) }
	, m_HitboxComponent{ pOwner->AttachComponent<HitboxComponent>(m_HitboxSize, m_HitboxSize, false) }
{
	pOwner->SetPosition(properties.spawnPos);
	InitialiseBulletPool();

	// Assign textures
	m_SpriteTank.LoadTexture(properties.filePathTank);
	m_SpriteGun.LoadTexture(properties.filePathGun);
}

dae::PlayerTank::PlayerTank(GameObject* pOwner, std::vector<const InputDevice*>&& pDevices, const TankProperties& properties)
	: BaseComponent(pOwner)
	, m_BulletPool{}
	, m_SpriteTank{ pOwner->AttachComponent<RenderComponent>() }
	, m_ObjGun{ SceneManager::GetInstance().GetActiveScene().AddObject() }
	, m_SpriteGun{ m_ObjGun.AttachComponent<RenderComponent>() }
	, m_ObjBarrel{ SceneManager::GetInstance().GetActiveScene().AddObject() }
	, m_PlayerInput{ pOwner->AttachComponent<PlayerInputComponent>(std::move(pDevices)) }
	, m_HitboxComponent{ pOwner->AttachComponent<HitboxComponent>(m_HitboxSize, m_HitboxSize, false) }
{
	pOwner->SetPosition(properties.spawnPos);
	InitialiseBulletPool();

	// Assign textures
	m_SpriteTank.LoadTexture(properties.filePathTank);
	m_SpriteGun.LoadTexture(properties.filePathGun);
}

void dae::PlayerTank::Start()
{
	GameObject& tank{ *BaseComponent::GetOwner() };

	// Parent the gun object to the tank body
	m_ObjGun.SetParent(std::addressof(tank));
	m_ObjGun.SetPosition(glm::vec2( -3.f, 0.f));

	m_ObjBarrel.SetParent(std::addressof(m_ObjGun));
	m_ObjBarrel.SetPosition(glm::vec2(25.f, 0.f));

	tank.SetScale(glm::vec2(2.f, 2.f));

	auto moveCommand{ std::make_unique<TankMoveCommand>(std::addressof(tank), m_MovementSpeed, std::addressof(m_HitboxComponent)) };
	auto aimCommand{ std::make_unique<GunRotateCommand>(std::addressof(m_ObjGun)) };
	auto shootCommand{ std::make_unique<TankShootCommand>(std::addressof(tank), m_BulletSpeed) };

	m_PlayerInput.AddCommandBinding("Move", std::move(moveCommand));
	m_PlayerInput.AddCommandBinding("Aim", std::move(aimCommand));
	m_PlayerInput.AddCommandBinding("Shoot", std::move(shootCommand));
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
	auto& transformGunBarrel{ m_ObjBarrel.GetTransform() };

	pUnusedBullet->SetPosition(transformGunBarrel.GetPosition());
	pUnusedBullet->SetRotation(transformGunBarrel.GetRotation());
	pUnusedBullet->SetActiveSelf(true);

	SoundLocator::GetSoundSystem().Play("Sounds/Shoot.mp3");

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

dae::RedPlayerTank::RedPlayerTank(GameObject* pOwner, const InputDevice* pDevice, const glm::vec2& spawnPos)
	: PlayerTank(pOwner, pDevice, TankProperties{ "Sprites/RedTank.png", "Sprites/RedTankGun.png", spawnPos })
{
}

dae::RedPlayerTank::RedPlayerTank(GameObject* pOwner, std::vector<const InputDevice*>&& pDevices, const glm::vec2& spawnPos)
	: PlayerTank(pOwner, std::move(pDevices), TankProperties{ "Sprites/RedTank.png", "Sprites/RedTankGun.png", spawnPos })
{
}

dae::BluePlayerTank::BluePlayerTank(GameObject* pOwner, const InputDevice* pDevice, const glm::vec2& spawnPos)
	: PlayerTank(pOwner, pDevice, TankProperties{ "Sprites/BlueTank.png", "Sprites/BlueTankGun.png", spawnPos })
{
}

dae::BluePlayerTank::BluePlayerTank(GameObject* pOwner, std::vector<const InputDevice*>&& pDevices, const glm::vec2& spawnPos)
	: PlayerTank(pOwner, std::move(pDevices), TankProperties{ "Sprites/BlueTank.png", "Sprites/BlueTankGun.png", spawnPos })
{
}

dae::GreenPlayerTank::GreenPlayerTank(GameObject* pOwner, const InputDevice* pDevice, const glm::vec2& spawnPos)
	: PlayerTank(pOwner, pDevice, TankProperties{ "Sprites/GreenTank.png", "Sprites/RedTankGun.png", spawnPos })
{
}

dae::GreenPlayerTank::GreenPlayerTank(GameObject* pOwner, std::vector<const InputDevice*>&& pDevices, const glm::vec2& spawnPos)
	: PlayerTank(pOwner, std::move(pDevices), TankProperties{ "Sprites/GreenTank.png", "Sprites/RedTankGun.png", spawnPos })
{
}
