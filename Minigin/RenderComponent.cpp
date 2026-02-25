#include "RenderComponent.h"
#include "Texture2D.h"
#include "Renderer.h"
#include "GameObject.h"
#include "ResourceManager.h"

dae::RenderComponent::RenderComponent(GameObject* pOwner)
	: BaseComponent(pOwner)
{

}

dae::RenderComponent::~RenderComponent()
{

}

void dae::RenderComponent::Render() const
{
	if (m_pTexture)
	{
		const auto& pos = BaseComponent::GetOwner()->GetWorldPosition();
		Renderer::GetInstance().RenderTexture(*m_pTexture, pos.x, pos.y);
	}
}

void dae::RenderComponent::Update()
{

}

dae::RenderComponent& dae::RenderComponent::LoadTexture(const std::string& path)
{
	m_pTexture = ResourceManager::GetInstance().LoadTexture(path);
	return *this;
}

dae::Texture2D* dae::RenderComponent::GetTexture() const
{
	return m_pTexture.get();
}