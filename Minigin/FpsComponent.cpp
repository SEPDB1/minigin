#include "FpsComponent.h"

dae::FpsComponent::FpsComponent(GameObject* pOwner)
	: BaseComponent(pOwner)
	, m_pTextComponent{ nullptr }
{

}

void dae::FpsComponent::Update(float)
{

}

void dae::FpsComponent::SetTextComponent(TextComponent* pTextComponent)
{
	m_pTextComponent = pTextComponent;
}