#include "RenderComponent.h"
#include "Texture2D.h"
#include "Renderer.h"
#include "GameObject.h"

dae::RenderComponent::RenderComponent(GameObject* pOwner)
	: BaseComponent(pOwner)
	, m_pTexture{ std::make_unique<Texture2D>() }
{

}

dae::RenderComponent::~RenderComponent()
{

}

void dae::RenderComponent::Render() const
{
	if (m_pTexture)
	{
		const auto& pos = BaseComponent::GetOwner()->GetTransform().GetPosition();
		Renderer::GetInstance().RenderTexture(*m_pTexture, pos.x, pos.y);
	}
}

void dae::RenderComponent::Update()
{

}

dae::RenderComponent& dae::RenderComponent::SetTexture(SDL_Texture* pTexture)
{
	m_pTexture->SetTexture(pTexture);
	return *this;
}

dae::RenderComponent& dae::RenderComponent::SetTexture(const std::string& path)
{
	m_pTexture->SetTexture(path);
	return *this;
}

dae::Texture2D* dae::RenderComponent::GetTexture() const
{
	return m_pTexture.get();
}