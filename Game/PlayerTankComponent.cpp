#include "PlayerTankComponent.h"
#include "MiniginEngine.h"
#include "GameCommands.h"

dae::PlayerTankComponent::PlayerTankComponent(GameObject* pOwner, const InputDevice* pDevice)
	: BaseComponent(pOwner)
	, m_RenderComp{ pOwner->AttachComponent<RenderComponent>() }
	, m_PlayerInput{ pOwner->AttachComponent<PlayerInputComponent>(pDevice) }
{
}

void dae::PlayerTankComponent::Start()
{
	BaseComponent::GetOwner()->SetScale(glm::vec2(10.f, 10.f));
	m_RenderComp.LoadTexture("Sprites/RedTank.png");
	m_PlayerInput.AddCommandBinding("Move", std::make_unique<TankMoveCommand>(BaseComponent::GetOwner(), 500.f));
}

void dae::PlayerTankComponent::Render() const
{
}

void dae::PlayerTankComponent::Update()
{
}
