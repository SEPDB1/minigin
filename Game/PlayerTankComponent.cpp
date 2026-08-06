#include "PlayerTankComponent.h"
#include "MiniginEngine.h"
#include "GameCommands.h"

dae::PlayerTankComponent::PlayerTankComponent(GameObject* pOwner, const InputDevice* pDevice)
	: BaseComponent(pOwner)
	, m_RenderCompTank{ pOwner->AttachComponent<RenderComponent>() }
	, m_GunObject{ SceneManager::GetInstance().GetActiveScene().AddObject() }
	, m_RenderCompGun{ m_GunObject.AttachComponent<RenderComponent>() }
	, m_PlayerInput{ pOwner->AttachComponent<PlayerInputComponent>(pDevice) }
{
}

void dae::PlayerTankComponent::Start()
{
	GameObject& tank{ *BaseComponent::GetOwner() };
	m_GunObject.SetParent(std::addressof(tank));
	m_GunObject.SetPosition(glm::vec2(-11.f, -8.f));
	tank.SetScale(glm::vec2(10.f, 10.f));
	tank.SetPosition(glm::vec2(100.f, 100.f));

	//m_GunObject.

	m_RenderCompTank.LoadTexture("Sprites/RedTank.png");
	m_RenderCompGun.LoadTexture("Sprites/RedTankGun.png");
	m_PlayerInput.AddCommandBinding("Move", std::make_unique<TankMoveCommand>(BaseComponent::GetOwner(), 500.f));
}

void dae::PlayerTankComponent::Render() const
{
}

void dae::PlayerTankComponent::Update()
{
}
