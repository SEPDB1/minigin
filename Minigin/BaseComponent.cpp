#include "BaseComponent.h"

dae::BaseComponent::BaseComponent(GameObject* pOwner)
	: m_pOwner{ pOwner }
{

}

dae::BaseComponent::~BaseComponent() = default;

dae::GameObject* dae::BaseComponent::GetOwner() const
{
	return m_pOwner;
}
