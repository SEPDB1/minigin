#include <string>
#include <algorithm>
#include <type_traits>
#include "GameObject.h"
#include "ResourceManager.h"
#include "Renderer.h"
#include "RenderComponent.h"
#include "TextComponent.h"
#include  <stdexcept>

void dae::GameObject::Update()
{
	for (const auto& pComp : m_pComponents)
	{
		pComp->Update();
	}
}

void dae::GameObject::Render() const
{
	for (const auto& pComp : m_pComponents)
	{
		pComp->Render();
	}
}

dae::GameObject& dae::GameObject::SetPosition(float x, float y)
{
	return SetPosition(glm::vec3(x, y, 0.f));
}

dae::GameObject& dae::GameObject::SetPosition(const glm::vec2& newPos)
{
	m_LocalTransform.SetPosition(newPos);
	SetTransformDirty();
	return *this;
}

dae::GameObject& dae::GameObject::SetRotation(float radians)
{
	m_LocalTransform.SetRotation(radians);
	SetTransformDirty();
	return *this;
}

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

		SetTransformDirty();
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

void dae::GameObject::SetTransformDirty() const
{
	if (!m_IsTransformDirty)
	{
		m_IsTransformDirty = true;

		for (auto pChild : m_pChildren)
			pChild->SetTransformDirty();
	}
}

const dae::Transform& dae::GameObject::GetTransform() const
{
	if (m_IsTransformDirty)
		UpdateWorldTransform();
	return m_GlobalTransform;
}

glm::vec2 dae::GameObject::GetWorldPosition() const
{
	if (m_IsTransformDirty)
		UpdateWorldTransform();
	return m_GlobalTransform.GetPosition();
}

glm::vec2 dae::GameObject::GetLocalPosition() const
{
	return m_LocalTransform.GetPosition();
}

float dae::GameObject::GetWorldRotation() const
{
	if (m_IsTransformDirty)
		UpdateWorldTransform();
	return m_GlobalTransform.GetRotation();
}

float dae::GameObject::GetLocalRotation() const
{
	return m_LocalTransform.GetRotation();
}

dae::GameObject* dae::GameObject::GetParent() const
{
	return m_pParent;
}

uint32_t dae::GameObject::GetChildCount() const
{
	return static_cast<uint32_t>(m_pChildren.size());
}

dae::GameObject* dae::GameObject::GetChildAt(int index) const
{
	try
	{
		return m_pChildren.at(index); 
	}
	catch (const std::out_of_range& e)
	{
		throw std::runtime_error(std::string(e.what()));
	}
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

void dae::GameObject::UpdateWorldTransform() const
{
	if (!m_pParent) 
		m_GlobalTransform.SetMatrix(m_LocalTransform.GetMatrix()); 
	else 
		m_GlobalTransform.SetMatrix(m_pParent->GetTransform().GetMatrix() * m_LocalTransform.GetMatrix());
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
