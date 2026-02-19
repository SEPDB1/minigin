#include <string>
#include <algorithm>
#include <type_traits>
#include "GameObject.h"
#include "ResourceManager.h"
#include "Renderer.h"
#include "TextureComponent.h"

dae::GameObject::GameObject()
	: m_pComponents{}
{
}

dae::GameObject::~GameObject() = default;

void dae::GameObject::Update()
{

}

void dae::GameObject::Render() const
{
	auto it = std::ranges::find_if(
		m_pComponents, 
		[](auto& pComp) { return typeid(*pComp) == typeid(TextureComponent); });

	if (it != m_pComponents.end())
	{
		const auto& pos = GetComponent<TransformComponent>()->GetPosition();
		const auto pTextureComp = dynamic_cast<TextureComponent*>(it->get());

		if (pTextureComp)
		{
			Renderer::GetInstance().RenderTexture(*pTextureComp, pos.x, pos.y);
		}
	}
}