#include "PlayerTankComponent.h"
#include "MiniginEngine.h"

dae::PlayerTankComponent::PlayerTankComponent(GameObject* pOwner)
	: BaseComponent(pOwner)
	, m_TankObj{ std::make_unique<GameObject>() }
	, m_RenderComp{ m_TankObj->AttachComponent<RenderComponent>() }
	, m_PlayerInput{ nullptr }
{
}

void dae::PlayerTankComponent::Start()
{
}

void dae::PlayerTankComponent::Render() const
{
}

void dae::PlayerTankComponent::Update()
{
}
