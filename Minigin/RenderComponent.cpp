#include "RenderComponent.h"
#include "Texture2D.h"
#include "Renderer.h"
#include "GameObject.h"
#include "ResourceManager.h"

const std::unordered_map<dae::RenderComponent::Pivot, glm::vec2> dae::RenderComponent::m_OffsetTable
{
	{ dae::RenderComponent::Pivot::topLeft,		glm::vec2{ 0.0f, 0.0f } },
	{ dae::RenderComponent::Pivot::top,			glm::vec2{ 0.5f, 0.0f } },
	{ dae::RenderComponent::Pivot::topRight,	glm::vec2{ 1.0f, 0.0f } },
	{ dae::RenderComponent::Pivot::right,		glm::vec2{ 1.0f, 0.5f } },
	{ dae::RenderComponent::Pivot::bottomRight,	glm::vec2{ 1.0f, 1.0f } },
	{ dae::RenderComponent::Pivot::bottom,		glm::vec2{ 0.5f, 1.0f } },
	{ dae::RenderComponent::Pivot::bottomLeft,	glm::vec2{ 0.0f, 1.0f } },
	{ dae::RenderComponent::Pivot::left,		glm::vec2{ 0.0f, 0.5f } },
	{ dae::RenderComponent::Pivot::center,		glm::vec2{ 0.5f, 0.5f } }
};

dae::RenderComponent::RenderComponent(GameObject* pOwner, Pivot pivot)
	: BaseComponent(pOwner)
	, m_Pivot{ pivot }
{
}

dae::RenderComponent::~RenderComponent()
{
}

void dae::RenderComponent::Render() const
{
	if (m_pTexture)
		SDLRenderer::GetInstance().RenderTexture(*m_pTexture, BaseComponent::GetOwner()->GetTransform(), m_OffsetTable.at(m_Pivot));
}

void dae::RenderComponent::Update()
{

}

std::shared_ptr<dae::Texture2D> dae::RenderComponent::LoadTexture(const std::string& path)
{
	m_pTexture = ResourceManager::GetInstance().LoadTexture(path);
	return m_pTexture;
}

void dae::RenderComponent::SetPivot(Pivot newPivot)
{
	m_Pivot = newPivot;
}

dae::Texture2D* dae::RenderComponent::GetTexture() const
{
	return m_pTexture.get();
}