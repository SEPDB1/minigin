#include <algorithm>
#include "Scene.h"
#include "BaseComponent.h"

dae::GameObject& dae::Scene::AddObject()
{
	m_Objects.emplace_back(new GameObject());

	GameObject& newObj{ *m_Objects.back() };

	if (m_IsStarted)
		newObj.Start();

	return newObj;
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
	m_IsStarted = true;

	for (size_t i{ 0 }; i < m_Objects.size(); ++i)
		m_Objects[i]->Start();
}

void dae::Scene::Update()
{
	for (size_t i{ 0 }; i < m_Objects.size(); ++i)
		m_Objects[i]->Update();
}

void dae::Scene::Render() const
{
	for (const auto& object : m_Objects)
		object->Render();
}

