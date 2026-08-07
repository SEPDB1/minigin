#include "PlayerTankComponent.h"
#include "MiniginEngine.h"
#include "GameCommands.h"

dae::PlayerTankComponent::PlayerTankComponent(GameObject* pOwner, const InputDevice* pDevice)
	: BaseComponent(pOwner)
	, m_RenderCompTank{ pOwner->AttachComponent<RenderComponent>() }
	, m_GunObj{ SceneManager::GetInstance().GetActiveScene().AddObject() }
	, m_RenderCompGun{ m_GunObj.AttachComponent<RenderComponent>() }
	, m_PlayerInput{ pOwner->AttachComponent<PlayerInputComponent>(pDevice) }
{
}

void dae::PlayerTankComponent::Start()
{
	GameObject& tank{ *BaseComponent::GetOwner() };

	// Parent the gun object to the tank body
	m_GunObj.SetParent(std::addressof(tank));
	m_GunObj.SetPosition(glm::vec2( -3.f, 0.f));

	tank.SetScale(glm::vec2(4.f, 4.f));
	tank.SetPosition(glm::vec2(100.f, 100.f));

	// Assign textures
	m_RenderCompTank.LoadTexture("Sprites/RedTank.png");
	m_RenderCompGun.LoadTexture("Sprites/RedTankGun.png");
	m_PlayerInput.AddCommandBinding("Move", std::make_unique<TankMoveCommand>(BaseComponent::GetOwner(), 500.f));
	m_PlayerInput.AddCommandBinding("Aim", std::make_unique<GunRotateCommand>(std::addressof(m_GunObj)));
}

void dae::PlayerTankComponent::Render() const
{
}

void dae::PlayerTankComponent::Update()
{
}
