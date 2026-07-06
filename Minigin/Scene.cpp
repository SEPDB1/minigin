#include <algorithm>
#include "Scene.h"
#include "BaseComponent.h"

dae::GameObject& dae::Scene::AddObject()
{
	m_Objects.emplace_back(std::make_unique<GameObject>());
	return *m_Objects.back();
}

void dae::Scene::Remove(const GameObject& object)
{
	m_Objects.erase(
		std::remove_if(
			m_Objects.begin(),
			m_Objects.end(),
			[&object](const auto& ptr) { return ptr.get() == &object; }
		),
		m_Objects.end()
	);
}

void dae::Scene::RemoveAll()
{
	m_Objects.clear();
}

void dae::Scene::Start()
{
	for (auto& object : m_Objects)
	{
		object->Start();
	}
}

void dae::Scene::Update()
{
	for(auto& object : m_Objects)
	{
		object->Update();
	}
}

void dae::Scene::Render() const
{
	for (const auto& object : m_Objects)
	{
		object->Render();
	}
}

