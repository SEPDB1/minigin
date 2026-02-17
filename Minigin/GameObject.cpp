#include <string>
#include <algorithm>
#include "GameObject.h"
#include "ResourceManager.h"
#include "Renderer.h"
#include "BaseComponent.h"
#include <type_traits>

dae::GameObject::GameObject()
	: m_Transform{}
	, m_pTexture{}
	, m_pComponents{}
{
}

dae::GameObject::~GameObject() = default;

void dae::GameObject::Update()
{

}

void dae::GameObject::Render() const
{
	const auto& pos = m_Transform.GetPosition();
	Renderer::GetInstance().RenderTexture(*m_pTexture, pos.x, pos.y);
}

void dae::GameObject::SetTexture(const std::string& filename)
{
	m_pTexture = ResourceManager::GetInstance().LoadTexture(filename);
}

void dae::GameObject::SetPosition(float x, float y)
{
	m_Transform.SetPosition(x, y, 0.0f);
}
