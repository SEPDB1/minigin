#include <string>
#include <algorithm>
#include <type_traits>
#include "GameObject.h"
#include "ResourceManager.h"
#include "Renderer.h"
#include "RenderComponent.h"
#include "TextComponent.h"

dae::GameObject::GameObject()
	: m_pComponents{}
	, m_Transform{}
{
}

dae::GameObject::~GameObject() = default;

void dae::GameObject::Update()
{
	for (const auto& pComp : m_pComponents)
	{
		pComp->Update();
	}
}

void dae::GameObject::SetPosition(const float x, const float y, const float z)
{
	m_Transform.SetPosition(x, y, z);
}

void dae::GameObject::SetPosition(const glm::vec3& position)
{
	m_Transform.SetPosition(position);
}

const dae::Transform& dae::GameObject::GetTransform() const
{
	return m_Transform;
}

void dae::GameObject::Render() const
{
	Texture2D* pTexture{};

	for (const auto& pComp : m_pComponents)
	{
		const auto pRawComp{ pComp.get() };

		if (typeid(*pRawComp) == typeid(RenderComponent))
		{
			pTexture = dynamic_cast<RenderComponent*>(pRawComp)->GetTexture();
		}
		else if (typeid(*pRawComp) == typeid(TextComponent))
		{
			pTexture = dynamic_cast<TextComponent*>(pRawComp)->GetTexture();
		}
		else continue;

		assert(pTexture != nullptr && "Component returned a null texture");

		const auto& pos = m_Transform.GetPosition();
		Renderer::GetInstance().RenderTexture(*pTexture, pos.x, pos.y);
	}
}