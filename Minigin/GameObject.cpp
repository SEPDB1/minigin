#include <string>
#include <algorithm>
#include <type_traits>
#include "GameObject.h"
#include "ResourceManager.h"
#include "Renderer.h"
#include "RenderComponent.h"
#include "TextComponent.h"

void dae::GameObject::Update()
{
	for (const auto& pComp : m_pComponents)
	{
		pComp->Update();
	}
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

		const auto& pos = GetWorldPosition();
		Renderer::GetInstance().RenderTexture(*pTexture, pos.x, pos.y);
	}
}

dae::GameObject& dae::GameObject::SetPosition(float x, float y, float z)
{
	return SetPosition(glm::vec3(x, y, z));
}

// OK
dae::GameObject& dae::GameObject::SetPosition(const glm::vec3& newPos)
{
	m_LocalTransform.SetPosition(newPos);
	SetPositionDirty();
	return *this;
}

// OK
dae::GameObject& dae::GameObject::SetParent(GameObject* pNewParent, bool keepWorldPosition)
{
	if (pNewParent == this || pNewParent == m_pParent || IsChild(pNewParent))
		return *this;

	if (!pNewParent)
	{
		SetPosition(GetWorldPosition());
	}
	else
	{
		if (keepWorldPosition)
			SetPosition(GetWorldPosition() - pNewParent->GetWorldPosition());

		SetPositionDirty();
	}

	// Remove itself from the previous parent
	if (m_pParent) m_pParent->RemoveChild(this);

	// Add parent
	m_pParent = pNewParent;

	// Add itself as child
	if (m_pParent) m_pParent->AddChild(this);

	// Update transform
	return *this;
}

// OK
void dae::GameObject::SetPositionDirty() const
{
	if (!m_IsPositionDirty)
	{
		m_IsPositionDirty = true;

		for (auto* child : m_pChildren)
			child->SetPositionDirty();
	}
}

// OK
const glm::vec3& dae::GameObject::GetWorldPosition() const
{
	if (m_IsPositionDirty)
		UpdateWorldPosition();
	return m_GlobalTransform.GetPosition();
}

// OK
const glm::vec3& dae::GameObject::GetLocalPosition() const
{
	return m_LocalTransform.GetPosition();
}

dae::GameObject* dae::GameObject::GetParent() const
{
	return m_pParent;
}

uint32_t dae::GameObject::GetChildCount() const
{
	return static_cast<uint32_t>(m_pChildren.size());
}

dae::GameObject* dae::GameObject::GetChildAt(uint32_t index) const
{
	assert(index < m_pChildren.size() && "Invalid idx entered for GetChildAt");
	return m_pChildren[index];
}

void dae::GameObject::AddChild(GameObject* pNewChild)
{
	// Check for invalid child
	if (!pNewChild || pNewChild == this || IsParent(pNewChild))
		return;

	// Remove newChild from previous parent
	GameObject* pParent{ pNewChild->GetParent() };
	if (pParent) pParent->RemoveChild(pNewChild);

	// Set itself as new parent
	pNewChild->SetParent(this, true);

	// add to children
	m_pChildren.push_back(pNewChild);

	// Update transform
}

void dae::GameObject::RemoveChild(GameObject* pChild)
{
	if (!pChild || !IsChild(pChild)) return;

	// Remove child from the list
	m_pChildren.erase(std::ranges::find(m_pChildren, pChild));

	// Remove itself as parent
	pChild->SetParent(nullptr, true);
}

// OK
void dae::GameObject::UpdateWorldPosition() const
{
	if(m_IsPositionDirty)
	{
		if (!m_pParent)
			m_GlobalTransform.SetPosition(m_LocalTransform.GetPosition());
		else
			m_GlobalTransform.SetPosition(m_pParent->GetWorldPosition() + m_LocalTransform.GetPosition());
	}
	m_IsPositionDirty = false;
}

bool dae::GameObject::IsChild(GameObject* pGameObject) const
{
	if (!pGameObject)
		return false;

	for (const auto pChild : m_pChildren)
	{
		if (pGameObject == pChild || pChild->IsChild(pGameObject))
		{
			return true;
		}
	}
	return false;
}

bool dae::GameObject::IsParent(GameObject* pGameObject) const
{
	if (!pGameObject || !m_pParent) 
		return false;

	if (pGameObject == m_pParent || m_pParent->IsParent(pGameObject))
		return true;
	
	return false;
}
