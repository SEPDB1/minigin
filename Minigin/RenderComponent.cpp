#include "RenderComponent.h"
#include "Texture2D.h"
#include "Renderer.h"
#include "GameObject.h"
#include "ResourceManager.h"

const std::unordered_map<dae::RenderComponent::PivotType, glm::vec2> dae::RenderComponent::m_PivotTable
{
	{ dae::RenderComponent::PivotType::topLeft,		glm::vec2{ 0.0f, 0.0f } },
	{ dae::RenderComponent::PivotType::top,			glm::vec2{ 0.5f, 0.0f } },
	{ dae::RenderComponent::PivotType::topRight,	glm::vec2{ 1.0f, 0.0f } },
	{ dae::RenderComponent::PivotType::right,		glm::vec2{ 1.0f, 0.5f } },
	{ dae::RenderComponent::PivotType::bottomRight,	glm::vec2{ 1.0f, 1.0f } },
	{ dae::RenderComponent::PivotType::bottom,		glm::vec2{ 0.5f, 1.0f } },
	{ dae::RenderComponent::PivotType::bottomLeft,	glm::vec2{ 0.0f, 1.0f } },
	{ dae::RenderComponent::PivotType::left,		glm::vec2{ 0.0f, 0.5f } },
	{ dae::RenderComponent::PivotType::center,		glm::vec2{ 0.5f, 0.5f } }
};

dae::RenderComponent::RenderComponent(GameObject* pOwner, PivotType type)
	: BaseComponent(pOwner)
	, m_PivotType{ type }
	, m_Pivot{ m_PivotTable.at(type) }
{
}

dae::RenderComponent::RenderComponent(GameObject* pOwner, const glm::vec2& customPivot)
	: BaseComponent(pOwner)
	, m_Pivot{ customPivot }
	, m_PivotType{ PivotType::custom }
{
}

dae::RenderComponent::~RenderComponent()
{
}

void dae::RenderComponent::Render() const
{
	if (m_pTexture)
		SDLRenderer::GetInstance().RenderTexture(*m_pTexture, BaseComponent::GetOwner()->GetTransform(), m_Pivot);
}

void dae::RenderComponent::Update()
{

}

std::shared_ptr<dae::Texture2D> dae::RenderComponent::LoadTexture(const std::string& path)
{
	m_pTexture = ResourceManager::GetInstance().LoadTexture(path);
	return m_pTexture;
}

void dae::RenderComponent::SetPivot(PivotType newPivot)
{
	m_PivotType = newPivot;
	m_Pivot = m_PivotTable.at(newPivot);
}

void dae::RenderComponent::SetCustomPivot(const glm::vec2& customPivot)
{
	m_Pivot = customPivot;
	m_PivotType = PivotType::custom;
}

dae::Texture2D* dae::RenderComponent::GetTexture() const
{
	return m_pTexture.get();
}